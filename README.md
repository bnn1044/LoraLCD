# LoraLCD
Arduino based LoRa Transmitter and Receiver with LCD

This example is based on Dr. Pham work http://cpham.perso.univ-pau.fr/LORA/RPIgateway.html and and uses NiceRF LoRa modules available on Aliexpress. 

The library and examples were modified for the 915 MHz ISM band. Ask NiceRF to provide the LoRa modules with the correct frequency for you country.

The diagram of Arduino Pro Mini connection and pictures of the prototype are included.

The LoRa modules must be connected with a 3.3V power source and the current is up to 200 mA for 20 dBm TX power. In this prototype, all the modules (LoRa , Arduino Pro (5V version)  and SPI LCD (5V version)) were connected in a 3.6 V LiPo battery. If you use a Arduino Nano, connect the LoRa module in the 3.3V pin available on Arduino and the rest on the 5V power supply.

In this prototype was used a 20x4 SPI LCD module was used to save some digital pins.

If you want more pins, the LoRA module TXEN and RXEN pins are connected to Arduino digital pins, but they can be connected to VCC using 10k pull-up resistors if you don't want disable RX and TX.

