//#include <MIDI.h>

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
int velocity = 100; //velocity of MIDI notes, 0-127
int noteOn = 144; // 144 = 1001000 in binary
int noteOff = 128; // 1000000 in binary

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

//MIDI_CREATE_DEFAULT_INSTANCE();

void setup() 
{
  // Set appropriate pins to inputs
  pinMode(nesData, INPUT);
  
  // Set appropriate pins to outputs
  pinMode(nesClock, OUTPUT);
  pinMode(nesLatch, OUTPUT);
  
  // Set initial states
  digitalWrite(nesClock, LOW);
  digitalWrite(nesLatch, LOW);

  // Set MIDI baud rate:
  Serial.begin(31250);

  //MIDI.begin(MIDI_CHANNEL_OFF);
}

//===============================================================================
//  Main
//===============================================================================
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
  if (bitRead(nesRegister, A_BUTTON) == 0){
    //MIDI.sendNoteOn(60, 127, 1);
    MIDIMessage(noteOn, 60, velocity);
    }
    
  if (bitRead(nesRegister, B_BUTTON) == 0){
    //MIDI.sendNoteOn(61, 127, 1);
    MIDIMessage(noteOn, 61, velocity);
    }
    
  if (bitRead(nesRegister, START_BUTTON) == 0){
    //MIDI.sendNoteOn(62, 127, 1);
    MIDIMessage(noteOn, 62, velocity);
    }
  
  if (bitRead(nesRegister, SELECT_BUTTON) == 0){
    //MIDI.sendNoteOn(63, 127, 1);
    MIDIMessage(noteOn, 63, velocity);
    }
    
  if (bitRead(nesRegister, UP_BUTTON) == 0){
    //MIDI.sendNoteOn(64, 127, 1);
    MIDIMessage(noteOn, 64, velocity);
    }
    
  if (bitRead(nesRegister, DOWN_BUTTON) == 0){
    //MIDI.sendNoteOn(65, 127, 1);
    MIDIMessage(noteOn, 65, velocity);
    }
    
  if (bitRead(nesRegister, LEFT_BUTTON) == 0){
    //MIDI.sendNoteOn(66, 127, 1);
    MIDIMessage(noteOn, 66, velocity);
    } 
  
  if (bitRead(nesRegister, RIGHT_BUTTON) == 0) {
    //MIDI.sendNoteOn(67, 127, 1);
    MIDIMessage(noteOn, 67, velocity);
    }

}

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

void MIDIMessage(int command, int MIDINote, int MIDIVelocity) {
  Serial.write(command);
  Serial.write(MIDINote);
  Serial.write(MIDIVelocity);
}
