/*

Copyright 2011, 2012 Jun Wako <wakojun@gmail.com>

This software is licensed with a Modified BSD License.
All of this is supposed to be Free Software, Open Source, DFSG-free,
GPL-compatible, and OK to use in both free and proprietary applications.
Additions and corrections to this file are welcome.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in
  the documentation and/or other materials provided with the
  distribution.

* Neither the name of the copyright holders nor the names of
  contributors may be used to endorse or promote products derived
  from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

Modifications for use with RebeccaRGB's LisaKeys project contributed by warmech@github

*/

#ifndef M0110_H
#define M0110_H

/*

The definitions for M0110_CLOCK_BIT and M0110_DATA_BIT have been removed from 
this header file and now exist in the m0110.cpp as variables. This is to allow 
the user to set whether they are using a normal Macintosh keyboard cable (less 
common) or a standard handset cable (much more easily obtained). A Mac cable 
is straight-through, whereas a 4P4C handset cable is effectively a crossover 
cable and flips the pins on either end. This feature enables the user to flip 
the order of the four pins that power and communicate with the Mac keyboard 
and so allow someone to use either a Mac cable or a handset cable.

*/


//Arduino Pro Micro pins PD1 (Clock) and PD0 (Data) - MODIFIED
#define M0110_CLOCK_PORT    PORTD
#define M0110_CLOCK_PIN     PIND
#define M0110_CLOCK_DDR     DDRD
//#define M0110_CLOCK_BIT     1
#define M0110_DATA_PORT     PORTD
#define M0110_DATA_PIN      PIND
#define M0110_DATA_DDR      DDRD
//#define M0110_DATA_BIT      0

//Arduino Pro Micro pin for setting keyboard cable type: Mac (straight-through) or telephone handset (crossover); uses digital pin 6 - NEW
#define M0110_CABLE_TYPE     6

//Keyboard Commands - the M0110/A must be asked politely what key is being pressed
#define M0110_INQUIRY       0x10
#define M0110_INSTANT       0x14
#define M0110_MODEL         0x16
#define M0110_TEST          0x36

//Keyboard Responses (each is the raw byte received from M0110/A)
#define M0110_NULL          0x7B
#define M0110_KEYPAD        0x79
#define M0110_TEST_ACK      0x7D
#define M0110_TEST_NAK      0x77
#define M0110_SHIFT         0x71
#define M0110_ARROW_UP      0x1B
#define M0110_ARROW_DOWN    0x11
#define M0110_ARROW_LEFT    0x0D
#define M0110_ARROW_RIGHT   0x05

//No response from keyboard
#define M0110_ERROR         0xFF

//Scan code offset for keypad and arrow keys
#define M0110_KEYPAD_OFFSET 0x40
#define M0110_CALC_OFFSET   0x60

//Error variable declaration
extern uint8_t m0110_error;

//Declare function prototypes - NEW
uint8_t m0110_init(void);
uint8_t m0110_send(uint8_t data);
uint8_t m0110_recv(void);
uint8_t m0110_recv_key(void);
uint8_t m0110_inquiry(void);
uint8_t m0110_instant(void);
char * m0110_identify_keyboard(uint8_t m0110_model);
void determine_keyboard_cable();

#endif
