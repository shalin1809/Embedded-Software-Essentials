/***************************************************


LEDs are Active Low in configuration. Thus setting the pin high will turn them off

*****************************************************/

#include "MKL25Z4.h"                    // Device header
#include "LED.h"
#include "uart.h"
#include "pwm.h"
#include "log.h"

void delay(int n);

int main () {
   
    char c = 0;
    //char array[100] = {'\0'};
    UART0_init();
    PWM_init();
    LED_init(); 
    //while (1) {
/*        UART0_WriteChar('H');
        UART0_WriteChar('e');
        UART0_WriteChar('l');
        UART0_WriteChar('l');
        UART0_WriteChar('o');
        UART0_WriteString("\r\nWorld");*/
//        c = UART0_ReadChar();
//        LED_Control(c);
    LOG_0("\r\nTesting123,Serial Print Test,no params\r\n", 42);
    LOG_1("\r\nThis is an integer number: ",32,200,8);
    LOG_1("\r\nThis is an integer number: ",32,4096,16);
    LOG_1("\r\nThis is an integer number: ",32,123456,32);
    LOG_2("\r\nThis is a floating point number: ",35,1543.321, sizeof(1543.321));
        //UART0_ReadString(array);
        //UART0_WriteString(array);
    //}
}

