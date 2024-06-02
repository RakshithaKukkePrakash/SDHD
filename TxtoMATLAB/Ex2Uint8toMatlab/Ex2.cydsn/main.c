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
#define TRIANGLE_WAVE 0

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_Start();
    uint16_t waveArray[256] = {0};
    UART_PutString("Exercise 2");
    
    #ifdef TRIANGLE_WAVE
        for(uint16_t rise =0; rise < 129;rise++)
        {
            waveArray[rise]=rise;            
        }
        for(uint16_t fall =129; fall <255;fall++)
        {
            waveArray[fall]=255-fall;
        }        
        
    #endif
    
    
    
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
   
    for(;;)
    {
        if(UART_GetChar() == 's')
        {
           for(uint16_t wave =0; wave < 256;wave++)
           {
                //UART_PutChar(waveArray[wave]);
                char log[20];
                itoa(waveArray[wave], log, 10);
                UART_PutString(log);
           }
        }
    }
}

/* [] END OF FILE */
