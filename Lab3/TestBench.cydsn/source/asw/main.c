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
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_Init();
    WaveDAC8_1_Init();    
    ADC_DelSig_1_Init();
      
    UART_PutString("Lab3");
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
}
CY_ISR(isr_ADC)
{
    
}
CY_ISR(isr_pushButton)
{
    if( Push_Button_Read() == 1)
    {
        statemachine();
    }
}
/* [] END OF FILE */
