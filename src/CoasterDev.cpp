/*******************************************************************************
 * @file CoasterDev.cpp
 * @author Michael Thompson
 * @brief This file outlines the main application of the coaster motor dev
 *        project
 * @details
*******************************************************************************/

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver g_motorDriver = Adafruit_PWMServoDriver();

void setup() {
  g_motorDriver.begin();
  g_motorDriver.setPWMFreq(50000);
}

void loop() {
  g_motorDriver.setPWM(0, 0, 50);
  delay(1000);
  g_motorDriver.setPWM(0, 0, 250);
  delay(1000);

}
