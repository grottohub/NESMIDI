#include <MIDI.h>
#include "Controller.h"

/*************************************************************
  MIDI CONTROLLER

  by Notes and Volts
  www.notesandvolts.com

  Version 1.2 **Arduino UNO ONLY!**
 *************************************************************/

// Begin NES Controller Wrapper

const int A_BUTTON         = 0;
const int B_BUTTON         = 1;
const int SELECT_BUTTON    = 2;
const int START_BUTTON     = 3;
const int UP_BUTTON        = 4;
const int DOWN_BUTTON      = 5;
const int LEFT_BUTTON      = 6;
const int RIGHT_BUTTON     = 7;

//===============================================================================
//  Variables
//===============================================================================
byte nesRegister  = 0;    // We will use this to hold current button states

//===============================================================================
//  Pin Declarations
//===============================================================================
//Inputs:
int nesData       = 4;    // The data pin for the NES controller

//Outputs:
int nesClock      = 2;    // The clock pin for the NES controller
int nesLatch      = 3;    // The latch pin for the NES controller

//===============================================================================
//  Initialization
//===============================================================================

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() 
{
  // Initialize serial port speed for the serial terminal
  Serial.begin(9600);
  
  // Set appropriate pins to inputs
  pinMode(nesData, INPUT);
  
  // Set appropriate pins to outputs
  pinMode(nesClock, OUTPUT);
  pinMode(nesLatch, OUTPUT);
  
  // Set initial states
  digitalWrite(nesClock, LOW);
  digitalWrite(nesLatch, LOW);

  MIDI.begin(MIDI_CHANNEL_OFF);
}

//===============================================================================
//  Main
//===============================================================================
/* void loop() 
{
  // This function call will return the states of all NES controller's register
  // in a nice 8 bit variable format. Remember to refer to the table and
  // constants above for which button maps where!
  nesRegister = readNesController();
  
  // Slight delay before we debug what was pressed so we don't spam the
  // serial monitor.
  delay(180);
  
  // To give you an idea on how to use this data to control things for your
  // next project, look through the serial terminal code below. Basically,
  // just choose a bit to look at and decide what to do whether HIGH (not pushed)
  // or LOW (pushed). What is nice about this test code is that we mapped all
  // of the bits to the actual button name so no useless memorizing!
  if (bitRead(nesRegister, A_BUTTON) == 0)
    Serial.println("JUMP!");
    
  if (bitRead(nesRegister, B_BUTTON) == 0)
    Serial.println("PUNCH!");
    
  if (bitRead(nesRegister, START_BUTTON) == 0)
    Serial.println("DOOMSDAY ACTIVATED");
  
  if (bitRead(nesRegister, SELECT_BUTTON) == 0)
    Serial.println("WHY DON'T YOU MAP SOMETHING HERE?");
    
  if (bitRead(nesRegister, UP_BUTTON) == 0)
    Serial.println("...OR HERE?");
    
  if (bitRead(nesRegister, DOWN_BUTTON) == 0)
    Serial.println("PLAY WITH THE CODE ALREADY!");
    
  if (bitRead(nesRegister, LEFT_BUTTON) == 0)
    Serial.println("MAKE SOMETHING WITH THIS!");  
  
  if (bitRead(nesRegister, RIGHT_BUTTON) == 0)
    Serial.println("GOOD LUCK WITH YOUR PROJECT ");

  if (NUMBER_BUTTONS != 0) updateButtons();
  if (NUMBER_POTS != 0) updatePots();
  if (NUMBER_MUX_BUTTONS != 0) updateMuxButtons();
  if (NUMBER_MUX_POTS != 0) updateMuxPots();
} */

