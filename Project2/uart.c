
#include "MKL25Z4.h"                    // Device header
#include "uart.h"



void UART0_init(void) {
    SIM_SCGC4 |= 0x00000400;            // enable clock for UART
    SIM_SOPT2 |= 0x04000000;            // use FLL output for UART
    UART0_C2 = 0x00000000;              // turn off UART0
    UART0_BDH = 0x00000000;             // Select BAUD rate as 115200
    UART0_BDL = 0x0000000B;             // Select BAUD rate as 115200
    UART0_C4 = 0x0000000F;              // Over Sampling Ratio 16 
    UART0_C1 = 0x00000000;              // Select 8-bit mode 
    UART0_C2 = 0x0000000C;              // enable transmit and receive
    SIM_SCGC5 |= 0x00000200;            // enable clock for PORTA 
    PORTA_PCR1 = 0x00000200;            // Select PTA1 as Receive pin
    PORTA_PCR2 = 0x00000200;            // Select PTA2 as Transmit pin
}


char UART0_ReadChar(void){
    while(!(UART0->S1 & 0x20)) {}       //wait for receive buffer full
    return UART0_D;                     //Return the read buffer
}


__inline void UART0_WriteChar(char byte){
    while(!(UART0->S1 & 0xC0)){}        // Wait till transmit buffer empty and Transmit complete
    UART0_D = byte;                     // send a char
}

void UART0_WriteString(char string[]){
    char * str = string;
    while(*str)                         //Print the string till a NULL character ending
        UART0_WriteChar(*str++);
    UART0_WriteChar('\n');              //Go to newlinc and return carriage after writing the string
    UART0_WriteChar('\r');
}

void UART0_ReadString(char * str){
    while((*(str) = UART0_ReadChar() )!= '\r')              //Take input till a newline character is received
        UART0_WriteChar(*str++);                            //Echo the character on the Terminal
    *str = '\0';                                            //End the string with a NULL character
}
