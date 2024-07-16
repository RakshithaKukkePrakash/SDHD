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
#include "fft_application.h"


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    uint16 adcArray[SAMPLES] = {0};

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    init_func();
    for(;;)
    {
        statemachine(adcArray);
        //statemachine_cfar(adcArray);
    }  
}

/* [] END OF FILE */
