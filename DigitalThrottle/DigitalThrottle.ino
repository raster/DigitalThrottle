/*
 * DigitalThrottle.ino
 * 
 * An interface for the Leadrise Motor Controller which allows the use
 * of 0-5V throttles instead of requiring (more expensive) 5K throttles.
 * 
 * We use a Microchip Technologies MCP4131-104E/P Digital Potentiometer
 * controlled by an Arduino to emulate the resistive throttle.
 * 
 * 
 * Pete Prodoehl <pete@2xlnetworks.com>
 * 
 */


#include <SPI.h>


byte address = 0x00;
int CS = 10;
int throttlePin = 0;
int throttleVal = 0;
int resistVal = 0;

int LEDpin = 2;

int debug = 1;

void setup() {
  pinMode(CS, OUTPUT);
  SPI.begin();
  
  if (debug > 0) {
    Serial.begin(9600);
  }
  pinMode(LEDpin, OUTPUT);
  digitalWrite(LEDpin, HIGH);
}

void loop() {
  
  throttleVal = analogRead(throttlePin);
  resistVal = constrain(map(throttleVal, 500, 700, 0, 255), 0, 255);
  digitalPotWrite(resistVal);

  if (debug > 0) {
    Serial.print(throttleVal);
    Serial.print("\t");
    Serial.println(resistVal);
  }

}

int digitalPotWrite(int value) {
  digitalWrite(CS, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);
}



