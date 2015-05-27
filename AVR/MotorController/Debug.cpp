/*
 * Debug.c
 * Author: Jason Lefley
 * Date  : 2015-05-01
 * Description: Debug output setup
 */

#ifdef DEBUG

#include <avr/io.h> // uart.h needs RAMEND

#include "Debug.h"
#include "canonical_machine.h"
#include "uart.h"

#define UART_BAUD_RATE 9600

static FILE uartStream;

/*
 * stdio specific putc function to interface with uart
 * Conversion of new line characters to appropriate serial newline and/or
 * carriage return sequence can be done here if desired
 * See example at http://www.nongnu.org/avr-libc/user-manual/group__avr__stdio.html
 */

int UARTPutChar(char c, FILE* stream)
{
    uart_putc(c);
    return 0;
}

/*
 * Initialize uart and direct standard out and standard error to uart
 */

void Debug::Initialize()
{
    uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
    fdev_setup_stream(&uartStream, UARTPutChar, NULL, _FDEV_SETUP_WRITE);
    stdout = &uartStream;
    stderr = &uartStream;
}

/*
 * Print a summary of the canonical machine state flags
 */

void Debug::PrintCMState()
{
    printf_P(PSTR("DEBUG: Current cm state:\n"));
    printf_P(PSTR("    cycle_state: %d\n"), cm_get_cycle_state());
    printf_P(PSTR("    motion_state: %d\n"), cm_get_motion_state());
    printf_P(PSTR("    hold_state: %d\n"), cm_get_hold_state());
}

#endif /* DEBUG */