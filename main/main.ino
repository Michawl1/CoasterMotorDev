/*******************************************************************************
 * @file CoasterDev.cpp
 * @author Michael Thompson
 * @brief This file outlines the main application of the coaster motor dev
 *        project
 * @details
*******************************************************************************/

#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

Adafruit_PWMServoDriver g_motorDriver = Adafruit_PWMServoDriver();
uint8_t g_interrupt1 = 2;
uint8_t g_interrupt2 = 3;
uint8_t g_state = 0;
uint8_t val = 0;

void setup()
{
  g_motorDriver.begin();
  g_motorDriver.setPWMFreq(50000);

  pinMode(g_interrupt1, INPUT);
  pinMode(g_interrupt2, INPUT);
}

void loop()
{
  //brakes sequence
  val = digitalRead(g_interrupt1);
  if(val != LOW)
  {
    delay(4000);
    g_motorDriver.setPWM(0, 0, 50);
    delay(1500);
    g_motorDriver.setPWM(0, 0, 250);
  }

  //station sequence
  val = digitalRead(g_interrupt2);
  if(val != LOW)
  {
    delay(1000);
    g_motorDriver.setPWM(1, 0, 50);
    delay(2500);
    g_motorDriver.setPWM(1, 0, 250);
    delay(1000);

    g_motorDriver.setPWM(2, 0, 50);
    delay(2000);
    g_motorDriver.setPWM(2, 0, 250);
    delay(1000);
  }
}
