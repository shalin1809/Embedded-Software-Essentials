/******************************************************
*   File: profiler.h
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
*   Description: Header file for time profiling
*               -profiler_start
*               -profiler_stop
*               -TPM1_IRQHandler
*
********************************************************/
#ifndef PROFILER_H_
#define PROFILER_H_

#include "MKL25Z4.h"

void start_profiling(void);

float profiler_stop(void);

void TPM1_IRQHandler(void);

#endif
