//These settings have been modified from their originals in the LisaKeys project
#ifndef LISAKEYSCONFIG_H
#define LISAKEYSCONFIG_H

// Arduino Pro Micro pin PD4 for Lisa keyboard data communications
#define LK_DATA_DDR  DDRD
#define LK_DATA_PORT PORTD
#define LK_DATA_PIN  PIND
#define LK_DATA_MASK 0x10

//Arduino Pro Micro pins for jumper settings
#define MOD_BUTTON        10
#define DE_FR_SWITCH      11
#define US_UK_SWITCH      12

#endif