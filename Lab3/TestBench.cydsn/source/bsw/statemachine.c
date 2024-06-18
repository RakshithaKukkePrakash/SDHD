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


FFT_State_t state= IDLE;
char charRx;
uint8_t count = 0;
uint8_t charS = 0;
uint8_t charO = 0;
volatile uint8_t buttonPressed = 0; 


// An array to store the result of the FFT calculation
int32 fftArray[2 * 1024] = {0}; 

/*
 * init_func function initializes all the Hardware used in the top design.
 * @param : None
 * @return : None
 */
void init_func()
{
    UART_Start();
    WaveDAC_Start();
    ADC_DelSig_Start();
    ADC_DelSig_StartConvert();
    isr_pushButton_StartEx(isr_pushButton);
    isr_UART_StartEx(isr_UART);
}
/*
 * Interrupt function that sets 'charS' and 'charO' variable to 1 if the UART 
 * recieves an 's' and 'o' characters respectively from the MATLAB script.
 */
CY_ISR(isr_UART)
{
    //isr_UART_ClearPending();
    charRx = UART_GetChar();
    if(charRx == 's')
    {
        charS = 1;
    }
    if(charRx == 'o')
    {
        charO = 1;
    }   
}

/*
 * Interrupt function that sets a buttonPressed variable to 1 if the PushButton is pressed.
 */
CY_ISR(isr_pushButton)
{
    Push_Button_ClearInterrupt();
    if(buttonPressed == 0)
    {
        buttonPressed = 1;
    }
}

/*
 * statemachine function initializes all the Hardware used in the top design.
 * @param : None
 * @return : None
 */
void statemachine(uint16_t *adcArray)
{
    switch(state)
    {
        case IDLE:
                 
            
            LED_RED_Write(1);
            /*
            LED_ORANGE_Write(0);
            LED_GREEN_Write(0);
            */
            count = 0;  
            //UART_PutString("Idle");
            if(buttonPressed == 1)
            {
                //UART_PutString("Idle to Samp");
                state = SAMPLING;
                buttonPressed = 0;
            }
        break;
        
        case SAMPLING:


            for(uint16_t i = 0; i < 1024; i++)
            {
                ADC_DelSig_IsEndConversion(ADC_DelSig_WAIT_FOR_RESULT);
                adcArray[i] = (uint16_t)ADC_DelSig_GetResult32();
            }
            if(charS)
            {
                //UART_PutString("Samp to UART");
                state = UART_TRANSFER;
                charS = 0;
            }
            break;
        
        case UART_TRANSFER:

            for (uint16_t i = 0; i < 1024; i++) {
                UART_PutChar(adcArray[i]);
                UART_PutChar(adcArray[i] >> 8);
            }
            
//            fft_app(adcArray, fftArray, 1024);
            /*
            for (uint32_t i = 0; i < 2048; i++) {
                UART_PutChar(fftArray[i]);
                UART_PutChar(fftArray[i] >> 8);
                UART_PutChar(fftArray[i] >> 16);
                UART_PutChar(fftArray[i] >> 32);
            }
            */
            count++;                      
            
            if(charO)
            {
                if(count < 10)
                {  
                    //UART_PutString("UART to Samp");
                    state = SAMPLING;
                    charO = 0;
                }
                else if(count == 10)
                {
                    //UART_PutString("UART to IDLE");
                    state = IDLE;  
                    charO = 0;
                }
            }
            break;
        
        default:
            state = IDLE;
        break;
    }
    
}

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/
