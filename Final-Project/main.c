/********************************************
*   File: main.c
*
*   Copyrights 2016 Snehal Sanghvi and Shalin Shah
*   All Rights Reserved
*
*   The information contained herein is property of the Authors.
*   The copying and distribution of the files is prohibited except
*   by express written agreement with the Authors.
*
*
*   Author: Snehal Sanghvi and Shalin Shah
*   Date Edited: 26 Nov 2016
*
*   Description: main.c file for our final ESE project

********************************************************/

#include "MKL25Z4.h"
#include "adc.h"
#include "log.h"
#include <stdint.h>

int main (void)
{
uint16_t result;

/* Configure ADC0 */
ADC0_init();

//Configuring the UART module for logging
UART0_init();

//Calibrating the adc module
adc_cal();

while (1) {
	adc_cal();

	ADC0->SC1[0] = 14; /* start conversion on channel 14 for LDR*/

	/* wait for COCO */
	while(!(ADC0->SC1[0] & 0x80)) { }

	/* read conversion result and clear COCO flag */
	result = ADC0->R[0];

	//Logging the result
	LOG_1("\n\rADC value is :",16,(uint16_t)result,8);
 }
}
