//Controlling multiple servos using multiple potentiometers
//framework for 1-to-1 robot joint/arm control

//   Board                     SERVO_PIN_A   SERVO_PIN_B   SERVO_PIN_C
//   -----                     -----------   -----------   -----------
//   //   Teensy 3.5                 (all PWM pins are usable)

#include <PWMServo.h>
#include <ResponsiveAnalogRead.h>

PWMServo servo1;  // create servo object to control servo1
PWMServo servo2;
PWMServo servo3;
PWMServo servo4;
PWMServo servo5;
PWMServo servo6;

const int potpin1 = A0;  // analog pin used to connect the potentiometer
const int potpin2 = A1;
const int potpin3 = A2;
const int potpin4 = A3;
const int potpin5 = A4;
const int potpin6 = A5;

ResponsiveAnalogRead analog1(potpin1, true);
ResponsiveAnalogRead analog2(potpin2, true);
ResponsiveAnalogRead analog3(potpin3, true);
ResponsiveAnalogRead analog4(potpin4, true);
ResponsiveAnalogRead analog5(potpin5, true);
ResponsiveAnalogRead analog6(potpin6, true);
// make a ResponsiveAnalogRead object, pass in the pin, and either true or false depending on if you want sleep enabled
// enabling sleep will cause values to take less time to stop changing and potentially stop changing more abruptly,
// where as disabling sleep will cause values to ease into their correct position smoothly and more accurately

int val1;    // variable to read the value from the analog pin
int val2;
int val3;
int val4;
int val5;
int val6;
int a;       // " " " " "

void setup() 
{
  servo1.attach(9);         // attaches the servo on pin 2 to the servo object
  //servo1.attach(SERVO_PIN_A, 1000, 2000); // some motors need min/max setting
  servo2.attach(10);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);
  servo6.attach(7);
  
  Serial.begin(38400);
}

void loop() 
{
  analogWriteResolution(13);
  analogReadResolution(13);
  
  analog1.setAnalogResolution(8192);
  analog2.setAnalogResolution(8192);
  analog3.setAnalogResolution(8192);
  analog4.setAnalogResolution(8192);
  analog5.setAnalogResolution(8192);
  analog6.setAnalogResolution(8192);
  
  analog1.update(); //updates ResponsiveAnalogRead every loop
  analog2.update();
  analog3.update();
  analog4.update();
  analog5.update();
  analog6.update();
  
//------------------------------------------------------------------
//Exclusively for visual reference, can be removed
  Serial.print(analog1.getRawValue());
  Serial.print("\t");
  Serial.print(analog1.getValue());
  Serial.print("\t");
  
  a = analog1.getValue();
  a = map(a, 0, 8191, 0, 179);
  Serial.print(a);
  Serial.print("\t");
  
  if(analog1.hasChanged()) 
  {
    Serial.print("changed");
  }
  
  Serial.print(analog2.getRawValue());
  Serial.print("\t");
  Serial.print(analog2.getValue());
  Serial.print("\t");
  
  a = analog2.getValue();
  a = map(a, 0, 8191, 0, 179);
  Serial.print(a);
  
  // if the responsive value has changed, prints out "changed"
  if(analog2.hasChanged()) 
  {
    Serial.print("\tchanged");
  }
  
  Serial.println("");
//--------------------------------------------------------------------
  val1 = analog1.getValue();           // reads the value of the potentiometer after pass through ResponsiveAnalogRead(value between 0 and 8191)
  val1 = map(val1, 0, 8191, 0, 179);   // scale it to use it with the servo (value between 0 and 179)
  servo1.write(val1);                  // sets the servo position according to the scaled value
 
  val2 = analog2.getValue();
  val2 = map(val2, 0, 8191, 0, 179);
  servo2.write(val2);

  val3 = analog3.getValue();
  val3 = map(val3, 0, 8191, 0, 179);
  servo3.write(val3);

  val4 = analog4.getValue();
  val4 = map(val4, 0, 8191, 0, 179);
  servo4.write(val4);

  val5 = analog5.getValue();
  val5 = map(val5, 0, 8191, 0, 179);
  servo5.write(val5);

  val6 = analog6.getValue();
  val6 = map(val6, 0, 8191, 0, 179);
  servo6.write(val6);
  
  delay(15);    // waits for the servos to get there
}
