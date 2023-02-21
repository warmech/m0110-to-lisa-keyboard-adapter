//USB and keypad-related data and functions have been removed from this library.
//This file has been updated with various data and functions to extend its functionality;
//these changes will be marked accordingly.
#include <Arduino.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "lisakeysconfig.h"
#include "lisakeyslib.h"
#include "lisakeyswrite.h"
#include "m0110.h"
#include "scancodes.h"

//Debounce management - NEW
unsigned long mod_button_time = 0;
unsigned long last_mod_button_time = 0;

//Interrupt pin setting - NEW
static const int INTERRUPT_PIN = 7;

//Declare Mac keyboard ID variable - NEW
int mac_keyboard_model;
char * mac_keyboard_name;

//Mode change default and maximum values - NEW
unsigned int mod_function = 0;
unsigned int mod_function_max = 2;

//Get things ready - MODIFIED
void setup() {
  //Set the mode change button's pin and keyboard cable type pin - NEW
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  pinMode(M0110_CABLE_TYPE, INPUT_PULLUP);

  //Determine the cable type by way of DIP switch 3 (Off = Mac / On = Handset) - NEW
  determine_keyboard_cable();

  //Get Mac keyboard model ID - NEW
  mac_keyboard_model = m0110_init();
  mac_keyboard_name = m0110_identify_keyboard(mac_keyboard_model);

  //Setup the mode change button interrupt - NEW
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), mod_button_isr, RISING);
  delay(250);
}

//Alternate between adapter mode depending on mode setting (changed via the ISR) - NEW
void loop() {
  //0 - Mac >> Lisa
  if (mod_function == 0) {
    delay(250);
    m0110_output_mode();
  }
  //1 - Serial/Mac >> Lisa
  if (mod_function == 1) {
    delay(250);
    serial_output_mode();
  }
  //2 - Test Mode
  if (mod_function == 2) {
    delay(250);
    keyboard_test_mode();
  }
}

//Get Lisa keyboard region as set by DIP switches 1 and 2 (US: OFF/OFF, UK: ON/OFF, DE: OFF/ON, or FR: ON/ON)
static unsigned char get_layout_setting() {
	pinMode(US_UK_SWITCH, INPUT_PULLUP);
	pinMode(DE_FR_SWITCH, INPUT_PULLUP);
  if (digitalRead(US_UK_SWITCH)) {
    return digitalRead(DE_FR_SWITCH)
         ? LK_LAYOUT_US : LK_LAYOUT_UK;
  } else {
    return digitalRead(DE_FR_SWITCH)
         ? LK_LAYOUT_DE : LK_LAYOUT_FR;
  }
}

//Get the character name for the Mac key pressed - NEW
char * convert_mac_character(uint8_t mac_scancode) {
  return mac_key_name(mac_scancode, mac_keyboard_model);
}

//Convert the Mac scancode to a Lisa scancode - NEW
uint8_t convert_mac_scancode(uint8_t mac_scancode) {
  if ((mac_keyboard_model != 0x0B) && (mac_keyboard_model != 0x1B)) {
    if ((mac_keyboard_model == 0x03) || (mac_keyboard_model == 0x11) || (mac_keyboard_model == 0x13)) {
      return translate_mac_to_lisa(mac_scancode, keymap_m0110);
    } else {
      return translate_mac_to_lisa(mac_scancode, keymap_m0110_intl);
    }
  } else {
    return translate_mac_to_lisa(mac_scancode, keymap_m0110a);
  }
}

