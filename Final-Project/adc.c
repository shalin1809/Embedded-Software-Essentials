/********************************************
*   File: adc.c
*
*   Copyrights 2016 Snehal Sanghvi and Shalin Shah
*   All Rights Reserved
*
*   The information contained herein is property of the Authors.
*   The copying and distribution of the files is prohibited except
*   by express written agreement with the Authors.
*
*   Author: Snehal Sanghvi and Shalin Shah
*   Date Edited: 26 Nov 2016
*
*   Description: Source file for ADC module
*                -ADC0_init
*                -ADC0_calibrate

********************************************************/

#include "MKL25Z4.h"

//This function initializes the ADC module
void ADC0_init(void)
{
SIM->SCGC5 |= 0x0800; /* clock to PORTC */
PORTC->PCR[0] = 0; /* PTC0 analog input for LDR */

/* clock to ADC0 */
SIM->SCGC6 |= 0x8000000;
/* software trigger */
ADC0->SC2 &= ~0x40; 
/* clock div by 4, long sample time, single ended 16 bit, bus clock */
ADC0->CFG1 = 0x40 | 0x10 | 0x0C | 0x00;
}

//function to calibrate the ADC module
int ADC0_calibrate(void)
{
	ADC0_CFG1 |= (ADC_CFG1_MODE(3)  |  	// 16 bits mode
				  ADC_CFG1_ADICLK(1)|	// Input Bus Clock divided by 2 (20-25 MHz out of reset (FEI mode) / 2)
				  ADC_CFG1_ADIV(2)) ;	// Clock divide by 4 (2.5-3 MHz)

	ADC0_SC3 |= ADC_SC3_AVGE_MASK |		// Enable HW average
				ADC_SC3_AVGS(3)   |		// Set HW average of 32 samples
				ADC_SC3_CAL_MASK;		// Start calibration process

	while(ADC0_SC3 & ADC_SC3_CAL_MASK); // Wait for calibration to end

	if(ADC0_SC3 & ADC_SC3_CALF_MASK)	// Check for successful calibration
		return 1;

	uint16_t calib = 0; // calibration variable
	calib += ADC0_CLPS + ADC0_CLP4 + ADC0_CLP3 + ADC0_CLP2 + ADC0_CLP1 + ADC0_CLP0;
	calib /= 2;
	calib |= 0x8000; 	// Set MSB
	ADC0_PG = calib;
	calib = 0;
	calib += ADC0_CLMS + ADC0_CLM4 + ADC0_CLM3 + ADC0_CLM2 + ADC0_CLM1 + ADC0_CLM0;
	calib /= 2;
	calib |= 0x8000;	// Set MSB
	ADC0_MG = calib;

	return 0;
}
