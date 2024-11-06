# Arduino Traffic Light Project

Dette projekt implementerer et trafiklys på en Arduino (ATmega328P) med seks uafhængige lysdioder for to retninger: Nord-Syd og Øst-Vest. Programmet er skrevet i ren C uden brug af `#include`-biblioteker og konfigurerer seks pins som output, der styrer lysdiodernes farver (Rød, Gul, Grøn) for de to retninger.

## Hardware Konfiguration

- **Nord-Syd lysdioder**:
  - **NS_RED**: Tilsluttes Port D, Pin 2
  - **NS_YELLOW**: Tilsluttes Port D, Pin 3
  - **NS_GREEN**: Tilsluttes Port D, Pin 4
- **Øst-Vest lysdioder**:
  - **EW_RED**: Tilsluttes Port D, Pin 5
  - **EW_YELLOW**: Tilsluttes Port D, Pin 6
  - **EW_GREEN**: Tilsluttes Port D, Pin 7

Koden sikrer, at der ikke vises grønt eller gult lys i begge retninger samtidig, selvom rødt lys kan være tændt i begge retninger.

## Kompilering og Upload Instruktioner

Følg nedenstående trin for at kompilere koden og uploade den til din Arduino.

### 1. Find korrekt USB-port

Inden du uploader koden til din Arduino, skal du finde hvilken USB-port, din Arduino er forbundet til. Åbn terminalen og kør:

```bash
ls /dev/tty*
```
Se efter en port med navnet /dev/tty.usbserial-XXXX eller tilsvarende. Notér denne port, da den skal bruges i upload-kommandoen nedenfor.

### 2. Kompiler koden
Kompiler koden til en .elf-fil med følgende kommando:

```bash
avr-gcc -mmcu=atmega328p -Os -o trafficlight.elf trafficlight.c
```

### 3. Konverter til HEX-format
Konverter .elf-filen til .hex, som er nødvendig for at uploade til Arduino:

```bash
avr-objcopy -O ihex trafficlight.elf trafficlight.hex
```

### 4. Upload til arduino
Endelig kan du bruge avrdude til at uploade .hex-filen til din Arduino. Indsæt USB-porten, du fandt i trin 1, i kommandoen nedenfor:

```bash
avrdude -p m328p -c arduino -P /dev/tty.DINUSBPORT -U flash:w:trafficlight.hex:i
```
