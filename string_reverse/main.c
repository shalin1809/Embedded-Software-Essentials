/*************************************************** 
 * File to test string reversal function 
 * Copyright of Company* 
 * All Rights Reserved** 
 * The information contained herein is confidential 
 * property of Company. The use, copying, transfer or 
 * disclosure of such information is prohibited except
 * by express written agreement with Company.
 * 
 * Author - Shalin Shah
 * 
 **********************************************/
#include<stdio.h>
#include"reverse.h"
#include<string.h>
int main()
{
    char arr[] = "This is a string";
    int i = reverse_string(arr,strlen(arr));
    if(i!=0)
    printf("Error code %d\n",i); //Print error code if any
    else
    printf("%s\n",arr);            //Print the reversed string if no errors
    
    char arr2[] = "some NUMmbers12345";
    i = reverse_string(arr,strlen(arr));
    if(i!=0)
    printf("Error code %d\n",i); //Print error code if any
    else
    printf("%s\n",arr2);         //Print the reversed string if no errors
    
    char arr3[] = "Does it reverse \n\0\t correctly?";
    i = reverse_string(arr,strlen(arr));
    if(i!=0)
    printf("Error code %d\n",i); //Print error code if any
    else
    printf("%s\n",arr3);           //Print the reversed string if no errors
    
    return 0;
}
