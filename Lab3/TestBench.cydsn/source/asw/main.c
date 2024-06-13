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
#include "statemachine.h"
char charRx;
uint8_t charS = 0;
uint8_t charO = 0;
uint8_t buttonPressed = 0;

CY_ISR_PROTO(isr_UART)
{
    isr_UART_ClearPending();
    charRx = UART_GetChar();
    if(charRx == 's')
    {
        charS = 1;
    }
    else if(charRx == 'o')
    {
        charO = 1;
    }   
}
CY_ISR_PROTO(isr_pushButton)
{
    isr_pushButton_ClearPending();
    if( buttonPressed == 0 )
    {
        UART_PutString("Pressed");
        buttonPressed = 1;
    }
}
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_Init();
    WaveDAC8_Init();    
    ADC_DelSig_Init();
    UART_Start();
    WaveDAC8_Start();
    ADC_DelSig_Start();
    ADC_DelSig_StartConvert();

    isr_pushButton_StartEx(isr_pushButton);
    isr_UART_StartEx(isr_UART);
    
    UART_PutString("Lab3");
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    for(;;)
    {
        statemachine();
    }  
}

/* [] END OF FILE */
