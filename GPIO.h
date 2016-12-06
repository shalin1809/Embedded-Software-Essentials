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
*   Description: Header file for GPIO interfaces
*               -PIR_init
*               -PIR_read
*
********************************************************/

#ifndef GPIO_H_
#define GPIO_H_

#include "MKL25Z4.h"


void PIR_init(void);

uint8_t PIR_read(void);

#endif
