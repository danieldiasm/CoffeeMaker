/*
* Coffee Maker - Firmware Version 1.0A
* Created on: 06 Jul 2019
* Last Version: Ver 1.0 - 06 Jul 2019
* 
* Pins:
* Pin 02 - Buzzer
* Pin 03 - LED Green
* Pin 04 - LED Yellow
* Pin 05 - LED Red
* Pin 06 - Coil Relay
* Pin 07 - Button 01
*/

//LEDs Pin Setup
const byte LED_Green  = 3;
const byte LED_Yellow = 4;
const byte LED_Red    = 5;
//Actuators Pin Setup
const byte Coil_01    = 6;
//Controls and Buttons Pin Setup
const byte Btn_01     = 7;

//Variables
byte Btn_01Read;

void setup() {
  //LEDs
  pinMode(LED_Green,  OUTPUT);
  pinMode(LED_Yellow, OUTPUT);
  pinMode(LED_Red,    OUTPUT);
  //Actuators
  pinMode(Coil_01, OUTPUT);
  //Controls and Buttons
  pinMode(Btn_01,  INPUT);
}

void loop() {
  Btn_01Read = digitalRead(Btn_01);
  
  if (Btn_01Read == HIGH){
    digitalWrite(Coil_01, HIGH);
  } else {
    digitalWrite(Coil_01, LOW);
  }

}
