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

const unit8_t g_brakeMotorIndex = 0;
const uint8_t g_stationGateMotorIndex = 1;
const uint8_t g_stationChainMotorIndex = 2;
Adafruit_PWMServoDriver g_motorDriver = Adafruit_PWMServoDriver();
BlockZone g_state = BlockZone::BEGIN;

void setup()
{
  g_motorDriver.begin();
  g_motorDriver.setPWMFreq(50000);
}

void loop()
{
  while(true)
  {
    switch(g_state)
    {
      case BlockZone::BEGIN:
      {
        g_motorDriver.setPWM(
          g_brakeMotorIndex, 
          0, 
          10);
        delay(
          1000);
        g_motorDriver.setPWM(
          g_brakeMotorIndex, 
          0, 
          40);
        g_state = BlockZone::BRAKERUN;
      }
      break;

      case BlockZone::BRAKERUN:
      {
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
        delay(15000)
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