//Keyboard test function for both the Lisa and M0110/A keyboards; based on serial_input_debug() in RebeccaRGB's LisaKeys project - MODIFIED
void keyboard_test_mode() {
  boolean isIDByte = false;
  unsigned char packet;
  unsigned char pressed;
  uint8_t mac_key = 0x00;

  lk_start_input();

  Serial.begin(9600);
  Serial.println("Keyboard Test Mode\n");

  if (mac_keyboard_model != 0xFF) {
    Serial.print("Macintosh keyboard detected: ");
    Serial.print(mac_keyboard_name);
    Serial.print(" (0x");
    Serial.print(mac_keyboard_model, HEX);
    Serial.print(")\n");
  } else {
    Serial.print(mac_keyboard_name);
    Serial.print("\n");
  }

  while (mod_function == 2) {

    //Did we get a Lisa keypress?
    if (packet = lk_read()) {
      if (packet == LK_INIT) {
        isIDByte = true;
      } else if (isIDByte) {
        Serial.print("Lisa keyboard detected: ");
        Serial.print(lk_layout_name(packet));
        Serial.print(" Model (0x");
        Serial.print(packet, HEX);
        Serial.print(")\n");
        isIDByte = false;
      } else {
        pressed = packet & 0x80;
        packet &= 0x7F;
        Serial.print(pressed ? "Lisa key pressed: " : "Lisa key released: ");
        Serial.println(lk_key_name(packet));
        Serial.print("\n");
        //Serial.print(packet, HEX);
      }
    }
    
    //Did we get a Mac keypress?
    if (mac_keyboard_model != 0xFF) {
      if (mac_key = m0110_recv_key()) {
        if (mac_key != 0x7b) {
          if (!bitRead(mac_key,7)) {
            Serial.print("Macintosh key pressed: ");
            Serial.print(convert_mac_character(mac_key));
            Serial.print("\n");
          } else {
            Serial.print("Macintosh key released: ");
            Serial.print(convert_mac_character(mac_key ^ 0x80));
            Serial.print("\n");
          }
        }
      }
    }
  }
}

//Send the translated M0110/A key to the output buffer - NEW
void lk_write_mackey(uint8_t mac_key) {
  lk_write(mac_key);
  lk_delay(LK_WRITE_DELAY); 
}

//Handle M0110/A input and output Lisa scancodes to Lisa hardware - NEW
void m0110_output_mode() {
  uint8_t mac_key = 0x00;
  
  lk_start_output(get_layout_setting());
  
  while (mod_function == 0) {
    mac_key = m0110_recv_key();
    if (mac_key != 0x7B) {
      if (!bitRead(mac_key,7)) {
        lk_write_mackey(convert_mac_scancode(mac_key) | LK_PRESSED);
      } else {
        if (check_keyrelease_for_multi_release(mac_key)) {
          if (multi_release_buffer[1] != 0x7B) {
            lk_write_mackey(convert_mac_scancode(multi_release_buffer[0] ^ 0x80));
            lk_flush();
            if (!bitRead(multi_release_buffer[1],7)) {
              lk_write_mackey(convert_mac_scancode(multi_release_buffer[1]) | LK_PRESSED);
            } else {
              lk_write_mackey(convert_mac_scancode(multi_release_buffer[1] ^ 0x80));
            }   
          } else {
            lk_write_mackey(convert_mac_scancode(multi_release_buffer[0] ^ 0x80));
          }
        } else {
          lk_write_mackey(convert_mac_scancode(mac_key ^ 0x80));
        }
      }
    }
    lk_flush();
  }
}

//Serial Output Mode - used by the Python program loader or for general serial console input to the Lisa
#define SERIAL_BUFFER_SIZE 80

void serial_output_mode() {
  unsigned char packet;
  unsigned char buf[SERIAL_BUFFER_SIZE];
  int ptr = 0;
  int ch;
  
  lk_start_output(get_layout_setting());
  Serial.begin(9600);
  Serial.println("Serial Communications Mode");
  while (mod_function == 1) {
    if ((ch = Serial.read()) > 0) {
      Serial.print(ch,HEX);
      Serial.print("\n");
      if (ch == '\n' || ch == '\r') {
        buf[ptr] = 0;
        if      (buf[0] == '#') /* "comment" / no-op */;
        else if (buf[0] == '$') lk_write_hex  (&buf[1]);
        else if (buf[0] == '%') lk_write_raw  (&buf[1]);
        else if (buf[0] == '&') lk_write_coded(&buf[1]);
        else if (buf[0] == '*') lk_write_blu_bootstrap(buf[1] & 0x0F);
        else if (buf[0] == '@') lk_write_ascii(&buf[1]);
        else                    lk_write_ascii(&buf[0]);
        ptr = 0;
      } else if (ptr < (SERIAL_BUFFER_SIZE - 1)) {
        buf[ptr] = ch;
        ptr++;
      }
    }
    lk_flush();
  }
}

//Interrupt Service Routine for alternating between adapter modes - NEW
void mod_button_isr() {
  //Debounce timer increment
  mod_button_time = millis();

  //Account for debounce and update mode accordingly; reset mode to zero if button is pressed while mode is at its max allowed value
  if (mod_button_time - last_mod_button_time > 250) {
    if (mod_function < mod_function_max) {
      mod_function++;
    } else {
      mod_function = 0;
    }
    last_mod_button_time = mod_button_time;
  }

}
