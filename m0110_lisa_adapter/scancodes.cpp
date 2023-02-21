//This library created by warmech (GitHub/68KMLA/TinkerDifferent/LisaList2) under the WTFPL license.
//See the "copying" file in license directory for licensing details. For all intents and purposes,
//this is to be considered public domain.

//Include headers
#include <Arduino.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "m0110.h"
#include "scancodes.h"

//Keyboard character lookup
const char * mac_key_name(uint8_t mac_scancode, int mac_keyboard_model) {
  switch (mac_scancode) {
    case 0x1D: return "0";
    case 0x12: return "1";
    case 0x13: return "2";
    case 0x14: return "3";
    case 0x15: return "4";
    case 0x17: return "5";
    case 0x16: return "6";
    case 0x1A: return "7";
    case 0x1C: return "8";
    case 0x19: return "9";
    case 0x00: return "A";
    case 0x0B: switch (mac_keyboard_model) {
      case 0x09: return "V";
      default:   return "B";
    }
    case 0x08: switch (mac_keyboard_model) {
      case 0x09: return "X";
      default:   return "C";
    }
    case 0x02: return "D";
    case 0x0E: return "E";
    case 0x03: return "F";
    case 0x05: return "G";
    case 0x04: return "H";
    case 0x22: return "I";
    case 0x26: return "J";
    case 0x28: return "K";
    case 0x25: return "L";
    case 0x2E: switch (mac_keyboard_model) {
      case 0x09: return "N";
      default:   return "M";
    }
    case 0x2D: switch (mac_keyboard_model) {
      case 0x09: return "B";
      default:   return "N";
    }
    case 0x1F: return "O";
    case 0x23: return "P";
    case 0x0C: return "Q";
    case 0x0F: return "R";
    case 0x01: return "S";
    case 0x10: return "T";
    case 0x20: return "U";
    case 0x09: switch (mac_keyboard_model) {
      case 0x09: return "C";
      default:   return "V";
    }
    case 0x0D: return "W";
    case 0x07: switch (mac_keyboard_model) {
      case 0x09: return "Z";
      default:   return "X";
    }
    case 0x11: return "Y";
    case 0x06: switch (mac_keyboard_model) {
      case 0x09: return "\\";
      default:   return "Z";
    }
    case 0x32: switch (mac_keyboard_model) {
      case 0x09: return "§";
      default:   return "`";
    }
    case 0x1B: return "-";
    case 0x18: return "=";
    case 0x33: return "Backspace";
    case 0x30: return "Tab";
    case 0x21: return "[";
    case 0x1E: return "]";
    case 0x39: return "Caps Lock";
    case 0x29: return ";";
    case 0x27: return "'";
    case 0x24: switch (mac_keyboard_model) {
      case 0x09: return "`";
      default:   return "Return";
    }
    case 0x38: return "Shift";
    case 0x2B: switch (mac_keyboard_model) {
      case 0x09: return "M";
      default:   return ",";
    }
    case 0x2F: switch (mac_keyboard_model) {
      case 0x09: return ",";
      default:   return ".";
    }
    case 0x2C: switch (mac_keyboard_model) {
      case 0x09: return ".";
      default:   return "/";
    }return "/";
    case 0x3A: return "Option";
    case 0x37: return "Command / Apple";
    case 0x31: switch (mac_keyboard_model) {
      case 0x09: return "Enter";
      default:   return "Space";
    }
    case 0x2A: switch (mac_keyboard_model) {
      case 0x09: return "Return";
      default:   return "\\";
    }
    case 0x4D: switch (mac_keyboard_model) {
      case 0x0B: return "Up";
      default:   return "NumPad /";
    }
    case 0x46: switch (mac_keyboard_model) {
      case 0x0B: return "Left";
      default:   return "NumPad +";
    }
    case 0x42: switch (mac_keyboard_model) {
      case 0x0B: return "Right";
      default:   return "NumPad *";
    }
    case 0x48: switch (mac_keyboard_model) {
      case 0x0B: return "Down";
      default:   return "NumPad ,";
    }
    case 0x52: return "NumPad 0";
    case 0x53: return "NumPad 1";
    case 0x54: return "NumPad 2";
    case 0x55: return "NumPad 3";
    case 0x56: return "NumPad 4";
    case 0x57: return "NumPad 5";
    case 0x58: return "NumPad 6";
    case 0x59: return "NumPad 7";
    case 0x5B: return "NumPad 8";
    case 0x5C: return "NumPad 9";
    case 0x47: return "NumPad Clear";
    case 0x4C: return "NumPad Enter";
    case 0x68: return "NumPad =";
    case 0x4E: return "NumPad -";
    case 0x62: return "NumPad *";
    case 0x41: return "NumPad .";
    case 0x66: return "NumPad +";
    case 0x6D: return "NumPad /";
    case 0x0A: return "/"; //M0110 international scancode - not present on other models
    case 0x34: switch (mac_keyboard_model) {
      case 0x09: return "Space"; //M0110 international scancode
      default:   return "Enter"; //M0110 scancode
    }
    default:   return "???";
  }
}

