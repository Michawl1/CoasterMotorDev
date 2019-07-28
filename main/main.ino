/*******************************************************************************
 * @file CoasterDev.cpp
 * @author Michael Thompson
 * @brief This file outlines the main application of the coaster motor dev
 *        project
 * @details
*******************************************************************************/

#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

void setup();
void loop();
void interrupt1();
void interrupt2();

Adafruit_PWMServoDriver g_motorDriver = Adafruit_PWMServoDriver();
uint8_t g_interrupt1 = 2;
uint8_t g_interrupt2 = 3;
uint8_t g_state = 0;

void setup()
{
  g_motorDriver.begin();
  g_motorDriver.setPWMFreq(50000);

  pinMode(g_interrupt1, INPUT_PULLUP);
  pinMode(g_interrupt2, INPUT_PULLUP);

  attachInterrupt(INT0, interrupt1, RISING);
  attachInterrupt(INT1, interrupt2, RISING);
}

void loop()
{

}

//Switch tied to brakes
void interrupt1()
{
  delay(1000);
  g_motorDriver.setPWM(0, 0, 50);
  delay(1000);
  g_motorDriver.setPWM(0, 0, 250);
}

//Switch tied to station
void interrupt2()
{
  g_motorDriver.setPWM(1, 0, 50);
  delay(1000);
  g_motorDriver.setPWM(1, 0, 250);
  delay(1000);
  
  //deploy motor
  g_motorDriver.setPWM(2, 0, 50);
  delay(1000);
  g_motorDriver.setPWM(2, 0, 250);
  delay(1000);
}
