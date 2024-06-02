/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "stdlib.h"
//#define TRIANGLE_WAVE 0
//#define SQUARE_WAVE 0
//#define SAWTOOTH_WAVE 0
#define STEP_WAVE 0


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_Start();
    UART_PutString("Exercise 2");
    uint16_t wave[256] = {0};  
    
    #ifdef TRIANGLE_WAVE
    for(uint16_t rise =0; rise <= 128;rise++)
    {
        wave[rise]=rise;            
    }
    for(uint16_t fall =129; fall <256;fall++)
    {
        wave[fall]=255-fall;
    } 
    for(uint16_t i = 0; i < 256; i++)
    {
        wave[i] = (i <= 128) ? i : 256 - i;
    }
    #endif
    
    #ifdef SQUARE_WAVE
    // 50% dutycycle 
    
    for(uint16_t i = 0; i < 256; i++)
    {
        wave[i] = (i < 128) ? 0 : 1;
    }
    
    // Different duty cycles 
    
    float dutyCycle = 0.2; 

    uint16_t highPeriod = 256 * dutyCycle; 
    uint16_t lowPeriod = (256 - highPeriod) / 2; 

    for(uint16_t i = 0; i < 256; i++)
    {
        wave[i] = (i < lowPeriod || i >= (256 - lowPeriod))? 0:1; 

    }
    #endif
      
    
    #ifdef SAWTOOTH_WAVE
    for(uint16_t i = 0; i < 256; i++)
    {
        wave[i] = (i <255) ? i : 0;
    }
    #endif
    
    #ifdef STEP_WAVE
        uint16_t stepDuration = 32; 
        for(uint16_t i = 0; i < 256; i++)
        {
            uint8_t level = i / stepDuration;
            wave[i] = level;
        }
    #endif

    
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
   
    for(;;)
    {
        if(UART_GetChar() == 's')
        {
           for(uint16_t i =0; i < 256;i++)
           {
                UART_PutChar(wave[i]);
           }
        }
    }
}

/* [] END OF FILE */