//===============================================================================
//  Functions
//===============================================================================
///////////////////////
// readNesController //
///////////////////////
byte readNesController() 
{  
  // Pre-load a variable with all 1's which assumes all buttons are not
  // pressed. But while we cycle through the bits, if we detect a LOW, which is
  // a 0, we clear that bit. In the end, we find all the buttons states at once.
  int tempData = 255;
    
  // Quickly pulse the nesLatch pin so that the register grab what it see on
  // its parallel data pins.
  digitalWrite(nesLatch, HIGH);
  digitalWrite(nesLatch, LOW);
 
  // Upon latching, the first bit is available to look at, which is the state
  // of the A button. We see if it is low, and if it is, we clear out variable's
  // first bit to indicate this is so.
  if (digitalRead(nesData) == LOW)
    bitClear(tempData, A_BUTTON);
    
  // Clock the next bit which is the B button and determine its state just like
  // we did above.
  digitalWrite(nesClock, HIGH);
  digitalWrite(nesClock, LOW);
  if (digitalRead(nesData) == LOW)
    bitClear(tempData, B_BUTTON);
  
  // Now do this for the rest of them!
  
  // Select button
  digitalWrite(nesClock, HIGH);
  digitalWrite(nesClock, LOW);
  if (digitalRead(nesData) == LOW)
    bitClear(tempData, SELECT_BUTTON);

  // Start button
  digitalWrite(nesClock, HIGH);
  digitalWrite(nesClock, LOW);
  if (digitalRead(nesData) == LOW)
    bitClear(tempData, START_BUTTON);

  // Up button
  digitalWrite(nesClock, HIGH);
  digitalWrite(nesClock, LOW);
  if (digitalRead(nesData) == LOW)
    bitClear(tempData, UP_BUTTON);
    
  // Down button
  digitalWrite(nesClock, HIGH);
  digitalWrite(nesClock, LOW);
  if (digitalRead(nesData) == LOW)
    bitClear(tempData, DOWN_BUTTON);

  // Left button
  digitalWrite(nesClock, HIGH);
  digitalWrite(nesClock, LOW);
  if (digitalRead(nesData) == LOW)
    bitClear(tempData, LEFT_BUTTON);  
    
  // Right button
  digitalWrite(nesClock, HIGH);
  digitalWrite(nesClock, LOW);
  if (digitalRead(nesData) == LOW)
    bitClear(tempData, RIGHT_BUTTON);
    
  // After all of this, we now have our variable all bundled up
  // with all of the NES button states.*/
  return tempData;
}
//End NES Controller Wrapper

// MIDI_CREATE_DEFAULT_INSTANCE();

//************************************************************
//***SET THE NUMBER OF CONTROLS USED**************************
//************************************************************
//---How many buttons are connected directly to pins?---------
byte NUMBER_BUTTONS = 1;
//---How many potentiometers are connected directly to pins?--
byte NUMBER_POTS = 0;
//---How many buttons are connected to a multiplexer?---------
byte NUMBER_MUX_BUTTONS = 0;
//---How many potentiometers are connected to a multiplexer?--
byte NUMBER_MUX_POTS = 0;
//************************************************************

//***ANY MULTIPLEXERS? (74HC4067)************************************
//MUX address pins must be connected to Arduino UNO pins 2,3,4,5
//A0 = PIN2, A1 = PIN3, A2 = PIN4, A3 = PIN5
//*******************************************************************
//Mux NAME (OUTPUT PIN, , How Many Mux Pins?(8 or 16) , Is It Analog?);


//Mux M1(10, 16, false); //Digital multiplexer on Arduino pin 10
//Mux M2(A5, 8, true); //Analog multiplexer on Arduino analog pin A0
//*******************************************************************


//***DEFINE DIRECTLY CONNECTED POTENTIOMETERS************************
//Pot (Pin Number, Command, CC Control, Channel Number)
//**Command parameter is for future use**

//Pot PO1(A0, 0, 1, 1);
//Pot PO2(A1, 0, 10, 1);
//Pot PO3(A2, 0, 22, 1);
//Pot PO4(A3, 0, 118, 1);
//Pot PO5(A4, 0, 30, 1);
//Pot PO6(A5, 0, 31, 1);
//*******************************************************************
//Add pots used to array below like this->  Pot *POTS[] {&PO1, &PO2, &PO3, &PO4, &PO5, &PO6};
Pot *POTS[] {};
//*******************************************************************


//***DEFINE DIRECTLY CONNECTED BUTTONS*******************************
// Button (Pin Number, Command, Note Number, Channel, Debounce Time)
//** Command parameter 0=NOTE  1=CC  2=Toggle CC **

Button BU1(2, 0, 60, 1, 5 );
//Button BU2(3, 0, 61, 1, 5 );
//Button BU3(4, 0, 62, 1, 5 );
//Button BU4(5, 0, 63, 1, 5 );
//Button BU5(6, 0, 64, 1, 5 );
//Button BU6(7, 0, 65, 1, 5 );
//Button BU7(8, 1, 64, 1, 5 );
//Button BU8(9, 2, 64, 1, 5 );
//*******************************************************************
//Add buttons used to array below like this->  Button *BUTTONS[] {&BU1, &BU2, &BU3, &BU4, &BU5, &BU6, &BU7, &BU8};
Button *BUTTONS[] {&BU1};
//*******************************************************************


