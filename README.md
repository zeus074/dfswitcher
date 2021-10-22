# dfswitcher
Amiga 500 DF selector

This card allows to automatically exchange the boot between internal floppy and an external floppy.
You need to reset the Amiga twice within 2 seconds to switch from internal / external df0 mode.
The state of the switch will be maintained even when the machine is turned off.

![alt text](https://github.com/zeus074/dfswitcher/blob/main/IMG/dfswitcher.jpg)

**Components:**
U1		ATTINY25 (SOIC8)
U2		CD4066 (SOP14)
U4		SOCKET 40 PIN (DIP40) TULIP
R1,R2	10Kohm (0805)
R3		560ohm (0805 OPTIONAL)
C1,C2	100nF (0805)
J3,J4	HEADER MALE-MALE TURNED

**Directory**
Gerber : File for make the PCB
IMG : Tester's pictures
Firmware : Firmware for Attiny25 (you can use avr commands like Arduino's IDE or an AVR programmer to write the HEX file)
Fuse (Extend: FF . High: DF . LOW: 52)

**How it works**
Use Ctrl-Alt-Amiga to switch between df0 internal/external.
You need to do two resets within two seconds to change modes
The buzer emits a beep in normal mode, two beeps in inverted mode
Compatible with Amiga 500,1000,2000

**How to burn the firmware**
You can use avrdude integrated on arduino via command line, or simply download a gui (if you use windows) like AVRDUDESS.
I use Atmel ICE with Microchip Studio.
