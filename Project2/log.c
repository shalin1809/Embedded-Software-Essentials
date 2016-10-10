/*
 * log.c
 *
 *  Created on: 10-Oct-2016
 *      Authors: Snehal Sanghvi and Shalin Shah
 */

#include <stdio.h>
#include "log.h"
#include "uart.h"


// reverses a string 'arr' of length 'length'
void reverse_string(char *arr, int length)
{
	int i=0, temp;
	while (i<length-1)
	{
		temp = *(arr+i);
		*(arr + i) = *(arr + length - 1 - i);
		*(arr + length - 1 - i) = temp;
		i++;
	}
}


// integer to ascii converter
int my_itoa(char arr[], int number, int no_of_digits)
{
	int i = 0;
	int digit = 0;

    //taking care of negative digits
	if(number<0)
	{	digit = -1;
		number = -number;
	}

    //dividing the number till it is not 0
	while (number!=0)
	{
		*(arr+i) = (number % 10) + '0';
		i++;
		number = number/10;
	}

	if(digit==-1){
		*(arr+i) = '-';
		i++;
	}

	//performing padding manipulations so that the zeros after decimal point are not lost
	while (i < no_of_digits)
	{	*(arr+i) = '0';
		 i++;
	}

    //reversing string so as to print it in correct order
	reverse_string(arr, i);
	*(arr+i) = '\0';
	return i;
}


// floating point to ascii converter
void my_ftoa(char *arr, float number, int after_decimal_point)
{
	// Extract integer part
	int integer_part = (int)number;

	// Extract floating part
	float floating_part = number - (float)integer_part;

	// convert integer part to string
	int i = my_itoa(arr, integer_part, 0);


	if (after_decimal_point != 0)
	{
		*(arr+i) = '.';

		// manipulations to implement the power function in math.h
        int dp = after_decimal_point;
        int a = 1;
        while(dp!=0){
            a = a*10;
            dp--;
        }

		floating_part = floating_part * a;
		my_itoa(arr + i + 1, (int)floating_part, after_decimal_point);

	}
}


// implementing LOG_0 function, which is used to write data bytes onto the terminal
void LOG_0(uint8_t * data, uint8_t len)
{
	for (int i=0; i<len; i++){
		UART0_WriteChar(*data);
		data++;
	}
}


//implementing LOG_1 function, which is a concatenation of the LOG_0 functionality with another parameter
//the parameter can only be a an integer for this function
void LOG_1(uint8_t * data, uint8_t len, uint32_t param, uint8_t data_type_size)
{
	LOG_0(data, len);
	char str[50];
	my_itoa(str, param, 0);
	LOG_0(str, data_type_size);
}


//implementing LOG_2 function, which has the same functionality of LOG_1 but the parameter is a floating type
void LOG_2(uint8_t * data, uint8_t len, float param, uint8_t data_type_size)
{
	LOG_0(data, len);
	char str[50];
	my_ftoa(str, param, 6);	//6 digits of precision after decimal point
	LOG_0(str, sizeof(param)); //using sizeof since the size of float maybe different on different architectures
}
