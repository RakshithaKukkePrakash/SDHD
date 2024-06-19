/**
* \file statemachine.c
* \author 
* \date 
*
* \brief 
*
* \copyright Copyright ©2016
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

// State machine's initial state
FFT_State_t state = IDLE;

// Variable to store received character from UART
char charRx;

// Counter variable
uint8_t count = 0;

// Flags to indicate reception of specific characters, 's' and 'o'
uint8_t charS = 0;
uint8_t charO = 0;

// Flag to indicate button press (Note: volatile to handle changes in interrupt)
volatile uint8_t buttonPressed = 0;

// Array to store the result of the FFT calculation
//int32 fftArray[2 * SAMPLES] = {0}; 

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

/*
 * init_func function initializes all the Hardware used in the top design.
 * @param : None
 * @return : None
 */
void init_func()
{
    // Start UART communication
    UART_Start();

    // Start Wave DAC (Digital-to-Analog Converter)
    WaveDAC_Start();

    // Start ADC (Analog-to-Digital Converter)
    ADC_DelSig_Start();

    // Start ADC conversion
    ADC_DelSig_StartConvert();

    // Start interrupt service routine for push button
    isr_pushButton_StartEx(isr_pushButton);

    // Start interrupt service routine for UART
    isr_UART_StartEx(isr_UART);
}

/*
 * Interrupt function that sets 'charS' and 'charO' variable to 1 if the UART 
 * receives 's' and 'o' characters respectively from the MATLAB script.
 */
CY_ISR(isr_UART)
{
    // Clear pending UART interrupt
    isr_UART_ClearPending();

    // Get character from UART
    charRx = UART_GetChar();

    // Check if received character is 's'
    if (charRx == 's') {
        charS = 1;
    }

    // Check if received character is 'o'
    if (charRx == 'o') {
        charO = 1;
    }   
}

/*
 * Interrupt function that sets a buttonPressed variable to 1 if the PushButton is pressed.
 */
CY_ISR(isr_pushButton)
{
    // Clears any active interrupts attached with the component and returns 
    //  the value of the interrupt status register allowing determination of which
    //  pins generated an interrupt event.
    Push_Button_ClearInterrupt();

    // Set buttonPressed flag if not already set
    if (buttonPressed == 0) {
        buttonPressed = 1;
    }
}

/*
 * statemachine function to handle the state transitions and actions.
 * @param : uint16_t *adcArray - Pointer to the array to store ADC samples.
 * @return : None
 */
void statemachine(uint16_t *adcArray)
{
    switch (state)
    {
        case IDLE:
            // Turn on red LED to indicate IDLE state
            LED_RED_Write(1);
            LED_ORANGE_Write(0);
            LED_GREEN_Write(0);

            // Reset counter
            count = 0;  

            // If button is pressed, transition to SAMPLING state
            if (buttonPressed == 1) {
                state = SAMPLING;
                buttonPressed = 0;
            }
            break;
        
        case SAMPLING:
            
            // Turn on orange LED to indicate SAMPLING state
            LED_RED_Write(0);
            LED_ORANGE_Write(1);
            LED_GREEN_Write(0);
            
            
            // Sample ADC values and store in adcArray
            for (uint16_t i = 0; i < 1024; i++) {
                ADC_DelSig_IsEndConversion(ADC_DelSig_WAIT_FOR_RESULT);
                adcArray[i] = (uint16_t)ADC_DelSig_GetResult32();
            }

            // If 's' character received, transition to UART_TRANSFER state
            if (charS) {
                state = UART_TRANSFER;
                charS = 0;
            }
            break;
        
        case UART_TRANSFER:
            
            // Turn on green LED to indicate UART_TRANSFER state
            LED_RED_Write(0);
            LED_ORANGE_Write(0);
            LED_GREEN_Write(1);
            
            // Send ADC samples over UART
            for (uint16_t i = 0; i < 1024; i++) {
                UART_PutChar(adcArray[i]);
                UART_PutChar(adcArray[i] >> 8);
            }
            /*
            // Perform FFT on the ADC samples
            fft_app(adcArray, fftArray, 1024);

            // Send FFT results over UART
            for (uint32_t i = 0; i < 2048; i++) {
                UART_PutChar(fftArray[i]);
                UART_PutChar(fftArray[i] >> 8);
                UART_PutChar(fftArray[i] >> 16);
                UART_PutChar(fftArray[i] >> 24);
            }
            */
            // Increment count
            count++;                      
            
            // Check if 'o' character received
            if (charO) {
                if (count < 10) {  
                    // If count is less than 10, return to SAMPLING state
                    state = SAMPLING;
                    charO = 0;
                } else if (count == 10) {
                    // If count is 10, return to IDLE state
                    state = IDLE;  
                    charO = 0;
                }
            }
            break;
        
        default:
            // Default to IDLE state
            state = IDLE;
            break;
    }
}

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/