//***DEFINE BUTTONS CONNECTED TO MULTIPLEXER*************************
//Button::Button(Mux mux, byte muxpin, byte command, byte value, byte channel, byte debounce)
//** Command parameter 0=NOTE  1=CC  2=Toggle CC **

//Button MBU1(M1, 0, 0, 70, 1, 5);
//Button MBU2(M1, 1, 1, 71, 1, 5);
//Button MBU3(M1, 2, 2, 72, 1, 5);
//Button MBU4(M1, 3, 0, 73, 1, 5);
//Button MBU5(M1, 4, 0, 74, 1, 5);
//Button MBU6(M1, 5, 0, 75, 1, 5);
//Button MBU7(M1, 6, 0, 76, 1, 5);
//Button MBU8(M1, 7, 0, 77, 1, 5);
//Button MBU9(M1, 8, 0, 78, 1, 5);
//Button MBU10(M1, 9, 0, 79, 1, 5);
//Button MBU11(M1, 10, 0, 80, 1, 5);
//Button MBU12(M1, 11, 0, 81, 1, 5);
//Button MBU13(M1, 12, 0, 82, 1, 5);
//Button MBU14(M1, 13, 0, 83, 1, 5);
//Button MBU15(M1, 14, 0, 84, 1, 5);
//Button MBU16(M1, 15, 0, 85, 1, 5);
//*******************************************************************
////Add multiplexed buttons used to array below like this->  Button *MUXBUTTONS[] {&MBU1, &MBU2, &MBU3, &MBU4, &MBU5, &MBU6.....};
Button *MUXBUTTONS[] {};

//*******************************************************************


//***DEFINE POTENTIOMETERS CONNECTED TO MULTIPLEXER*******************
//Pot::Pot(Mux mux, byte muxpin, byte command, byte control, byte channel)
//**Command parameter is for future use**

//Pot MPO1(M2, 0, 0, 1, 1);
//Pot MPO2(M2, 1, 0, 7, 1);
//Pot MPO3(M2, 2, 0, 50, 1);
//Pot MPO4(M2, 3, 0, 55, 2);
//Pot MPO5(M2, 4, 0, 50, 1);
//Pot MPO6(M2, 5, 0, 55, 2);
//Pot MPO7(M2, 6, 0, 50, 1);
//Pot MPO8(M2, 7, 0, 55, 2);
//Pot MPO9(M2, 8, 0, 50, 1);
//Pot MPO10(M2, 9, 0, 55, 2);
//Pot MPO11(M2, 10, 0, 50, 1);
//Pot MPO12(M2, 11, 0, 55, 2);
//Pot MPO13(M2, 12, 0, 50, 1);
//Pot MPO14(M2, 13, 0, 55, 2);
//Pot MPO15(M2, 14, 0, 50, 1);
//Pot MPO16(M2, 15, 0, 55, 2);
//*******************************************************************
//Add multiplexed pots used to array below like this->  Pot *MUXPOTS[] {&MPO1, &MPO2, &MPO3, &MPO4, &MPO5, &MPO6.....};
Pot *MUXPOTS[] {};
//*******************************************************************


/* void setup() {
  MIDI.begin(MIDI_CHANNEL_OFF);
} */

