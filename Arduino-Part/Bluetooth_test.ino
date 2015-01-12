#include "EEPROM.h"

#define D1 2          // direction of motor rotation 1
#define M1 3          // PWM left motor
#define D2 4          // direction of motor rotation 2
#define M2 5          // PWM right motor

char incomingByte;

unsigned long currentTime, lastTimeCommand, autoOFF;
boolean MotorL, MotorR, valueSet, directionSet, direc;
int i;

void setup()
{
  Serial.begin(9600); // Bitrate 9600 bit/s => Bitdauer 104µs
  pinMode(D1, OUTPUT);      // output for motor rotation
  pinMode(D2, OUTPUT);      // output for motor rotation
  MotorL = MotorR = valueSet = directionSet = direc = false;
  i = 0; 
}

void loop()
{
    if (Serial.available() > 0) 
    {   
      incomingByte = Serial.read();        // raed byte
      
      if(incomingByte=='L')              
      {
        MotorL = true;  
      }else if(incomingByte == 'B' && (MotorL || MotorR))
      {
        directionSet = true;
        direc = false;
      }else if(incomingByte=='F' && (MotorL || MotorR))
      {
        directionSet = true;
        direc = true;
      }else if (incomingByte=='R')
      {
        MotorR = true;      
      }else
      {
        if (direc)
        {
          i = 255 - (int)incomingByte;
        }else
          i = (int)incomingByte;
         valueSet = true;
      }
    }
    
    if(MotorL && valueSet && directionSet)
    {
      analogWrite(M1, i);            // set speed for left motor
      digitalWrite(D1, direc);        // set direction of left motor rotation
      MotorL = valueSet = directionSet = false;
    }
    
    if(MotorR && valueSet && directionSet)
    {
      analogWrite(M2, i);            // set speed for left motor
      digitalWrite(D2, direc);        // set direction of left motor rotation
      MotorR = valueSet = directionSet = false;
    }
}
