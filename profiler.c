/******************************************************
*   File: profiler.c
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
*   Date Edited: 7 Dec 2016
*
*   Description: Source file for time profiling
*               -profiler_start
*               -profiler_stop
*               -TPM1_IRQHandler
*
********************************************************/

#include "profiler.h"
uint8_t overflow_counts=0;      

void start_profiling(void){
    SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;			// Enable TPM1 Clock gate
    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);			// Select MCGIRFLL clock 21 Mhz
    TPM1_SC=0;									// Disable Timer
    TPM1 -> MOD = 65535;								//Set Counter for 10 uS

    TPM1_SC |= TPM_SC_PS(0);	// Prescaler divide by 1
    __enable_irq();					// Enable global Interrupt
    NVIC_EnableIRQ(TPM1_IRQn);  	// Enable NVIC Interrupt
    TPM1_SC |= TPM_SC_TOIE_MASK; 	// Enable Timer Overflow Interrupt
    TPM1_SC |= TPM_SC_CMOD(1);      //start counter
}

float profiler_stop(void){
    //TPM1->SC =0x0;  //stop counter
    float time_spent = 0.0;
    uint32_t total_clocks = overflow_counts*65535 + TPM1->CNT;
    time_spent = total_clocks/21;
    return time_spent;
}

void TPM1_IRQHandler(void){
	if(TPM1_SC & TPM_SC_TOF_MASK)
	{
        TPM1->SC =0x0;  //stop counter
		TPM1->CNT = 0;
        overflow_counts++;					
		TPM1_SC &= ~TPM_SC_TOF_MASK;	//clear the tof bit by writing 1
        TPM1_SC |= TPM_SC_CMOD(1);      //start counter
	}
}
