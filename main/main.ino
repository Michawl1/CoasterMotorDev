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

  attachInterrupt(digitalPinToInterrupt(g_interrupt1), interrupt1, RISING);
  attachInterrupt(digitalPinToInterrupt(g_interrupt2), interrupt2, RISING);
}

void loop()
{

  switch(g_state)
  {
    case 0:
      //This is the default state, we don't do anything here
      break;
    case 1:
      //This is after the switch on the brakes is hit
      noInterrupts();
      delay(1000);
      g_motorDriver.setPWM(0, 0, 50);
      delay(1000);
      g_motorDriver.setPWM(0, 0, 250);
      interrupts();
      break;
    case 2:
      //This is afer the switch in the station is hit
      noInterrupts();
      //station gates
      g_motorDriver.setPWM(1, 0, 50);
      delay(1000);
      g_motorDriver.setPWM(1, 0, 250);
      delay(1000);

      //deploy motor
      g_motorDriver.setPWM(2, 0, 50);
      delay(1000);
      g_motorDriver.setPWM(2, 0, 250);
      delay(1000);

      interrupts();    
  }
  g_motorDriver.setPWM(0, 0, 50);
  delay(1000);
  g_motorDriver.setPWM(0, 0, 250);
  delay(1000);

}

void interrupt1()
{
   g_state = 1;
}

void interrupt2()
{
  g_state = 2;
}
