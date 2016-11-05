/*
 * dma.h
 *
 *  Created on: 03-Nov-2016
 *  Author: Snehal Sanghvi
 */

#ifndef INCLUDES_DMA_H_
#define INCLUDES_DMA_H_

// function to write zeros to the array
void memzero_dma(uint16_t length);

//function to move data from one location to another
void memmove_dma(uint16_t length);

//initializing UART
void UART0_init();

// function to print out a character using UART
 void UART0_WriteChar(char byte);

 // function to print out a string using UART
 void UART0_WriteString(char string[]);

 // reverses a string 'arr' of length 'length'
 void reverse_string(char *arr, int length);

 // integer to ascii converter
 int my_itoa(char arr[], int number, int no_of_digits);

 // floating point to ascii converter
 void my_ftoa(char *arr, float number, int after_decimal_point);

 // implementing LOG_0 function, which is used to write data bytes onto the terminal
 void LOG_0(uint8_t * data, uint8_t len);

 //implementing LOG_1 function, which is a concatenation of the LOG_0 functionality with another parameter
 //the parameter can only be a an integer for this function
 void LOG_1(uint8_t * data, uint8_t len, uint32_t param, uint8_t data_type_size);

 //implementing LOG_2 function, which has the same functionality of LOG_1 but the parameter is a floating type
 void LOG_2(uint8_t * data, uint8_t len, float param, uint8_t data_type_size);

 //starting the profiler function for KL25z
 void start_profiling(void);

 //function to stop the timer and print out the clock cycles
 void profiler_stop(void);



#endif /* INCLUDES_DMA_H_ */
