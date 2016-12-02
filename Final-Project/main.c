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
*   Description: Source file for our final ESE project

********************************************************/

#include "MKL25Z4.h"
#include "adc.h"
#include "log.h"
#include "dac.h"
#include <stdint.h>

uint16_t result_TEMP;
uint16_t result_LDR;
uint32_t average_result_TEMP=0;
float voltage_TEMP = 0.0;
float temperature = 0.0;

int main (void)
{
/* Configure ADC0 */
ADC0_init();

//Configuring the UART module for logging
UART0_init();

//Calibrating the adc module
ADC0_calibrate();
DAC0_init(); /* Configure DAC0 */

while (1) {
	ADC0_calibrate();

/************************************************************
 * DAC buzzer
 ***********************************************************/
	int i,j;
	for (i = 0; i < 0x1000; i += 0x8000) {
	/* write value of i to DAC0 */

	DAC0->DAT[0].DATL = 0xff; /* write low byte */
	DAC0->DAT[0].DATH = 0x0f;
	for(j=0;j<500;j++){

	}
	}


/*************************************************************
* ADC conversions for LDR
*************************************************************/
#ifdef LDR
	ADC0->SC1[0] = 11; /* start conversion on channel 11 for LDR*/
	/* wait for COCO */
	while(!(ADC0->SC1[0] & 0x80)) { }
	/* read conversion result and clear COCO flag */
	result_LDR = ADC0->R[0];
	//logging the result
	LOG_1("\n\rADC value of LDR is :",23,(uint16_t)result_LDR,10);
#endif

/*************************************************************
* ADC conversions for Temperature sensor
*************************************************************/
#ifdef TEMP
	ADC0->SC1[0] = 14; /* start conversion on channel 14 for temp sensor*/
	/* wait for COCO */
	while(!(ADC0->SC1[0] & 0x80)) { }
	/* read conversion result and clear COCO flag */
	result_TEMP = ADC0->R[0];
	/*Taking an average */
	average_result_TEMP = mean_filter(result_TEMP);

	if(average_result_TEMP!=0){
		voltage_TEMP = (average_result_TEMP/65536.0) * 3.3;
		temperature = (voltage_TEMP - 0.5)/0.01;
		//Logging the result
		LOG_1("\n\rADC value of temp sensor is :",30,(uint16_t)average_result_TEMP,10);
		LOG_2("\n\rTemperature (in Celsius) is :",30,temperature,10);
	}
#endif
 }
}