/* void loop() {
  if (NUMBER_BUTTONS != 0) updateButtons();
  if (NUMBER_POTS != 0) updatePots();
  if (NUMBER_MUX_BUTTONS != 0) updateMuxButtons();
  if (NUMBER_MUX_POTS != 0) updateMuxPots();
} */
void loop() 
{
  // This function call will return the states of all NES controller's register
  // in a nice 8 bit variable format. Remember to refer to the table and
  // constants above for which button maps where!
  nesRegister = readNesController();
  
  // Slight delay before we debug what was pressed so we don't spam the
  // serial monitor.
  delay(180);
  
  // To give you an idea on how to use this data to control things for your
  // next project, look through the serial terminal code below. Basically,
  // just choose a bit to look at and decide what to do whether HIGH (not pushed)
  // or LOW (pushed). What is nice about this test code is that we mapped all
  // of the bits to the actual button name so no useless memorizing!
  if (bitRead(nesRegister, A_BUTTON) == 0)
    Serial.println("JUMP!");
    
  if (bitRead(nesRegister, B_BUTTON) == 0)
    Serial.println("PUNCH!");
    
  if (bitRead(nesRegister, START_BUTTON) == 0)
    Serial.println("DOOMSDAY ACTIVATED");
  
  if (bitRead(nesRegister, SELECT_BUTTON) == 0)
    Serial.println("WHY DON'T YOU MAP SOMETHING HERE?");
    
  if (bitRead(nesRegister, UP_BUTTON) == 0)
    Serial.println("...OR HERE?");
    
  if (bitRead(nesRegister, DOWN_BUTTON) == 0)
    Serial.println("PLAY WITH THE CODE ALREADY!");
    
  if (bitRead(nesRegister, LEFT_BUTTON) == 0)
    Serial.println("MAKE SOMETHING WITH THIS!");  
  
  if (bitRead(nesRegister, RIGHT_BUTTON) == 0)
    Serial.println("GOOD LUCK WITH YOUR PROJECT ");

  if (NUMBER_BUTTONS != 0) updateButtons();
  if (NUMBER_POTS != 0) updatePots();
  if (NUMBER_MUX_BUTTONS != 0) updateMuxButtons();
  if (NUMBER_MUX_POTS != 0) updateMuxPots();
}
//*****************************************************************
void updateButtons() {

  // Cycle through Button array
  for (int i = 0; i < NUMBER_BUTTONS; i = i + 1) {
    byte message = BUTTONS[i]->getValue();

    //  Button is pressed
    if (message == 0) {
      switch (BUTTONS[i]->Bcommand) {
        case 0: //Note
          MIDI.sendNoteOn(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
          break;
        case 1: //CC
          MIDI.sendControlChange(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
          break;
        case 2: //Toggle
          if (BUTTONS[i]->Btoggle == 0) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
            BUTTONS[i]->Btoggle = 1;
          }
          else if (BUTTONS[i]->Btoggle == 1) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 0, BUTTONS[i]->Bchannel);
            BUTTONS[i]->Btoggle = 0;
          }
          break;
      }
    }

    //  Button is not pressed
    if (message == 1) {
      switch (BUTTONS[i]->Bcommand) {
        case 0:
          MIDI.sendNoteOff(BUTTONS[i]->Bvalue, 0, BUTTONS[i]->Bchannel);
          break;
        case 1:
          MIDI.sendControlChange(BUTTONS[i]->Bvalue, 0, BUTTONS[i]->Bchannel);
          break;
      }
    }
  }
}
//*******************************************************************
void updateMuxButtons() {

  // Cycle through Mux Button array
  for (int i = 0; i < NUMBER_MUX_BUTTONS; i = i + 1) {

    MUXBUTTONS[i]->muxUpdate();
    byte message = MUXBUTTONS[i]->getValue();

    //  Button is pressed
    if (message == 0) {
      switch (MUXBUTTONS[i]->Bcommand) {
        case 0: //Note
          MIDI.sendNoteOn(MUXBUTTONS[i]->Bvalue, 127, MUXBUTTONS[i]->Bchannel);
          break;
        case 1: //CC
          MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 127, MUXBUTTONS[i]->Bchannel);
          break;
        case 2: //Toggle
          if (MUXBUTTONS[i]->Btoggle == 0) {
            MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 127, MUXBUTTONS[i]->Bchannel);
            MUXBUTTONS[i]->Btoggle = 1;
          }
          else if (MUXBUTTONS[i]->Btoggle == 1) {
            MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 0, MUXBUTTONS[i]->Bchannel);
            MUXBUTTONS[i]->Btoggle = 0;
          }
          break;
      }
    }
    //  Button is not pressed
    if (message == 1) {
      switch (MUXBUTTONS[i]->Bcommand) {
        case 0:
          MIDI.sendNoteOff(MUXBUTTONS[i]->Bvalue, 0, MUXBUTTONS[i]->Bchannel);
          break;
        case 1:
          MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 0, MUXBUTTONS[i]->Bchannel);
          break;
      }
    }
  }
}
//***********************************************************************
void updatePots() {
  for (int i = 0; i < NUMBER_POTS; i = i + 1) {
    byte potmessage = POTS[i]->getValue();
    if (potmessage != 255) MIDI.sendControlChange(POTS[i]->Pcontrol, potmessage, POTS[i]->Pchannel);
  }
}
//***********************************************************************
void updateMuxPots() {
  for (int i = 0; i < NUMBER_MUX_POTS; i = i + 1) {
    MUXPOTS[i]->muxUpdate();
    byte potmessage = MUXPOTS[i]->getValue();
    if (potmessage != 255) MIDI.sendControlChange(MUXPOTS[i]->Pcontrol, potmessage, MUXPOTS[i]->Pchannel);
  }
}
