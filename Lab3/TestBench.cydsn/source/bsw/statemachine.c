/**
* \file joystick.c
* \author P. Fromm
* \date 29.8.17
*
* \brief Joystick driver
*
* \copyright Copyright �2016
* Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
* Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
* (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
* this paragraph and the following paragraph appear in all copies, modifications, and distributions.
* Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
*
* \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
* The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
* This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/

#include "statemachine.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/



/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/
void statemachine()
{
    static uint16_t adcArray[1024] = {0};
    static FFT_State_t state= IDLE;
    
    switch(state)
    {
        case IDLE:
        {          
            LED_RED_Write(1);
            LED_ORANGE_Write(0);
            LED_GREEN_Write(0);
            
            count = 0;
            if(buttonPressed == 1)
            {
                state = SAMPLING;
            }
            break;
        }
        case SAMPLING:
        {
            LED_RED_Write(0);
            LED_ORANGE_Write(1);
            LED_GREEN_Write(0);
            
            for(uint16_t i = 0; i < 1024; i++)
            {
                ADC_DelSig_IsEndConversion(ADC_DelSig_WAIT_FOR_RESULT);
                adcArray[i] = (uint16_t)ADC_DelSig_GetResult32();
            }
           
            if(charS)
            {
                state = UART_TRANSFER;
            }
            break;
        }
        case UART_TRANSFER:
        {
            LED_RED_Write(0);
            LED_ORANGE_Write(0);
            LED_GREEN_Write(1);
            
            for (uint16_t i = 0; i < 1024; i++) {
                UART_PutChar(adcArray[i]);
                UART_PutChar((adcArray[i] >> 8));
            }
            
            count++;
            if (charO) 
            {
                if (count < 10) 
                {
                    state = SAMPLING;
                    charO = 0;
                } 
                else if(count == 10)
                {
                    state = IDLE;
                    charO = 0;
                }
            }
            break;
        }
        default:
            state = IDLE;
        break;
    }
    
}

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/
