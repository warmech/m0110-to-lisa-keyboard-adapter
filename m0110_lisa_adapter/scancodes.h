//This library created by warmech (GitHub/68KMLA/TinkerDifferent/LisaList2) under the WTFPL license.
//See the "copying" file in license directory for licensing details. For all intents and purposes,
//this is to be considered public domain.
#ifndef SCANCODES_H
#define SCANCODES_H

//Keymap info
extern uint8_t keymap_m0110a;
extern uint8_t keymap_m0110;
extern uint8_t keymap_m0110_intl;
extern uint8_t keymap_lisa_us;
extern uint8_t lookup_table_rows;
extern uint8_t lookup_table_cols;

//Key release sequence hadling buffer
extern uint8_t multi_release_buffer[2];

//Keymap lookup table
extern const uint8_t scancode_lookup_table[80][4] PROGMEM;

//Scancode and character name lookup
uint8_t translate_mac_to_lisa(uint8_t scancode, uint8_t keymap);
const char * mac_key_name(uint8_t mac_scancode, int mac_keyboard_model);

//Handle key releases with multiple codes sent back by the keyboard
bool check_keyrelease_for_multi_release(uint8_t scancode);

#endif