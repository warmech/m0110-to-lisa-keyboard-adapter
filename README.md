# M0110/A to Lisa 2 Keyboard Adapter

This project aims to offer an inexpensive and open-source method for using M0110/A keyboards with the Apple Lisa 2; as the M0110/A line of keyboards is functionally and aesthetically similar to the Lisa's keyboard, this seemed a good fit. Additionally, as Lisa keyboards have become obscenely expensive, this offers a much more affordable option to those who have Lisas but do not wish to spend the kind of money that original keyboards now command.

This adapter will allow an M0110A all-in-one keyboard or M0110 with accompanying M0120 number pad to function as a Lisa keyboard. The suggested configuration is to use an M0110A for the following reasons:

- this configuration more closely resembles an original Lisa keyboard than the M0110/M0120 combination, and 
- the M0110A is a bit easier to come by than M0120s by themselves (which are required if using an M0110).

Further, the Lisa keyboard's number pad has five keys that an M0110 alone does not provide (which is why the M0120 is required if using an M0110): four arrow keys and the clear key. If, for instance, you plan on using Tom Stepleton's hard disk bootloader for emulated ProFiles, the four arrow keys are required to operate the interface and you will not be able to boot to anything other than the bootloader image itself.

This tool was designed to be as cost-effective as possible and, as such, makes use of as many off-the-shelf and generally available components as possible. The PCB measures approximately 1.5" x 2.3" (38mm x 58mm), which should allow fabrication through even OSHPark to be relatively inexpensive. The BOM for the adapter is as follows:

