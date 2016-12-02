/******************************************************
*   File: myrtc.h
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
*   Description: Header file for using Real time clock on KL25Z
*               -rtc_init
*               -RTC_Seconds_IRQHandler
*
********************************************************/

#include "MKL25Z4.h"
#include "stdint.h"


typedef struct myrtc_t {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
}rtc;

void rtc_init(void) ;

void RTC_Seconds_IRQHandler(void);
