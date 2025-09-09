/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

// #define CABIN_LIGHTS_PIN 12
// #define CABIN_LIGHTS_SWITCH_PIN 2
//saber #define is depreciated.  It isn't a best practice anymore. 
//saber byte = uint8_t = keyword unsigned char = bits 8 = range 0 - 255 
const byte CABIN_LIGHTS_PIN = 10;  //pin controlling the cabin lights
const byte STORAGE_LIGHTS_PIN = 11;  //pin controlling the storage lights
const byte COCKPIT_LIGHTS_PIN = 12;  //pin controlling the exterior lights

const byte CABIN_LIGHTS_SWITCH_PIN = 2;  //cabin lights controlled by switch 1
const byte STORAGE_LIGHTS_SWITCH_PIN = 3;  //cabin lights controlled by switch 2
const byte COCKPIT_LIGHTS_SWITCH_PIN = 4;  //exterior lights controlled by switch 3

bool CABIN_LIGHTS_SWITCH_CURRENT = 0;
bool STORAGE_LIGHTS_SWITCH_CURRENT = 0;
bool COCKPIT_LIGHTS_SWITCH_CURRENT = 0;

bool CABIN_LIGHTS_SWITCH_MEMORY = 0;
bool STORAGE_LIGHTS_SWITCH_MEMORY = 0;
bool COCKPIT_LIGHTS_SWITCH_MEMORY = 0;

// the setup function runs once when you press reset or power the board
void setup() 
{
  // initialize digital pins output.
  pinMode(CABIN_LIGHTS_PIN, OUTPUT);
  pinMode(STORAGE_LIGHTS_PIN, OUTPUT);
  pinMode(COCKPIT_LIGHTS_PIN, OUTPUT);

  // initialize digital pins as an input.
  pinMode(CABIN_LIGHTS_SWITCH_PIN, INPUT);
  pinMode(STORAGE_LIGHTS_SWITCH_PIN, INPUT);
  pinMode(COCKPIT_LIGHTS_SWITCH_PIN, INPUT);

  CABIN_LIGHTS_SWITCH_MEMORY = digitalRead(CABIN_LIGHTS_SWITCH_PIN);
  STORAGE_LIGHTS_SWITCH_MEMORY = digitalRead(STORAGE_LIGHTS_SWITCH_PIN);
  COCKPIT_LIGHTS_SWITCH_MEMORY = digitalRead(COCKPIT_LIGHTS_SWITCH_PIN);
}

// the loop function runs over and over again forever
// saber, this is a more practical solution because you can leave one room with 
// the light on and when you get to the next, turn that light on and it will take priority.
// If you are back in a room that lost priority, just turn off and back on to regain priority.
void loop()
{
  CABIN_LIGHTS_SWITCH_CURRENT = digitalRead(CABIN_LIGHTS_SWITCH_PIN);
  STORAGE_LIGHTS_SWITCH_CURRENT = digitalRead(STORAGE_LIGHTS_SWITCH_PIN);
  COCKPIT_LIGHTS_SWITCH_CURRENT = digitalRead(COCKPIT_LIGHTS_SWITCH_PIN);
  
  if(CABIN_LIGHTS_SWITCH_CURRENT != CABIN_LIGHTS_SWITCH_MEMORY)
  {
    if(CABIN_LIGHTS_SWITCH_CURRENT == HIGH)
    {
      digitalWrite(CABIN_LIGHTS_PIN, HIGH);
      digitalWrite(STORAGE_LIGHTS_PIN, LOW);
      digitalWrite(COCKPIT_LIGHTS_PIN, LOW);
    }
    else
    {
      digitalWrite(CABIN_LIGHTS_PIN, LOW);
    }
    CABIN_LIGHTS_SWITCH_MEMORY = CABIN_LIGHTS_SWITCH_CURRENT;
  }
    
  if(STORAGE_LIGHTS_SWITCH_CURRENT != STORAGE_LIGHTS_SWITCH_MEMORY)
  {
    if(STORAGE_LIGHTS_SWITCH_CURRENT == HIGH)
    {
      digitalWrite(STORAGE_LIGHTS_PIN, HIGH);
      digitalWrite(CABIN_LIGHTS_PIN, LOW);
      digitalWrite(COCKPIT_LIGHTS_PIN, LOW);
    }
    else
    {
      digitalWrite(STORAGE_LIGHTS_PIN, LOW);
    }
    STORAGE_LIGHTS_SWITCH_MEMORY = STORAGE_LIGHTS_SWITCH_CURRENT;
  }

  if(COCKPIT_LIGHTS_SWITCH_CURRENT != COCKPIT_LIGHTS_SWITCH_MEMORY)
  {
    if(COCKPIT_LIGHTS_SWITCH_CURRENT == HIGH)
    {
      digitalWrite(COCKPIT_LIGHTS_PIN, HIGH);
      digitalWrite(CABIN_LIGHTS_PIN, LOW);
      digitalWrite(STORAGE_LIGHTS_PIN, LOW);
    }
    else
    {
      digitalWrite(COCKPIT_LIGHTS_PIN, LOW);
    }
    COCKPIT_LIGHTS_SWITCH_MEMORY = COCKPIT_LIGHTS_SWITCH_CURRENT;
  }
}

// saber notes 
// the long lead of the LED should go to positive.  The short should go to ground.
// The 10K resistor is for the switch 
// The 220R resistor is for the leds
// Resistors can be put in either direction.
