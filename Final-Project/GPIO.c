/******************************************************
*   File: gpio.c
*
*   Copyrights 2016  Snehal Sanghvi and Shalin Shah
*   All Rights Reserved
*
*
*   The information contained herein is property of the Authors. 
*   The copying and distribution of the files is prohibited except
*   by express written agreement with the Authors.
*
*
*   Authors: Shalin Shah and Snehal Sanghvi
*   Date Edited: 5 Dec 2016
*
*   Description: Source file for GPIO interfaces
*               -PIR_init
*               -PIR_read
*
********************************************************/


#include "GPIO.h"

void PIR_init(void){
    SIM_SCGC5 |= 0x00002000;            // enable clock to Port E
    PORTE_PCR29 = PORT_PCR_MUX(1);      // set PTE29 pin as GPIO
    PTE->PDDR &= ~(0x20000000);         // set PTE29 as input pin for PIR
}

uint8_t PIR_read(void){
    return ((GPIOE_PDIR & 0x20000000)>>29);
}

