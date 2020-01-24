/*
Robotic Arm Demo 
1/20/20
Demo program to demonstrate simple 3-DOF robot arm for TCF 2020
Authors: Jordan Sinoway
*/



#include "project.h"
#include "stdio.h"
#include "string.h"
#include "math.h"


#define STEP_DELAY (1) //defining global delay for stepper motor



void stepperCW(int degrees) //full wave stepping of stepper motor, 8 consecutive CW steps
{
    int actualDegree = degrees * 0.703125;
    int correctedTurn = degrees+(degrees - actualDegree);
    
    for(int i = 0; i < correctedTurn; i++)
    {
        Stepper_Write(0x8); // 1 0 0 0
        CyDelay(STEP_DELAY);
        Stepper_Write(0xC); // 1 1 0 0
        CyDelay(STEP_DELAY);
        Stepper_Write(0x4); // 0 1 0 0 
        CyDelay(STEP_DELAY);
        Stepper_Write(0x6); // 0 1 1 0
        CyDelay(STEP_DELAY);
        Stepper_Write(0x2); // 0 0 1 0 
        CyDelay(STEP_DELAY);
        Stepper_Write(0x3); // 0 0 1 1
        CyDelay(STEP_DELAY);
        Stepper_Write(0x1); // 0 0 0 1
        CyDelay(STEP_DELAY);
        Stepper_Write(0x9); // 1 0 0 1
        CyDelay(STEP_DELAY);
    }
}

void stepperCCW(int degrees)
{
    int actualDegree = degrees * 0.703125;
    int correctedTurn = degrees+(degrees - actualDegree);
    
    for(int i = 0; i < correctedTurn; i++)
    {
        Stepper_Write(0x1); // 0 0 0 1
        CyDelay(STEP_DELAY);
        Stepper_Write(0x3); // 0 0 1 1
        CyDelay(STEP_DELAY);
        Stepper_Write(0x2); // 0 0 1 0
        CyDelay(STEP_DELAY);
        Stepper_Write(0x6); // 0 1 1 0
        CyDelay(STEP_DELAY);
        Stepper_Write(0x4); // 0 1 0 0 
        CyDelay(STEP_DELAY);
        Stepper_Write(0xC); // 1 1 0 0
        CyDelay(STEP_DELAY);
        Stepper_Write(0x8); // 1 0 0 0
        CyDelay(STEP_DELAY);
        Stepper_Write(0x9); // 1 0 0 1
        CyDelay(STEP_DELAY);
    }
}





int main(void)
{
    CyGlobalIntEnable; 
    
    PWM_1_Start(); //start PWM block 1
    PWM_2_Start(); //start PWM block 2
    PWM_3_Start();
   
    for(;;)
    {
        stepperCCW(100);
        PWM_2_WriteCompare(2000);
        CyDelay(450);
        PWM_1_WriteCompare(3000);
        CyDelay(450);
        PWM_2_WriteCompare(2200);
        CyDelay(450);
        PWM_1_WriteCompare(2800);
        CyDelay(450);
        
        stepperCW(50);
        
        PWM_2_WriteCompare(2400);
        CyDelay(450);
        PWM_1_WriteCompare(2600);
        CyDelay(450);
        PWM_2_WriteCompare(2600);
        CyDelay(450);
        PWM_1_WriteCompare(2400);
        CyDelay(450);
        
        stepperCCW(50);
        
        PWM_2_WriteCompare(2800);
        CyDelay(450);
        PWM_1_WriteCompare(2200);
        CyDelay(450);
        PWM_2_WriteCompare(3000);
        CyDelay(450);
        PWM_1_WriteCompare(2000);
        CyDelay(450);
        
        PWM_3_WriteCompare(1000);
        CyDelay(450);
        PWM_3_WriteCompare(4000);
        CyDelay(450);
              
        stepperCW(100);
        CyDelay(200);
        
    }
    


    
}


