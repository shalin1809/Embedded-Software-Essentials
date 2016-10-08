/***************************************************


LEDs are Active Low in configuration. Thus setting the pin high will turn them off

*****************************************************/

#include "MKL25Z4.h"                    // Device header
#include "LED.h"
#include "uart.h"
#include "pwm.h"

void delay(int n);


int main () {
   
    char c = 0;
    char array[100] = {'\0'};
    UART0_init();
    PWM_init();
    LED_init(); 
    while (1) {
        UART0_WriteChar('H');
        UART0_WriteChar('e');
        UART0_WriteChar('l');
        UART0_WriteChar('l');
        UART0_WriteChar('o');
        UART0_WriteString("\n\rWorld");
        c = UART0_ReadChar();
        LED_Control(c);
        //UART0_ReadString(array);
        //UART0_WriteString(array);
    }
}





