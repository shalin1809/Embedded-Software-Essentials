/********************************************
*   File: adc.h
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
*   Description: Header file for ADC module
*                -ADC0_init
*                -ADC0_calibrate

********************************************************/

#ifndef INCLUDES_ADC_H_
#define INCLUDES_ADC_H_

//This function initializes the ADC module
void ADC0_init(void);

//function to calibrate the ADC module
int ADC0_calibrate(void);


#endif /* INCLUDES_ADC_H_ */
