/*  
 *  LoRa 868 / 915MHz SX1272 LoRa module
 *  
 *  Copyright (C) Libelium Comunicaciones Distribuidas S.L. 
 *  http://www.libelium.com 
 *  
 *  This program is free software: you can redistribute it and/or modify 
 *  it under the terms of the GNU General Public License as published by 
 *  the Free Software Foundation, either version 3 of the License, or 
 *  (at your option) any later version. 
 *  
 *  This program is distributed in the hope that it will be useful, 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License 
 *  along with this program.  If not, see http://www.gnu.org/licenses/. 
 *  
 *  Version:           1.1
 *  Design:            David Gascón 
 *  Implementation:    Covadonga Albiñana & Victor Boria
 */

// Include the SX1272 and SPI library:
#include "SX1272.h"
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define RADIO_INAIR9B
#define BAND900

LiquidCrystal_I2C  lcd(0x3F-0,2,1,0,4,5,6,7); // 0x27 is the I2C bus address for an unmodified backpack
int e;
char my_packet[100];
int led = 7 ;
int txen_pin=6;
int rxen_pin=5;
boolean led_state = LOW;
void setup()
{
  pinMode(txen_pin, OUTPUT);
  pinMode(rxen_pin, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(txen_pin, HIGH);
  digitalWrite(rxen_pin, HIGH);
  lcd.begin(20,4); // for 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  Wire.begin(); 
  lcd.setCursor(0, 0);
  lcd.print ("Inicio");

  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  // Print a start message
  Serial.println(F("SX1272 module and Arduino: receive packets without ACK"));

  // Power ON the module
  e = sx1272.ON();
  Serial.print(F("Setting power ON: state "));
  Serial.println(e, DEC);
  
  // Set transmission mode and print the result
  e = sx1272.setMode(4);
  Serial.print(F("Setting Mode: state "));
  Serial.println(e, DEC);
  
  // Set header
  e = sx1272.setHeaderON();
  Serial.print(F("Setting Header ON: state "));
  Serial.println(e, DEC);
  
  // Select frequency channel
  e = sx1272.setChannel(CH_05_900);
  Serial.print(F("Setting Channel: state "));
  Serial.println(e, DEC);
  
  // Set CRC
  e = sx1272.setCRC_ON();
  Serial.print(F("Setting CRC ON: state "));
  Serial.println(e, DEC);
  
  // Select output power (Max, High or Low)
  e = sx1272.setPower('x');
  Serial.print(F("Setting Power: state "));
  Serial.println(e, DEC);
  
  // Set the node address and print the result
  e = sx1272.setNodeAddress(8);
  Serial.print(F("Setting node address: state "));
  Serial.println(e, DEC);
  
  // Print a success message
  Serial.println(F("SX1272 successfully configured"));
  Serial.println();
}

void loop(void)
{
  // Receive message
  e = sx1272.receivePacketTimeout(10000);
  if ( e == 0 )
  {
    Serial.print(F("Receive packet, state "));
    Serial.println(e, DEC);

    for (unsigned int i = 0; i < sx1272.packet_received.length; i++)
    {
      my_packet[i] = (char)sx1272.packet_received.data[i];
    }
    Serial.print(F("Message: "));
    Serial.println(my_packet);
    lcd.setCursor(0, 1);
    lcd.print("Message: ");
    lcd.print(my_packet);
    led_state = !led_state ;  
    digitalWrite(led, led_state);  // toggle the led state
    
    sx1272.getRSSIpacket();
    sx1272.getSNR();
    Serial.print("Console: RSSI is ");
    Serial.print(sx1272._RSSIpacket,DEC); 
    Serial.print(" dBm");
    Serial.println(" ");
    lcd.setCursor(0, 0);
    lcd.print("RSSI:");
    lcd.print(sx1272._RSSIpacket,DEC);
    lcd.print("dBm ");   
    Serial.print("Console: SNR is ");
    Serial.print(sx1272._SNR,DEC); 
    Serial.println(" dBm");
    lcd.print("SNR:");
    lcd.print(sx1272._SNR,DEC);   
    lcd.print(" ");
  }
  else {
    Serial.print(F("Receive packet, state "));
    Serial.println(e, DEC);
  }
}
