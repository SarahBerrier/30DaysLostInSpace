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

bool CABIN_LIGHT_STATE = 0;
bool STORAGE_LIGHT_STATE = 0;
bool COCKPIT_LIGHT_STATE = 0;

bool binaryLightSwitch[] = {0,0,0};

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
}


//This is the day 5 challenge 2.  I make the 3 switches correlate to 3 binary 
// digits to potentially control 7 lights with 000 turning off all lights 
void loopChallenge2()
//void loop()
{
  for(int i = 0; i<3; i++)
  {
    if(digitalRead(i+2) == HIGH)
    {
      binaryLightSwitch[i] = 1;
    }
    else
    {
      binaryLightSwitch[i] = 0;
    }
  }

  if( binaryLightSwitch[0] == 0 && binaryLightSwitch[1] == 0 && binaryLightSwitch[2] == 0 )
  {
    digitalWrite(CABIN_LIGHTS_PIN, LOW);
    digitalWrite(STORAGE_LIGHTS_PIN, LOW);
    digitalWrite(COCKPIT_LIGHTS_PIN, LOW);
  }
  else if (binaryLightSwitch[0] == 0 && binaryLightSwitch[1] == 0 && binaryLightSwitch[2] == 1)
  {
    digitalWrite(CABIN_LIGHTS_PIN, LOW);
    digitalWrite(STORAGE_LIGHTS_PIN, LOW);
    digitalWrite(COCKPIT_LIGHTS_PIN, HIGH);
  }
  else if (binaryLightSwitch[0] == 0 && binaryLightSwitch[1] == 1 && binaryLightSwitch[2] == 0)
  {
    digitalWrite(CABIN_LIGHTS_PIN, LOW);
    digitalWrite(STORAGE_LIGHTS_PIN, HIGH);
    digitalWrite(COCKPIT_LIGHTS_PIN, LOW);
  }
  else if (binaryLightSwitch[0] == 0 && binaryLightSwitch[1] == 1 && binaryLightSwitch[2] == 1)
  {
    digitalWrite(CABIN_LIGHTS_PIN, HIGH);
    digitalWrite(STORAGE_LIGHTS_PIN, LOW);
    digitalWrite(COCKPIT_LIGHTS_PIN, LOW);
  }
  else
  {
    digitalWrite(CABIN_LIGHTS_PIN, LOW);
    digitalWrite(STORAGE_LIGHTS_PIN, LOW);
    digitalWrite(COCKPIT_LIGHTS_PIN, LOW);
  }
}

// the loop function runs over and over again forever
// saber comment.  I like my solution for challenge 1 from day 5 the best but it feels clunky and like too much code.  
// also, it isn't practical for a real world environment.  On the ship you don't want to have to turn off one light
// to travel in the dark to turn on a second light.
void loopChallenge1NonPractical() 
//void loop()
{
/*
  digitalWrite(CABIN_LIGHTS_PIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(100);                            // wait for a second
  digitalWrite(CABIN_LIGHTS_PIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                           // wait for a second
*/

  if(digitalRead(CABIN_LIGHTS_SWITCH_PIN) == HIGH)      //if the switch is on (HIGH voltage)
  {
    if (STORAGE_LIGHT_STATE || COCKPIT_LIGHT_STATE)
    {
      CABIN_LIGHT_STATE = 0;      
    }
    else
    {
      digitalWrite(CABIN_LIGHTS_PIN, HIGH);               //turn on LED by providing HIGH voltage (5V)
      CABIN_LIGHT_STATE = 1;
    }
  }
  else
  {
    digitalWrite(CABIN_LIGHTS_PIN, LOW);                //else turn off LED by setting output to LOW (zero volts)
    CABIN_LIGHT_STATE = 0;      
  }

  if(digitalRead(STORAGE_LIGHTS_SWITCH_PIN) == HIGH)
  {
    if (CABIN_LIGHT_STATE || COCKPIT_LIGHT_STATE)
    {
      STORAGE_LIGHT_STATE = 0;      
    }
    else
    {
      digitalWrite(STORAGE_LIGHTS_PIN, HIGH);
      STORAGE_LIGHT_STATE = 1;
    }
  }
  else
  {
    digitalWrite(STORAGE_LIGHTS_PIN, LOW);
    STORAGE_LIGHT_STATE = 0;      
  }

  if(digitalRead(COCKPIT_LIGHTS_SWITCH_PIN) == HIGH)
  {
    if (CABIN_LIGHT_STATE || STORAGE_LIGHT_STATE)
    {
      COCKPIT_LIGHT_STATE = 0;
    }
    else
    {
      digitalWrite(COCKPIT_LIGHTS_PIN, HIGH);
      COCKPIT_LIGHT_STATE = 1;
    }
  }
  else
  {
    digitalWrite(COCKPIT_LIGHTS_PIN, LOW);
    COCKPIT_LIGHT_STATE = 0;
  }
}

// saber, this is a more practical solution because you can leave one room with 
// the light on and when you get to the next, turn that light on and it will take priority.
void loop1challenge1Practical()
{
  if(digitalRead(CABIN_LIGHTS_SWITCH_PIN) == HIGH)      //if the switch is on (HIGH voltage)
  {
    if (CABIN_LIGHT_STATE == 0) 
    {    
      CABIN_LIGHT_STATE = 1;      
      digitalWrite(CABIN_LIGHTS_PIN, HIGH);               //turn on LED by providing HIGH voltage (5V)
    }
    else
    {
      CABIN_LIGHT_STATE = 1;
    }
  }
  else
  {
    digitalWrite(CABIN_LIGHTS_PIN, LOW);                //else turn off LED by setting output to LOW (zero volts)
    CABIN_LIGHT_STATE = 0;      
  }

}

// saber notes 
// the long lead of the LED should go to positive.  The short should go to ground.
// The 10K resistor is for the switch 
// The 220R resistor is for the leds
// Resistors can be put in either direction.
