/******************************************************
*   File: myrtc.c
*
*   Copyrights 2016 Snehal Sanghvi and Shalin Shah
*   All Rights Reserved
*
*   The information contained herein is property of the Authors.
*   The copying and distribution of the files is prohibited except
*   by express written agreement with the Authors.
*
*   Authors: Shalin Shah and Snehal Sanghvi 
*   Date Edited: 1 Dec 2016
*
*   Description: Source file for using Real time clock on KL25Z
*               -rtc_init
*               -RTC_Seconds_IRQHandler
*
********************************************************/

#include "myrtc.h"
#include "stdint.h"

struct myrtc_t myrtc;



























void UART0_init(void) {
    SIM_SCGC4 |= 0x00000400;            // enable clock for UART
    SIM_SOPT2 |= 0x04000000;            // use FLL output for UART
    UART0_C2 = 0x00000000;              // turn off UART0
    UART0_BDH = 0x00000000;             // Select BAUD rate as 57600
    UART0_BDL = 0x000000017;            // Select BAUD rate as 57600
    UART0_C4 = 0x0000000F;              // Over Sampling Ratio 16 
    UART0_C1 = 0x00000000;              // Select 8-bit mode 
    UART0_C2 = 0x0000002C;              // enable transmit and receive
    SIM_SCGC5 |= 0x00000200;            // enable clock for PORTA 
    //NVIC->ISER[0] = 0x000001000;        // enable IRQ12 which is for UART0
    PORTA_PCR1 = 0x00000200;            // Select PTA1 as Receive pin
    PORTA_PCR2 = 0x00000200;            // Select PTA2 as Transmit pin
}


char UART0_ReadChar(void){
    while(!(UART0->S1 & 0x20)) {}       //wait for receive buffer full
    return UART0_D;                     //Return the read buffer
}


void UART0_WriteChar(char BYTE){
    UART0_D = BYTE;       //send a char
    while(!(UART0->S1 & 0x40));             //Wait till transmit receive complete
    //UART0_C2 |= 0x00000080;              //Enable transmit interrupt 
}

void UART0_WriteString(char string[]){
    char * str = string;
    while(*str)                         //Print the string till a NULL character ending
        UART0_WriteChar(*str++);
    UART0_WriteChar('\n');              //Go to newlinc and return carriage after writing the string
    UART0_WriteChar('\r');
}

void UART0_ReadString(char * str){
    __disable_irq();
    while((*(str++) = UART0_ReadChar() )!= '\r')              //Take input till a newline character is received
    *str = '\0';                                            //End the string with a NULL character
    __enable_irq();
}





















void rtc_init() 
{   
    SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;      //Enable Port C
    UART0_init();
    
    MCG_C1 |= MCG_C1_IRCLKEN_MASK;      //Enable internal reference clock
	MCG_C2 &= ~(MCG_C2_IRCS_MASK);      //Internal Reference Clock Slow
	PORTC_PCR1 |= (PORT_PCR_MUX(0x1));              //PTC1 as RTC_CLKIN
    SIM_SOPT1 |= 0x00080000;                    //RTC_CLKIN selected for OSC32KCLK
    SIM_SOPT2 |= 0x00000080;                    //MCGIRCLK selected for clock out
    PORTC_PCR3 |= (PORT_PCR_MUX(0x5));              //PTC3 as CLKOUT
    
    
    __enable_irq();
    
    SIM_SCGC6 |= SIM_SCGC6_RTC_MASK;        //Enable the clock to RTC
    RTC_CR  = RTC_CR_SWR_MASK;              
    RTC_CR  &= ~RTC_CR_SWR_MASK;            //Disable and reset RTC
  
    if (RTC_SR & RTC_SR_TIF_MASK){          //Check if time invalid
        RTC_TSR = 0x00000000;               //Clears the Time invalid flag
    }
    
    RTC_TCR = RTC_TCR_CIR(1) | RTC_TCR_TCR(0xCF);   //Setup compensation parameters
  
    NVIC->ICPR[0] |= RTC_Seconds_IRQn;
    NVIC->ISER[0] |= RTC_Seconds_IRQn;              //Enable RTC interrupts
    
    RTC_IER |= RTC_IER_TSIE_MASK;                   //Seconds interrupt enable
    RTC_CR |= RTC_CR_OSCE_MASK;                     //Enable 32.768Hz oscillator
    RTC_SR |= RTC_SR_TCE_MASK;                      //Enable RTC
    RTC_TSR = 0xFF;                                 //Reset the seconds register
    

   
    UART0_WriteString("Hello");
    myrtc.seconds=0;
    myrtc.minutes=0;
    myrtc.hours=0;
}


void RTC_Seconds_IRQHandler(void) 
{
	myrtc.seconds = RTC_TSR;                      //Update seconds
    if (myrtc.seconds >59){
    	myrtc.minutes++;                          //Update minutes
        if(myrtc.minutes>59){
            myrtc.hours++;                        //Update hours
            myrtc.minutes=0;
            if(myrtc.hours>24)
                myrtc.hours = 0;
        }
    	RTC_SR &= ~RTC_SR_TCE_MASK;             //Disable RTC
    	RTC_TSR = 0x00;                         //Reset seconds
    	myrtc.seconds = 0;
    	RTC_SR |= RTC_SR_TCE_MASK;	            //Enable RTC
    }
            UART0_WriteChar((myrtc.minutes/10 + 48));
            UART0_WriteChar((myrtc.minutes%10 + 48));
            UART0_WriteChar('\t');
            UART0_WriteChar((myrtc.seconds/10 + 48));
            UART0_WriteChar((myrtc.seconds%10 + 48));
}