- 1 - Arduino Pro Micro, 5V/16MHz (any brand should work fine)
- 1 - 1/4" Stereo Phone Connector - Neutrik, Part No. NRJ6HM-1 ([Mouser](https://www.mouser.com/ProductDetail/568-NRJ6HM1))
- 1 - RJ9 4P4C Modular Telephone Jack - Amphenol, Part No. 66010-004LF ([Mouser](https://www.mouser.com/ProductDetail/649-66010-004LF))
- 2 - Right-Angle Tact Switch - CUI, Part No. TS11-674-73-BK-260-RA-D ([Mouser](https://www.mouser.com/ProductDetail/179-TS1167473260RAD))
- 1 - On-On DPDT Switch, Non-Shorting - C&K, Part No. OS202013MT5QN1 ([Mouser](https://www.mouser.com/ProductDetail/611-OS202013MT5QN1))
- 1 - DIP Switch, 3 Position - Wurth Elektronik, Part No. 418117270903 ([Mouser](https://www.mouser.com/ProductDetail/710-418117270903))

A 3D-printed case is currently in development; when finished, STL and project files will be available in the "case" directory.

## Function

The adapter has three modes of operation: adapter mode, serial input mode, and keyboard test mode.

### Adapter Mode

Adapter Mode takes input from an M0110/A keyboard via the RJ9 connector and outputs Lisa ketstrokes via the 1/4" stereo phone jack. To use this mode, first ensure that the Lisa is powered off prior to continuing. Do not connect or disconnect either end of the 1/4" stereo cable to/from the Lisa or adapter while the Lisa is powered on, as you may damage the Lisa and/or the adapter. 

First, connect your M0110/A keyboard to the RJ9 jack; you may use either a Macintosh keyboard cable or a standard 4P4C handset cable. To toggle between cables types, use the DPDT switch on the corner adjacent to the RJ9 connector to select either MAC (for original Macintosh cables) or HANDSET (for off-the-shelf telephone handset cables). If using a handset cable, also be sure to set DIP switch 3 to ON; this will tell the MCU to flip the pins used for Macintosh keyboard clock and data, just as the DPDT flips the power and ground connections. (NOTE: DO NOT TOGGLE THE DPDT SWITCH OR SWAP MACINTOSH KEYBOARD CABLES WHILE THE ADAPTER IS POWERED ON; THE +5V RAIL WILL BE SHORTED TO GROUND AND THE LISA'S PSU WILL GO INTO SHUTDOWN. THIS MAY POTENTIALLY DAMAGE THE M0110/A, THE ADAPTER, AND/OR THE LISA.)

Second, while the Lisa is off connect the adapter to the Lisa by use of a stereo 1/4" cable. For strain relief on the Lisa's input connector, it is recommended to use a cable with at least one right-angle male connector such as this one ([Amazon](https://www.amazon.com/dp/B09NSHKKJR)), for example.

Third, determine what nationality your keyboard needs to present itself as. This is done by setting DIP swiches 1 and 2 on the adapter according to the table printed on the PCB. The default configuration is 1 and 2 both OFF, instructing the adapter to tell the Lisa it is a US keyboard.

Lastly, power on your Lisa. Once the boot sequence completes, you will now be able to interact with your Lisa via the M0110/A.

NOTE: As the M0110A has distinct arrow keys and a different button arrangement on the number pad than does the Lisa or M0120, the arrow keys have been remapped to transmit the Lisa scancodes for the arrow keys on the Lisa and M0120. Additionally, the M0110A's number pad transmits the Lisa scancodes for the symbols on the M0110A's number pad keys. For example, the plus (+) key on the M0110A is a comma (,) and down arrow on the Lisa; in this case, pressing the plus key on the M0110A will transmit a plus scancode to the Lisa and NOT a comma/down arrow scancode.

NOTE: The difference between a Macintosh keyboard cable and a handset cable is that a Macintosh cable is straight-through whereas a handset cable behaves more like a crossover cable, flipping the connections at each end. While using the wrong cable with a Macintosh itself won't damage the keyboard or Mac (see [Mac Gui](https://macgui.com/news/article.php?t=440)), the keyboard will not work as you will have created a short from the +5V line to ground. Using the incorrect cable and switch settings with this adapter prior to powering on the Lisa is likely to prevent the Lisa from powering on at all, since a short on the +5V rail will be detected by the PSU and prevent it from escaping shutdown via the PSU's crowbar circuit.

### Serial Input Mode

Serial Input Mode allows a user to connect both an M0110/A to a Lisa, as well as enable input over serial; this is primarily aimed at allowing users to load bootloaders (such as BLU) or DC42 images into RAM when in the Lisa's service mode.

First, begin by following the steps listed under the Adapter Mode section.

Second, once the Lisa is powered up, connect the adapter to a computer via the USB port. 

Third, once the adapter is connected via USB, you may use either the Arduino IDE's serial monitor or a dedicated serial console (such as PuTTY or the built-in terminals in MacOS or Linux) set to 9600 baud in order to interact with the adapter.

Fourth, press the mode button (the tact switch closest to the RJ9 connector) once to enter the serial input mode. You should see the words "Serial Communications Mode" appear in the terminal.

At this point, you may either directly interact with the Lisa via manual serial input or, as this mode is more inteded for, use the included Python script from RebeccaRGS's LisaKeys project (see tools directory) to write whole files into RAM using the Lisa's service mode. The tools directory also has a brief explanation on how to use the serial input mode for dedicated user input.

### Keyboard Test Mode

Keyboard Test Mode allows a user to attach an M0110/A and/or Lisa keyboard to the adapter and, via a serial console, view the scancode output for any pressed key.

First ensure that the adapter is not powered on by disconnecting it from USB and/or the Lisa. 

Second, connect the keyboards you wish to test to the adapter; both an M0110/A series keyboard and a Lisa keyboard may be attached at the same time.

Third, connect the adapter to a computer via USB to power it up. Once powered on, you may use either the Arduino IDE's serial monitor or a dedicated serial console (such as PuTTY or the built-in terminals in MacOS or Linux) set to 9600 baud in order to view output from the adapter.

Fourth, press the mode button (the tact switch closest to the RJ9 connector) twice to enter the test mode. You should see in the serial monitor the words "Serial Communications Mode" appear after the first press, followed by "Keyboard Test Mode" after the second press. 

Lastly, once the "Keyboard Test Mode" message appears, the adapter will attempt to identify whether a Mac or Lisa keyboard (or both) is attached. If one or both are attched and subsequently detected, the adapter will also indicate the type of keyboard and the region it is from (region is a Lisa-only feature at the present time). Keymaps and scancode listings may be found in the documentation (docs) folder.

## Hardware

Under the hardware directory, you will find a subdirectory (gerbers) containing Gerber files and a subdirectory (schematics) containing project files. This project was assembled in EasyEDA but it has been exported in both EasyEDA and Altium formats; Altium exports from EasyEDA are experimental at this time and no guarantee is made as to their functionality. As of the date of publishing this repository, the per-unit cost for assembling one complete adapter (including the per-PCB fabrication cost) is less than $20 USD.

## Attributions

Credit is due to the following parties:

### RebeccaRGB - [LisaKeys](https://github.com/RebeccaRGB/lisakeys)

Rebecca's LisaKeys libraries function as the software backbone of this project, providing the majority of its functionality. Libraries from LisaKeys have been slightly retooled here to remove unnecessary code and have had some updates made to integrate the use of M0110/A keyboards. The following components have been removed wholesale due to their being made unnecessary or in order to reduce the resource footprint on the MCU:

- keypadconfig.h
- keypadlib.cpp
- keypadlib.h
- usbkeysconfig.h
- usbkeyslib.cpp
- usbkeyslib.h

Additional functions, macros, and/or variables in other files which are directly or solely responsible for keypad or USB functionality have also been removed. Elements added to remaining libraries or elements in those libraries that have been modified or updated have been indicated as such. Tremendous thanks goes to Rebecca for her work in developing and implementing a means for utilizing the Lisa's keyboard protocol; none of this would have been possible without her work.

### Jun Wako - [TMK Keyboard Firmware Collection](https://github.com/tmk/tmk_keyboard)

Jun Wako provided an implementation of the M0110 and M0120 keyboard protocol to the TMK firmware project (subsequent support for the M0110A added by GitHub user Skagon, for whom I have been unable to locate a profile). This protocol has provided valuable insight into how the M0110/A series of keyboards work and has been used here with minimal modification; as with LisaKeys, any additions, changes, or updates have been noted in the m0110.cpp and m0110.h files.

## License

Original works, Copyright © 2023 warmech

Except where licensing is otherwise noted below and/or in project files, this work is free. You can redistribute it and/or modify it under the terms of the Do What The F*** You Want To Public License, Version 2, as published by Sam Hocevar. See the COPYING file for more details.

Works excepted from the WTFPL license in this project:

- Jun Wako's M0110 protocol libraries - Modified BSD; stated as such under m0110.cpp and m0110.h
- RebeccaRGB's LisaKeys libraries - Unknown/None Stated; other works by the author have been licensed under the CCPL, so we will treat these libraries as residing under Creative Commons until otherwise advised