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
        int brakesUp = 358;
        int brakesDown = 335;
        // brakes down
        for(int i = brakesUp; i > brakesDown; i--)
        {
          g_motorDriver.setPWM(
            g_brakeMotorIndex, 
            0, 
            i);
          delay(
            150);
        }
        delay(1000);
        // brakes up
        g_motorDriver.setPWM(
          g_brakeMotorIndex, 
          0, 
          brakesUp);
        g_state = BlockZone::STATION;
      }
      break;

      case BlockZone::STATION:
      {
        g_state = BlockZone::RIDE;
      }
      break;

      case BlockZone::RIDE:
      {
        delay(25000);
        g_state = BlockZone::BRAKERUN;
      }
      break;

      case BlockZone::END:
      {
      }
      break;
    }
  }
}
