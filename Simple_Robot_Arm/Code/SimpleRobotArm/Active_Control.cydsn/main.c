/*
ELC 343 - Microcomputer Lab Final Project
November 19, 2019
Goal: controlling 3 servos and stepper motor to form a simple 
3-DOF robot arm, using touch sensor and potentiometer inputs
Authors: Jordan Sinoway & Caleb McKinney
*/



#include "project.h"
#include "stdio.h"
#include "string.h"
#include "math.h"


#define STEP_DELAY (2) //defining global delay for stepper motor


uint16 curPos, oldPos;

uint16 CapSense_DisplayState(void)
{
    curPos = CapSense_CSD_GetCentroidPos(CapSense_CSD_LINEARSLIDER0__LS); //find slider position
    
    /*
    if(curPos == 0xFFFFu) //reset position
    {
        curPos = 0u;
    }
    */
    
    return curPos;
    
}


void stepper(int a, int b, int c, int d, int delay)
{
    A_Write(a);
    B_Write(b);
    C_Write(c);
    D_Write(d);
    CyDelay(delay);
}


int range_map(int x, int a, int b, int c, int d) // y = (x-a)((d-c)/(b-a)) + c   | range [a,b] | range [c,d] | input x |
{
    int mapped_out;                              //mapping function to convert 0-255 ADC (8-bit) output range to PWM for servo
    
    mapped_out = ((x - a)*(d - c)/(b - a)) + c;
    
    return mapped_out;
}

int main(void)
{
    CyGlobalIntEnable; 
    
    LCD_Char_1_Start();//initalizing lcd
    char lcdOutput[256];//string for lcd display
    
    PWM_1_Start(); //start PWM block 1
    ADC_SAR_1_Start(); //start SAR ADC 1
    PWM_2_Start(); //start PWM block 2
    ADC_SAR_2_Start(); //start SAR ADC 2
    ADC_DelSig_1_Start();
    PWM_3_Start();
    
    CapSense_CSD_Start();
    CapSense_CSD_InitializeAllBaselines();
    
 
    
    int val1; //initial adc output val
    int val2;
    int val3;
    
    int stepPos = 0;
    int targetPos = 0;
    
    int mapped_val1; //val post mapping
    int mapped_val2;
    int mapped_val3;
     

    for(;;)
    {
        ADC_SAR_1_StartConvert();
        ADC_SAR_2_StartConvert(); //note: max amount of SAR ADCs is 2 on PSOC5 LP
        ADC_DelSig_1_StartConvert();
        
        
        ADC_SAR_1_IsEndConversion(ADC_SAR_1_WAIT_FOR_RESULT); //wait for ADC output
        ADC_SAR_2_IsEndConversion(ADC_SAR_2_WAIT_FOR_RESULT);
        ADC_DelSig_1_IsEndConversion(ADC_DelSig_1_WAIT_FOR_RESULT);
        
                
        if(0u == CapSense_CSD_IsBusy())
        {
            CapSense_CSD_UpdateEnabledBaselines();
            CapSense_CSD_ScanEnabledWidgets();
        }
        
        val3 = CapSense_DisplayState();
        
        
        val1 = (uint8_t) ADC_SAR_1_GetResult8(); //casting to uint8, as the input is int8 (bug)
        val2 = (uint8_t) ADC_SAR_2_GetResult8();
        targetPos = ADC_DelSig_1_GetResult32(); 
        
        mapped_val1 = range_map(val1, 0, 255, 850, 4500);//mapping 0-255 range of pot to 850-4500 range of PWM servo
        mapped_val2 = range_map(val2, 0, 255, 850, 4500);
        mapped_val3 = range_map(val3, 10, 85, 850, 4400);
        
        PWM_1_WriteCompare(mapped_val1); //writing to pwm (servo)
        PWM_2_WriteCompare(mapped_val2);
        PWM_3_WriteCompare(mapped_val3);
        
        
        if(stepPos < targetPos - 4) //clockwise motion, full wave stepping
        {
            stepper(1,0,0,0,STEP_DELAY);
            stepper(1,1,0,0,STEP_DELAY);
            stepper(0,1,0,0,STEP_DELAY);
            stepper(0,1,1,0,STEP_DELAY);
            stepper(0,0,1,0,STEP_DELAY);
            stepper(0,0,1,1,STEP_DELAY);
            stepper(0,0,0,1,STEP_DELAY);
            stepper(1,0,0,1,STEP_DELAY);
            
            stepPos++;          
        }
        if(stepPos > targetPos + 4 ) //counter-clockwise motion, full wave stepping 
        {
            stepper(0,0,0,1,STEP_DELAY);
            stepper(0,0,1,1,STEP_DELAY);
            stepper(0,0,1,0,STEP_DELAY);
            stepper(0,1,1,0,STEP_DELAY);
            stepper(0,1,0,0,STEP_DELAY);
            stepper(1,1,0,0,STEP_DELAY);
            stepper(1,0,0,0,STEP_DELAY);
            stepper(1,0,0,1,STEP_DELAY);
            
            stepPos--;
        }
        
                  
            LCD_Char_1_ClearDisplay(); //clears display
            LCD_Char_1_WriteControl(LCD_Char_1_CURSOR_HOME); //sets cursor to top left corner
            sprintf(lcdOutput,"targ=%3d", (int)targetPos);
            LCD_Char_1_Position(0,0); 
            LCD_Char_1_PrintString(lcdOutput); //prints PWM value for servo 1
            
            sprintf(lcdOutput,"Val2=%d", (int)mapped_val2);
            LCD_Char_1_Position(1,0); 
            LCD_Char_1_PrintString(lcdOutput); //prints PWM value for servo 1
            
            sprintf(lcdOutput,"Val3=%d", (int)mapped_val3);
            LCD_Char_1_Position(8,0); 
            LCD_Char_1_PrintString(lcdOutput); //prints PWM value for servo 1
            
            
        /*
        due to SAR ADC # limits, possibly add switching buttons to switch between controlling
        different servos with a single potentiometer, and use sliding CapSense for claw control
        */
            

        
        
    }
}


