/*
Telemedicine system code for Arduino
Created by Prajwal Sankar
 */


#include <GPRS_Shield_Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define PIN_TX    7
#define PIN_RX    8
#define BAUDRATE  9600
#define PHONE_NUMBER "+16466232422"
#define MESSAGE  "Temperature and Alcohol level is critical, urgent attention required !!!"

const int AOUTpin=0;//the AOUT pin of the alcohol sensor goes into analog pin A0 of the arduino
const int DOUTpin=6;//the DOUT pin of the alcohol sensor goes into digital pin D8 of the arduino
const int ledPin=13;//the anode of the LED connects to digital pin D13 of the arduino

int limit;
int value;
int val;
int tempPin = 1;

GPRS gprsTest(PIN_TX,PIN_RX,BAUDRATE);//RX,TX,BaudRate

void setup() {
/*Temperature sensor */
val = analogRead(tempPin);
float mv = ( 5*val*(100/1024.0)); 
float cel = mv/10;
float farh = (cel*9)/5 + 32;

Serial.print("TEMPRATURE = ");
Serial.print(farh);
Serial.print("*F");
Serial.println();

/* Gas Sensor */
Serial.begin(115200);//sets the baud rate
pinMode(DOUTpin, INPUT);//sets the pin as an input to the arduino
pinMode(ledPin, OUTPUT);//sets the pin as an output of the arduino

  value= analogRead(AOUTpin);//reads the analaog value from the alcohol sensor's AOUT pin
limit= digitalRead(DOUTpin);//reads the digital value from the alcohol sensor's DOUT pin
      Serial.println("Body Temperature=");
      Serial.println(farh);
      Serial.println("Alcohol Level=");
      Serial.println(value);
      
/*GSM Section */
  Serial.begin(9600);
  while(!gprsTest.init()) {
      delay(1000);
      Serial.print("init error\r\n");
  }  
  Serial.println("gprs init success");

  if((farh>=100.0)||(value>=120))
  {
  gprsTest.sendSMS(PHONE_NUMBER,MESSAGE); //define phone number and text
gprsTest.callUp(PHONE_NUMBER);
  }
 
}

void loop() {
  //nothing to do
}
