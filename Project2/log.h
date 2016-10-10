/*
 * log.h
 *
 *  Created on: 10-Oct-2016
 *      Authors: Snehal Sanghvi and Shalin Shah
 */
#include <stdint.h>

#ifndef INCLUDES_LOG_H_
#define INCLUDES_LOG_H_


// reverses a string 'arr' of length 'length'
void reverse_string(char *arr, int length);

// integer to ascii converter
int my_itoa(char arr[], int number, int no_of_digits);

// floating point to ascii converter
void my_ftoa(char *arr, float number, int after_decimal_point);

// LOG_0 function is used to write data bytes onto the terminal
void LOG_0(uint8_t * data, uint8_t len);

//LOG_1 function is a concatenation of the LOG_0 functionality with another parameter
//the parameter can only be a an integer for this function
void LOG_1(uint8_t * data, uint8_t len, uint32_t param, uint8_t data_type_size);

//implementing LOG_2 function, which has the same functionality of LOG_1 but the parameter is a floating type
void LOG_2(uint8_t * data, uint8_t len, float param, uint8_t data_type_size);


#endif /* INCLUDES_LOG_H_ */
