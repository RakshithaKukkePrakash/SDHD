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

int main()
{
    /* Step 1 - Hello and talk back
    uint8 ch;
    // Start SCB UART TX+RX operation 
    UART_Start();
    // Transmit String through UART TX Line 
    UART_PutString("CY8CKIT-044 USB-UART");
    for(;;)
    {
        // Get received character or zero if nothing has been received yet 
        ch = UART_GetChar();
        if(0u != ch)
        {
        // Send the data through UART. This functions is blocking and waits until there is an entry into the TX FIFO.
        UART_PutChar(ch);
        }
    }
    */
    
    // Step 2 - Capitalize and talk back
    uint8_t rx_char = 0;
    UART_Start();
    for(;;)
    {
        // Method 1
        // Get received character or zero if nothing has been received yet 
        rx_char = UART_GetChar();
        /*if(rx_char != 0)
        {
            if(rx_char >= 'a' && rx_char <= 'z')
            {
            // Send the data through UART. This functions is blocking and waits until there is an entry into the TX FIFO.
            rx_char-= 32;
            }
            UART_PutChar(rx_char);
        } */
        // Method 2
        if(rx_char != 0)
        {
            UART_PutChar(toupper(rx_char));
        }
    }
}

/* [] END OF FILE */
