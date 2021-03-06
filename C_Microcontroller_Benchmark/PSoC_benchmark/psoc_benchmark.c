/**
Benchmark for PSoC 4,5,6 vs Arduino comparison
Simple add-multiply benchmark for microcontrollers, timing of runs done with stopwatch
Can be extended to use internal timers later

Authors: Jordan Sinoway, Dr. Larry Pearlstein
TCNJ
1/14/2020
**/

#include "project.h"
#include <stdint.h>
#include <stdio.h>

int32_t x[1000];
int32_t y[1000];


int32_t inner_prod_benchmark( int32_t *x, int32_t *y, int32_t n ); //needs inner_prod_benchmark.c file in same directory 


int main(void)
{
    CyGlobalIntEnable; 
    UART_Start();  //uart output for timing
    int32_t n = 10;
    
    int32_t sum = 0;
    char str[64];
    
    for(;;)
    {

        for(int32_t i = 0; i <= (40000000/n); i++)
        {
            sum += (inner_prod_benchmark(x,y,n));
        }
        sprintf(str,"answer is %d\n\r", (int)(sum));
        UART_PutString(str);
    
    }
}