//Number Pad character lookup
const char * m0120_key_name(uint8_t mac_scancode) {
  switch (mac_scancode) {
    case 0x52: return "NumPad 0";
    case 0x53: return "NumPad 1";
    case 0x54: return "NumPad 2";
    case 0x55: return "NumPad 3";
    case 0x56: return "NumPad 4";
    case 0x57: return "NumPad 5";
    case 0x58: return "NumPad 6";
    case 0x59: return "NumPad 7";
    case 0x5B: return "NumPad 8";
    case 0x5C: return "NumPad 9";
    case 0x47: return "NumPad Clear";
    case 0x48: return "NumPad ,";
    case 0x4C: return "NumPad Enter";
    case 0x4E: return "NumPad -";
    case 0x42: return "NumPad *";
    case 0x41: return "NumPad .";
    case 0x46: return "NumPad +";
    case 0x4D: return "NumPad /";
    default:   return "???";
    }
}

//Keymap info
uint8_t keymap_m0110a = 0;
uint8_t keymap_m0110 = 1;
uint8_t keymap_m0110_intl = 2;
uint8_t keymap_lisa_us = 3;
uint8_t lookup_table_rows = 80;
uint8_t lookup_table_cols = 4;

//Keymap lookup table
const uint8_t scancode_lookup_table[80][4] PROGMEM {
  {0x1D,0x1D,0x1D,0x51}, //0
  {0x12,0x12,0x12,0x74}, //1
  {0x13,0x13,0x13,0x71}, //2
  {0x14,0x14,0x14,0x72}, //3
  {0x15,0x15,0x15,0x73}, //4
  {0x17,0x17,0x17,0x64}, //5
  {0x16,0x16,0x16,0x61}, //6
  {0x1A,0x1A,0x1A,0x62}, //7
  {0x1C,0x1C,0x1C,0x63}, //8
  {0x19,0x19,0x19,0x50}, //9
  {0x00,0x00,0x00,0x70}, //A
  {0x0B,0x0B,0x2D,0x6E}, //B
  {0x08,0x08,0x09,0x6D}, //C
  {0x02,0x02,0x02,0x7B}, //D
  {0x0E,0x0E,0x0E,0x60}, //E
  {0x03,0x03,0x03,0x69}, //F
  {0x05,0x05,0x05,0x6A}, //G
  {0x04,0x04,0x04,0x6B}, //H
  {0x22,0x22,0x22,0x53}, //I
  {0x26,0x26,0x26,0x54}, //J
  {0x28,0x28,0x28,0x55}, //K
  {0x25,0x25,0x25,0x59}, //L
  {0x2E,0x2E,0x2B,0x58}, //M
  {0x2D,0x2D,0x2E,0x6F}, //N
  {0x1F,0x1F,0x1F,0x5F}, //O
  {0x23,0x23,0x23,0x44}, //P
  {0x0C,0x0C,0x0C,0x75}, //Q
  {0x0F,0x0F,0x0F,0x65}, //R
  {0x01,0x01,0x01,0x76}, //S
  {0x10,0x10,0x10,0x66}, //T
  {0x20,0x20,0x20,0x52}, //U
  {0x09,0x09,0x0B,0x6C}, //V
  {0x0D,0x0D,0x0D,0x77}, //W
  {0x07,0x07,0x08,0x7A}, //X
  {0x11,0x11,0x11,0x67}, //Y
  {0x06,0x06,0x07,0x79}, //Z
  {0x32,0x32,0x24,0x68}, //TILDE
  {0x1B,0x1B,0x1B,0x40}, //MINUS
  {0x18,0x18,0x18,0x41}, //EQUAL
  {0x33,0x33,0x33,0x45}, //BACKSPACE
  {0x30,0x30,0x30,0x78}, //TAB
  {0x21,0x21,0x21,0x56}, //OPEN_BRACKET
  {0x1E,0x1E,0x1E,0x57}, //CLOSE_BRACKET
  {0x39,0x39,0x39,0x7D}, //CAPSLOCK
  {0x29,0x29,0x29,0x5A}, //SEMICOLON
  {0x27,0x27,0x27,0x5B}, //QUOTE
  {0x24,0x24,0x2A,0x48}, //RETURN
  {0x38,0x38,0x38,0x7E}, //SHIFT
  {0x2B,0x2B,0x2F,0x5D}, //COMMA
  {0x2F,0x2F,0x2C,0x5E}, //PERIOD
  {0x2C,0x2C,0x0A,0x4C}, //SLASH
  {0x3A,0x3A,0x3A,0x7C}, //OPTION
  {0x37,0x37,0x37,0x7F}, //COMMAND
  {0x31,0x31,0x34,0x5C}, //SPACE
  {0x2A,0x2A,0x06,0x42}, //BACKSLASH
  {0x4C,0x34,0x31,0x46}, //NUM_ENTER
  {0x52,0x52,0x52,0x49}, //NUM_0
  {0x53,0x53,0x53,0x4D}, //NUM_1
  {0x54,0x54,0x54,0x2D}, //NUM_2
  {0x55,0x55,0x55,0x2E}, //NUM_3
  {0x56,0x56,0x56,0x28}, //NUM_4
  {0x57,0x57,0x57,0x29}, //NUM_5
  {0x58,0x58,0x58,0x2A}, //NUM_6
  {0x59,0x59,0x59,0x24}, //NUM_7
  {0x5B,0x5B,0x5B,0x25}, //NUM_8
  {0x5C,0x5C,0x5C,0x26}, //NUM_9
  {0x47,0x47,0x47,0x20}, //NUM_CLEAR
  {0x66,0x48,0x48,0x2B}, //NUM_PLUS or NUM_COMMA
  {0x4C,0x4C,0x4C,0x2F}, //NUM_ENTER
  {0x68,0x4E,0x4E,0x21}, //NUM_EQUAL or NUM_MINUS
  {0x62,0x42,0x42,0x23}, //NUM_MULTIPLY
  {0x41,0x41,0x41,0x2C}, //NUM_PERIOD
  {0x6D,0x46,0x46,0x22}, //NUM_SLASH or NUM_PLUS
  {0x4E,0x4D,0x4D,0x27}, //NUM_MINUS or NUM_SLASH
  {0x7B,0x7B,0x32,0x68}, //SECTION or TILDE
  {0x7B,0x7B,0x7B,0x43}, //<> - DOES NOT EXIST?
  {0x4D,0x7B,0x7B,0x27}, //ARROW_UP or NUM_SLASH
  {0x46,0x7B,0x7B,0x22}, //ARROW_LEFT or NUM_PLUS
  {0x42,0x7B,0x7B,0x23}, //ARROW_RIGHT or NUM_MULTIPLY
  {0x48,0x7B,0x7B,0x2B}  //ARROW_DOWN or NUM_COMMA
};

