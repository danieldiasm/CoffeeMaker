#include <SoftwareSerial.h>
#include "DFRobotDFPlayerMini.h"
/*
 Coffee Maker - Firmware Version 1.0A
 Created on: 06 Jul 2019
 Last Version: Ver 1.0 - 06 Jul 2019
 
 Pins:
 Pin 02 - Buzzer
 Pin 03 - LED Green
 Pin 04 - LED Yellow
 Pin 05 - LED Red
 Pin 06 - Coil Relay
 Pin 07 - Button 01
*/
SoftwareSerial DFSoftSerial(10, 11); // RX, TX
DFRobotDFPlayerMini DFPlayer;
//LEDs Pin Setup
//(Must be PWM capable pins, due to fade effects)
const byte LED_Green  = 3;
const byte LED_Yellow = 9;
const byte LED_Red    = 5;
//Actuators Pin Setup
const byte Coil_01    = 6;
const byte Buzzer     = 2;
//Controls and Buttons Pin Setup
const byte Btn_01     = 7;

////////Variables
//Button state variable and last status checker
bool Btn_01State;
bool Btn_01LastRead;
//Initial mode and last status checker
byte Mode = 0;
byte LastMode = 1;
//Declares how many modes the machine have to cycle through
byte modesQty = 1;

void setup() {
  //Start-up Proceedure

  //DFPlayer Startup
  DFSoftSerial.begin(9600);
  DFPlayer.begin(DFSoftSerial);
  DFPlayer.volume(30);
  //LEDs
  pinMode(LED_Green,  OUTPUT);
  pinMode(LED_Yellow, OUTPUT);
  pinMode(LED_Red,    OUTPUT);
  //Actuators
  pinMode(Coil_01, OUTPUT);
  //Controls and Buttons
  pinMode(Btn_01,  INPUT);

  //Play Startup Sound and LED Effects
  playStartUp();
}

void loop(){
stateCycler();

//Calls the mode modeSelect if the status changes
if (Mode != LastMode){
  modeSelect();
  LastMode = Mode;
}
}

//Reads the button 01 state and cycle through qty of states
void stateCycler(){
  Btn_01State = digitalRead(Btn_01);
  if (Btn_01State != Btn_01LastRead){
    if (Btn_01State == HIGH){
      if (Mode >= modesQty){
        Mode = 0;
      } else {
        ++Mode;
      }
    }
    delay(150);
  }
  Btn_01LastRead = Btn_01State;
}

//Set the outputs as the states indicates
void modeSelect(){
  
  switch (Mode)
  {
  case 0:
    standBy();
    break;
  case 1:
    makingCoffee();
    break;
  }
}

//Making coffee Mode
void makingCoffee(){
  cleanLEDs();
  for (byte i = 0; i < 5; i++)
  {
    digitalWrite(LED_Green, HIGH);
    delay(50);
    digitalWrite(LED_Green, LOW);
    delay(50);
  }
  digitalWrite(LED_Green, HIGH);
  digitalWrite(Coil_01, HIGH);
  DFPlayer.play(3);
}

//Stand by Mode 
void standBy(){
  cleanLEDs();
  for (byte i = 0; i < 5; i++)
  {
    digitalWrite(LED_Red, HIGH);
    delay(50);
    digitalWrite(LED_Red, LOW);
    delay(50);
  }
  digitalWrite(LED_Yellow, HIGH);
  digitalWrite(Coil_01, LOW);
  DFPlayer.play(5);
}

//Cleans up all lit LEDs
void cleanLEDs(){
  digitalWrite(LED_Green, LOW);
  digitalWrite(LED_Yellow, LOW);
  digitalWrite(LED_Red, LOW);
}
int fadeDelay = 500;

void playStartUp(){
  DFPlayer.play(1);
  for (int j = 0; j < 10; j++)
  {
    for (int i = 0; i < 500; i++)
  {
    if ((i>0)&&(i<250)){
      analogWrite(LED_Green, i);
      delayMicroseconds(fadeDelay);
      }
    if ((i>125)&&(i<375)){
      analogWrite(LED_Yellow, i-125);
      delayMicroseconds(fadeDelay);
      }
    if ((i>250)&&(i<500)){
      analogWrite(LED_Red, i-250);
      delayMicroseconds(fadeDelay);
      }
  }
  for (int i = 500; i > 0; i--)
  {
    if ((i<500)&&(i>250)){
      analogWrite(LED_Green, i-250);
      delayMicroseconds(fadeDelay);
      }
    if ((i<375)&&(i>125)){
      analogWrite(LED_Yellow, i-125);
      delayMicroseconds(fadeDelay);
      }
    if ((i>0)&&(i<250)){
      analogWrite(LED_Red, i);
      delayMicroseconds(fadeDelay);
      }
  }
  }
}