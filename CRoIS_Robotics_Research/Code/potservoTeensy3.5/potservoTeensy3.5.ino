// Controlling a servo position using a potentiometer

//   Board                     SERVO_PIN_A   SERVO_PIN_B   SERVO_PIN_C
//   -----                     -----------   -----------   -----------
//   //   Teensy 3.5                 (all PWM pins are usable)

#include <PWMServo.h>
#include <ResponsiveAnalogRead.h>

PWMServo servo1;  // create servo object to control servo1

const int potpin1 = A0;  // analog pin used to connect the potentiometer

ResponsiveAnalogRead analog1(potpin1, true);
//                   analog2(potpin2, true); etc for more pots
// make a ResponsiveAnalogRead object, pass in the pin, and either true or false depending on if you want sleep enabled
// enabling sleep will cause values to take less time to stop changing and potentially stop changing more abruptly,
// where as disabling sleep will cause values to ease into their correct position smoothly and more accurately

int val1;    // variable to read the value from the analog pin
int a;       // " " " " "

void setup() 
{
  //servo1.attach(9);         // attaches the servo on pin 9 to the servo object
  servo1.attach(9, 800, 2200); // some motors need min/max setting
  Serial.begin(115200);
}

void loop() 
{
  analogWriteResolution(13);
  analogReadResolution(13);
  
  analog1.setAnalogResolution(8192);
  
  analog1.update(); //updates ResponsiveAnalogRead every loop
//analog2.update();

//------------------------------------------------------------------
//Exclusively for visual reference, can be removed
  Serial.print(analog1.getRawValue());
  Serial.print("\t");
  Serial.print(analog1.getValue());
  Serial.print("\t");
  a = analog1.getValue();
  a = map(a, 0, 8191, 0, 179);
  Serial.print(a);
  
  // if the responsive value has changed, prints out "changed"
  if(analog1.hasChanged()) {
    Serial.print("\tchanged");
  }
  
  Serial.println("");
//--------------------------------------------------------------------
  val1 = analog1.getValue();            // reads the value of the potentiometer after pass through ResponsiveAnalogRead(value between 0 and 4095)
  val1 = map(val1, 0, 8191, 0, 179);     // scale it to use it with the servo (value between 0 and 179)
  servo1.write(val1);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
}