//Convert scancodes from the Mac keyboard to Lisa scancodes
uint8_t translate_mac_to_lisa(uint8_t scancode, uint8_t keymap) {
  for (uint8_t i = 0; i < lookup_table_rows; i++) {
    if (pgm_read_byte(&scancode_lookup_table[i][keymap]) == scancode) {
      return pgm_read_byte(&scancode_lookup_table[i][keymap_lisa_us]);
    }
  }    
}

/*
Scancode buffer - this is required for filtering out a handful of keys' release codes. For example:

M0110A
------------------------
KEY PRESSED:    0x68 (=)
FRONT PORCH?    0xC8
KEY RELEASED:   0xE8
BACK PORCH?     0xB8

We cannot simply ignore 0xC8 because, while garbage here, 0xC8 also happens to be the release code for "," on the both 
the M0110A's number pad and the M0120. As a result, we need to buffer the relevant release codes to verify if the next 
value sent across the wire is the ACTUAL release code, then drop the two values bookending it. For scancodes that have
only two release values returned, we only need to drop the next releae code returned.
*/

/*
M0110/A Keypresses where multiple scancodes are returned for key releases:

M0110 + M0120
--------------------
Keypress (Character):   46 (+<)     42 (*>)     4D (/^)     48 (,v)
Key Release Sequence:   C6          C2          CD          C8
                        E6          E2          ED          E8

M0110A
--------------------
Keypress (Character):   46 (+<)     42 (*>)     4D (/^)     48 (,v)     68 (=)      6D (/)      62 (*)      66 (+)
Key Release Sequence:   C6          C2          CD          C8          C8          CD          C2          C6
                        E6          E2          ED          E8          E8          ED          E2          E6
                                                                        B8          BD          B2          B6
*/

//Buffer for key release sequence handling
uint8_t multi_release_buffer[2];

bool check_keyrelease_for_multi_release(uint8_t scancode) {
   
  uint8_t intercepted_mac_key = 0x00;
  uint8_t intercepted_mac_key_buffer = 0x00;

  if (((scancode == 0xC2) || (scancode == 0xC6) || (scancode == 0xC8) || (scancode == 0xCD))) {
    intercepted_mac_key = m0110_recv_key();
    if ((intercepted_mac_key == 0xE2) || (intercepted_mac_key == 0xE6) || (intercepted_mac_key == 0xE8) || (intercepted_mac_key == 0xED)) {
      intercepted_mac_key_buffer = intercepted_mac_key;
      intercepted_mac_key = m0110_recv_key();
      if ((intercepted_mac_key == 0xB2) || (intercepted_mac_key == 0xB6) || (intercepted_mac_key == 0xB8) || (intercepted_mac_key == 0xBD)) {
        multi_release_buffer[0] = intercepted_mac_key_buffer;
        multi_release_buffer[1] = 0x7B;
        return true;
      } else {
        multi_release_buffer[0] = scancode;
        multi_release_buffer[1] = intercepted_mac_key;
        return true;
      }
    } else {
      return false;
    }
  } else {
    return false;
  }
}
