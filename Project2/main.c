/***************************************************


LEDs are Active Low in configuration. Thus setting the pin high will turn them off

*****************************************************/

#include "MKL25Z4.h"                    // Device header
#include "LED.h"
#include "uart.h"
#include "pwm.h"
#include "Circular_buffer.h"

char c;                                 //Global variable to read or write UART0
char array[100] = {'\0'};               //Global array to read string UART0
char byte;

void Control(char a){
    if(a == 'i')
        UART0_ReadString(array);
    else 
        LED_Control(a);
}

void UART0_WriteChar(char BYTE){
    byte = BYTE;
    UART0_C2 |= 0x00000080;              //Enable transmit interrupt
    //while(!(UART0->S1 & 0xC0));
    
}

int main () {
    __disable_irq();
    UART0_init();
    PWM_init();
    LED_init();
    __enable_irq();    
    

    
    while (1) {
        UART0_WriteChar('H');
        UART0_WriteChar('e');
        UART0_WriteChar('l');
        UART0_WriteChar('l');
        UART0_WriteChar('o');
        UART0_WriteString("\n\rWorld 123");
        
        //UART0_ReadString(array);
        //UART0_WriteString(array);
    }
}

void UART0_IRQHandler(){
    if(UART0->S1 & 0x20){
        c = UART0_D;                            //Interrupt caused by receiver
        Control(c);
    }
    else if (UART0->S1 & 0x80){                 //Interrupt caused by transmitter
        UART0_D = byte;                         //send a char
        UART0_C2 &= 0x7F;                       //Clear transmit receive interrupt flag
        while(!(UART0->S1 & 0x40));             //Wait till transmit receive
    }
}
