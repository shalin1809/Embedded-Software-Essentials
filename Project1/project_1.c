/********************************************
*   File: project_1.c
*
*   Copyrights 2016 Shalin Shah and Snehal Sanghvi
*   All Rights Reserved
*
*
*   The information contained herein is property of the Authors. 
*   The copying and distribution of the files is prohibited except
*   by express written agreement with the Authors.
*
*
*   Authors: Shalin Shah and Snehal Sanghvi
*   Date Edited: 17 Sept 2016
*
*   Description: Source file for the testing functions for project
*               -project_1_report
*
*
*
********************************************************/

#ifndef NULL
#define NULL '\0'
#endif

#include "project_1.h"
#include "stdio.h"
#include "stdint.h"
#include "memory.h"
#include "data.h"

/*
Mandatory function required for project report
*/
void project_1_report(){
    
    //Create an array of 32 bytes
    uint8_t TestArray[32]={};
    #define LENGTH 32
    
    //Create three pointers to various points in this array
    uint8_t * aptr_1 = TestArray;        //Initializing aptr_1 to the first element of the array
    uint8_t * aptr_2 = (aptr_1 + 9);     //Initializing aptr_2 to the 9th element of the array
    uint8_t * aptr_3 = (aptr_1 +17);     //Initializing aptr_3 to the 16th element of the array
    
    //Initialize memory at two of the pointers
    int count = 16;                 //Set count value
    while(count--)
        *(aptr_1+count-1)=(31+count-1);    //Put value of the first 16 bytes as 31-46 respectively
        
    my_memzero(aptr_3,16);           //Using my_memzero to set the remaining values of the array to '0'
    
    //Use memmove to move 8 bytes from aptr_1 to aptr_3
    #define LENGTH8 8
    uint8_t Error = my_memmove(aptr_1,aptr_3,LENGTH8);
    if(Error!=0)
        printf("\n Error code %d",Error);            //Print error if memmove fails
    
    //Use memmove to move 16 bytes from aptr_2 to aptr_1
    #define LENGTH16 16
    Error = my_memmove(aptr_2,aptr_1,LENGTH16);
    if(Error!=0)
        printf("\n Error code %d",Error);            //Print error if memmove fails
    
    //Use reverse on aptr_1 to reverse the entire 32 byte array
    Error = my_reverse(aptr_1,LENGTH);
    if(Error!=0)
        printf("\n Error code %d",Error);            //Print error if reverse fails
    
    
    //Print the entire 32 byte array
    printf("\n The new modified array is:%s",TestArray);
    
}


