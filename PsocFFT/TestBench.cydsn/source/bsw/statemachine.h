/**
* \file statemachine.h
* \author 
* \date 
*
* \brief 
*
*
* \note <notes>
* Programming rules (may be deleted in the final release of the file)
* ===================================================================
*
* 1. Naming conventions:
*    - Prefix of your module in front of every function and static data. 
*    - Scope _ for public and __ for private functions / data / types, e.g. 
*       Public:  void CONTROL_straightPark_Init();
*       Private: static void CONTROL__calcDistance();
*       Public:  typedef enum {RED, GREEN, YELLOW} CONTROL_color_t
*    - Own type definitions e.g. for structs or enums get a postfix _t
*    - #define's and enums are written in CAPITAL letters
* 2. Code structure
*    - Be aware of the scope of your modules and functions. Provide only functions which belong to your module to your files
*    - Prepare your design before starting to code
*    - Implement the simple most solution (Too many if then else nestings are an indicator that you have not properly analysed your task)
*    - Avoid magic numbers, use enums and #define's instead
*    - Make sure, that all error conditions are properly handled
*    - If your module provides data structures, which are required in many other files, it is recommended to place them in a file_type.h file
*	  - If your module contains configurable parts, is is recommended to place these in a file_config.h|.c file
* 3. Data conventions
*    - Minimize the scope of data (and functions)
*    - Global data is not allowed outside of the signal layer (in case a signal layer is part of your design)
*    - All static objects have to be placed in a valid linker sections
*    - Data which is accessed in more than one task has to be volatile and needs to be protected (e.g. by using messages or semaphores)
*    - Do not mix signed and unsigned data in the same operation
* 4. Documentation
*    - Use self explaining function and variable names
*    - Use proper indentation
*    - Provide Javadoc / Doxygen compatible comments in your header file and C-File
*    		- Every  File has to be documented in the header
*			- Every function parameter and return value must be documented, the valid range needs to be specified
*     		- Logical code blocks in the C-File must be commented
*    - For a detailed list of doxygen commands check http://www.stack.nl/~dimitri/doxygen/index.html 
* 5. Qualification
*    - Perform and document design and code reviews for every module
*    - Provide test specifications for every module (focus on error conditions)
*
* Further information:
*    - Check the programming rules defined in the MIMIR project guide
*         - Code structure: https://fromm.eit.h-da.de/intern/mimir/methods/eng_codestructure/method.htm
*         - MISRA for C: https://fromm.eit.h-da.de/intern/mimir/methods/eng_c_rules/method.htm
*         - MISRA for C++: https://fromm.eit.h-da.de/intern/mimir/methods/eng_cpp_rules/method.htm 
*
* \todo <todos>
* \warning <warnings, e.g. dependencies, order of execution etc.>
*
*  Changelog:\n
*  - <version; data of change; author>
*            - <description of the change>
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


 
#ifndef STATEMACHINE_H
#define STATEMACHINE_H

    
/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/
#include "project.h"
#include "fft_application.h"
     
// Define the number of samples for the ADC and FFT
#define SAMPLES 1024
#define N 512 // Number of Samples
#define NG 1  // Number of Guard Cells
#define NR 10 // Number of Reference Cells
#define PFA 1e-6 // Probability of False Alarm
/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

// Enumeration to represent the states of the state machine
typedef enum {
    IDLE,          // Idle state
    SAMPLING,      // Sampling state
    UART_TRANSFER  // UART transfer state
} FFT_State_t;

/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/*
 * init_func function initializes all the Hardware used in the top design.
 * @param : None
 * @return : None
 */
void init_func();
void ca_cfar(int32 *fft_result, int32_t *threshold_cfar, int32_t *signal_cfar);
void uart_transfer(uint16_t *adcArray, int32 *fftArray);
/*
 * statemachine function to handle the state transitions and actions.
 * @param : uint16_t *adcArray - Pointer to the array to store ADC samples.
 * @return : None
 */
void statemachine(uint16_t *adcArray);
void statemachine_cfar(uint16_t *adcArray);
/*
 * Interrupt function that sets 'charS' and 'charO' variable to 1 if the UART 
 * receives 's' and 'o' characters respectively from the MATLAB script.
 */
CY_ISR_PROTO(isr_UART);


/*
 * Interrupt function that sets a buttonPressed variable to 1 if the PushButton is pressed.
 */
CY_ISR_PROTO(isr_pushButton);


#endif /* FILE_H */
