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


//LEDs Pin Setup
const byte LED_Green  = 3;
const byte LED_Yellow = 4;
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
  //LEDs
  pinMode(LED_Green,  OUTPUT);
  pinMode(LED_Yellow, OUTPUT);
  pinMode(LED_Red,    OUTPUT);
  //Actuators
  pinMode(Coil_01, OUTPUT);
  //Controls and Buttons
  pinMode(Btn_01,  INPUT);
  playStartUp();
}

void loop() {

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
}

//Cleans up all lit LEDs
void cleanLEDs(){
  digitalWrite(LED_Green, LOW);
  digitalWrite(LED_Yellow, LOW);
  digitalWrite(LED_Red, LOW);
}

// void playStartUp(){
//   int startUpTone[] = {
//   NOTE_G4, NOTE_A3, NOTE_D4, NOTE_A3, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_D4};

//   int noteDurations[] = {4,7,7,7,3,4,3,4};

//   for (int thisNote = 0; thisNote < 8; thisNote++) {

//   // to calculate the note duration, take one second divided by the note type.
//   //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
//   int noteDuration = 1000 / noteDurations[thisNote];
//   tone(Buzzer, startUpTone[thisNote], noteDuration);

//   // to distinguish the notes, set a minimum time between them.
//   // the note's duration + 30% seems to work well:
//   int pauseBetweenNotes = noteDuration * 1.30;
//   delay(pauseBetweenNotes);
//   // stop the tone playing:
//   noTone(Buzzer);
//   }
// }