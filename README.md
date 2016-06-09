# LoraLCD
Arduino based LoRa Transmitter and Receiver with LCD

This example is based on Dr. Pham work http://cpham.perso.univ-pau.fr/LORA/RPIgateway.html and and uses NiceRF LoRa modules available on Aliexpress. 

The library and examples were modified for the 915 MHz ISM band. Ask NiceRF to provide the LoRa modules with the correct frequency for you country.

The diagram of Arduino Pro Mini connection and pictures of the prototype are included.

The LoRa modules must be connected with a 3.3V power source and the current is up to 200 mA for 20 dBm TX power. In this prototype, all the modules (LoRa , Arduino Pro (5V version)  and SPI LCD (5V version)) were connected in a 3.6 V LiPo battery. If you use a Arduino Nano, connect the LoRa module in the 3.3V pin available on Arduino and the rest on the 5V power supply.

In this prototype a 20x4 SPI LCD module was used to save some digital pins.

The LoRA module TXEN and RXEN pins are connected to Arduino digital (5 and 6) pins, but they can be connected to VCC using 10k pull-up resistors if you don't want control RX and TX and save two pins.

Arduino PRO ----- LoRa NiceRF

 GND -----------------   GND

 D6  -----------------   TXEN

 D5  -----------------   RXEN

 D13 -----------------   SCK

 D12 -----------------   MISO

 D11 -----------------   MOSI

 D10 -----------------   MSS

 NC  -----------------   DIO2

 NC  -----------------   DIO1

 D9  -----------------   DIO0

 VCC (3.3V)-----------   VCC

 D8  -----------------   MRESET

 A4  -----------------   LCD SPI SDA
 
 A5 ------------------   LCD SPI SCL

