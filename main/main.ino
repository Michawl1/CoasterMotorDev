/*******************************************************************************
 * @file CoasterDev.cpp
 * @author Michael Thompson
 * @brief This file outlines the main application of the coaster motor dev
 *        project
 * @details
*******************************************************************************/

// Adafruit PWM Servo Driver Library by Adafruit v2.4.1
#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

enum BlockZone
{
  BEGIN,
  BRAKERUN,
  STATION,
  RIDE,
  END
};

const uint8_t g_brakeMotorIndex = 0;
const uint8_t g_stationGateMotorIndex = 1;
const uint8_t g_stationChainMotorIndex = 2;
Adafruit_PWMServoDriver g_motorDriver = Adafruit_PWMServoDriver();
BlockZone g_state = BlockZone::BEGIN;

void setup()
{
  g_motorDriver.begin();
  g_motorDriver.setOscillatorFrequency(25000000);
  g_motorDriver.setPWMFreq(50);
}

void loop()
{
  int brakesDown = 333;
  int brakesUp = 363;

  int chainOn = 200;
  int chainOff = 308;

  int gatesOpen = 347;
  int gatesClosed = 90;

  while(true)
  {      
    switch(g_state)
    {
      case BlockZone::BEGIN:
      {
        g_state = BlockZone::BRAKERUN;
      }
      break;
     
      case BlockZone::BRAKERUN:
      {      
        // brakes down
        for(int i = brakesUp; i > brakesDown; i-=2)
        {
          g_motorDriver.setPWM(
            g_brakeMotorIndex, 
            0, 
            i);
          delay(
            150);
        }
        
        g_state = BlockZone::STATION;
      }
      break;

      case BlockZone::STATION:
      {
        // Chain on
        g_motorDriver.setPWM(
          g_stationChainMotorIndex,
          0,
          chainOn);
        delay(1000);
        
        // brakes up
        g_motorDriver.setPWM(
          g_brakeMotorIndex, 
          0, 
          brakesUp);
        delay(1000);

        // Chain off
        g_motorDriver.setPWM(
          g_stationChainMotorIndex,
          0,
          chainOff);
        delay(1800);

        // Gates open
        g_motorDriver.setPWM(
          g_stationGateMotorIndex,
          0,
          gatesOpen);          
        delay(3500);

        // Gates closed
        g_motorDriver.setPWM(
          g_stationGateMotorIndex,
          0,
          gatesClosed);
        delay(1000);

        // Chain on
        g_motorDriver.setPWM(
          g_stationChainMotorIndex,
          0,
          chainOn);
        delay(3000);

        // Chain off
        g_motorDriver.setPWM(
          g_stationChainMotorIndex,
          0,
          chainOff);
          
        g_state = BlockZone::RIDE;
      }
      
      case BlockZone::RIDE:
      {
        delay(5500);

        g_state = BlockZone::BRAKERUN;
      }
      break;
    }
  }
}
