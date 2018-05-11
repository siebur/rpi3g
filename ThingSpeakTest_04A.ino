/*
  "WriteVoltage" minimal from 1.3.3 lib  
 ThingSpeak ( https://www.thingspeak.com ) 
############################################################################################################################################  
*/
#include "ThingSpeak.h"
#define USE_ETHERNET_SHIELD

#include <SPI.h>
#include <Ethernet.h>
byte mac[] = { 0x00, 0x44, 0x22, 0x33, 0x11, 0xFF};
EthernetClient client;
#define ARDUINO_ARCH_AVR
#define VOLTAGE_MAX 5.0
#define VOLTAGE_MAXCOUNTS 1023.0
unsigned long myChannelNumber = "XXXXXX";
const char * myWriteAPIKey = "ABCDEFGHIJKLMNOP";

void setup() {

  Ethernet.begin(mac);
  ThingSpeak.begin(client);
}

void loop() {
  
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (VOLTAGE_MAX / VOLTAGE_MAXCOUNTS);
  ThingSpeak.writeField(myChannelNumber, 1, voltage, myWriteAPIKey);
  delay(20000);  
}
