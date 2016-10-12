/******************************************************
*   File: Circular_buffer.c
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
*   Authors: Snehal Sanghvi and Shalin Shah
*   Date Edited: 8 Oct 2016
*
*   Description: Source file for implementing Circular buffer functions
*               -is_Buffer_empty 
*               -is_Buffer_full
*               -add_item
*               -remove_item
*               -initialize_Buffer
*               -destroy
*
********************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "Circular_buffer.h"
 
    
uint8_t no_of_tests = 0;
uint8_t pass = 0;
uint8_t fail = 0;


// This function checks if the buffer is empty
enum bufferStates is_Buffer_empty(CircBuf_t *circ_ptr){
	if(circ_ptr -> count == 0){
		return Buffer_Empty;
	}
	else{
		return Buffer_Ok;
	}
}


// This function checks if the buffer is full
enum bufferStates is_Buffer_full(CircBuf_t *circ_ptr){
	if(circ_ptr -> count == MAX_SIZE){
		return Buffer_Full;	
	}
	return Buffer_Ok;
}


// This function adds an item to the buffer array
enum bufferStates add_item(CircBuf_t *circ_ptr, uint8_t item){

	if(is_Buffer_full(circ_ptr) == Buffer_Full)	{			      // if buffer is full, return a buffer full error
        //printf("\nCannot add any more elements! Buffer is full.\n");
		return Buffer_Full_Error;                                    
    }
	circ_ptr -> count ++;							    // incrementing the number of elements

	if(circ_ptr->head == (circ_ptr -> buff + (circ_ptr -> size -1))){
	    circ_ptr -> head = circ_ptr -> buff;            // so that we wrap around after the last element
	}
	else
	    circ_ptr -> head++;
	
	*(circ_ptr -> head) = item;              // assigning the item to the incremented head position
	return Buffer_Ok;
}


//This function removes the oldest element from the buffer
uint8_t remove_item(CircBuf_t *circ_ptr){

	if(is_Buffer_empty(circ_ptr) == 0){							// if buffer is empty, do not add more elements. 
		//printf("\nCannot read any more elements! Buffer is empty.\n");
		return 4;												// return 4 which is code for Buffer empty error
    }	
	
	if(circ_ptr -> tail == (circ_ptr -> buff + (circ_ptr -> size -1))){  
	    circ_ptr -> tail = circ_ptr -> buff;    // so that we can wrap around after the last element
	}	
	
	else
	    circ_ptr -> tail++;	
	    	  	
	circ_ptr -> count--;							// number of active elements is decreased
	return *(circ_ptr -> tail);                     // returning the value read
}


// This function initializes the buffer, allocates memory and returns a pointer to the allocated heap
uint8_t  *initialize_Buffer(CircBuf_t *circ_ptr)
{   
    if (circ_ptr != NULL) {
        // initializations
        circ_ptr -> count  = 0;
        circ_ptr -> buff = NULL; 
        circ_ptr -> size = MAX_SIZE;
        
        // allocating memory to the buffer
        circ_ptr -> buff = (uint8_t *)malloc(sizeof(uint8_t) * (circ_ptr -> size));
        
        //checking for successful memory allocation
        if(circ_ptr -> buff == NULL){
            printf("\nError : Expected memory allocation is bigger than expected.\n");
            return NULL;
        }
        else{
            circ_ptr -> head = circ_ptr -> buff;
            circ_ptr -> tail = circ_ptr -> buff;   
             return (circ_ptr -> buff); 
        }  
   }
}


// This function frees up the circular buffer from dynamic memory
void destroy(CircBuf_t *circ_ptr)
{
    if (circ_ptr != NULL) {
        free(circ_ptr -> buff);
        circ_ptr -> buff = NULL;
    }
}


// Writing unit tests for all modules
void unit_testing(CircBuf_t *buf_ptr){
    uint8_t i = 0;
    uint8_t *buff_address;
    uint8_t read = 0;
    
    
    printf("STARTING THE CIRCBUFF UNIT TEST SUITE...\n");
    
    // Testing if initialization and allocation was successful
    buff_address = initialize_Buffer(buf_ptr);
    no_of_tests++;
    if (buff_address == NULL){
        printf("CB UNIT TEST: 1/10 - <INITIALIZE AND ALLOCATE> ...FAIL\n");
        fail++;
    }
    else{
        printf("CB UNIT TEST: 1/10 - <INITIALIZE AND ALLOCATE> ...PASS\n");
        pass++;
    }
    
    //checking an empty buffer for the empty condition
    no_of_tests++;
    if(is_Buffer_empty(buf_ptr) == Buffer_Empty){
        printf("CB UNIT TEST: 2/10 - <CHECKING AN EMPTY BUFFER> ...PASS\n");
        pass++;
    }
    else{
        printf("CB UNIT TEST: 2/10 - <CHECKING AN EMPTY BUFFER> ...FAIL\n");
        fail++;
    }
    
    //test to read value from an empty buffer
    
    no_of_tests++;
    read = remove_item(buf_ptr);
    if(read == 4){
         printf("CB UNIT TEST: 3/10 - <READING ITEM FROM EMPTY BUFFER> ...PASS\n"); 
         pass++;
    }
    else{
        printf("CB UNIT TEST: 3/10 - <READING ITEM FROM EMPTY BUFFER> ...FAIL\n");
        fail++;
    }   
        
    //for loop to add elements into the buffer till the max count
    // checking if the add item module works correctly
    no_of_tests++;
	for(i=0 ; i< MAX_SIZE ; i++){
		add_item(buf_ptr, i);
	}

	
	if(buf_ptr->count == MAX_SIZE){
	    printf("CB UNIT TEST: 4/10 - <VERIFYING ADD ITEM FUNCTIONALITY> ...PASS\n");
	    pass++;
	}
	else{
	    printf("CB UNIT TEST: 4/10 - <VERIFYING ADD ITEM FUNCTIONALITY> ...FAIL\n");
	    fail++;
	}	
	
	//checking if the buffer full condition is detected
	no_of_tests++;
	if(is_Buffer_full(buf_ptr) == Buffer_Full){
        printf("CB UNIT TEST: 5/10 - <CHECKING A FULL BUFFER> ...PASS\n");
        pass++;
    }
    else{
        printf("CB UNIT TEST: 5/10 - <CHECKING A FULL BUFFER> ...FAIL\n");
        fail++;
    }
    
    // checking if an extra item can be added to a full buffer
    no_of_tests++;
    add_item(buf_ptr, 100);
    if(buf_ptr -> count == MAX_SIZE){
         printf("CB UNIT TEST: 6/10 - <ADDING ITEM TO FULL BUFFER> ...PASS\n"); 
         pass++;
    }
    else{
        printf("CB UNIT TEST: 6/10 - <ADDING ITEM TO FULL BUFFER> ...FAIL\n");
        fail++;
    }   
    
    //reading items from a non-empty buffer
    no_of_tests++;
    for(i=0;i<MAX_SIZE;i++){
        remove_item(buf_ptr);
    }
    if(buf_ptr -> count == 0){
        printf("CB UNIT TEST: 7/10 - <REMOVING ITEMS FROM A FULL BUFFER> ...PASS\n"); 
        pass++;
    }    
    else{
        printf("CB UNIT TEST: 7/10 - <REMOVING ITEMS FROM A FULL BUFFER> ...FAIL\n");
        fail++;
    }  
    
    //adding 1 item and then removing it to see if there is a proper wraparound
    no_of_tests++;
    add_item(buf_ptr, 100);
    remove_item(buf_ptr);
    if(buf_ptr -> count == 0){
        printf("CB UNIT TEST: 8/10 - <CHECKING THE WRAP-AROUND CASE> ...PASS\n"); 
        pass++;
    }  
    else{
        printf("CB UNIT TEST: 8/10 - <CHECKING THE WRAP-AROUND CASE> ...FAIL\n");
        fail++;
    }  
      
    // adding an element and removing two to check for an error
    no_of_tests++;
    add_item(buf_ptr,100);
    remove_item(buf_ptr);
    remove_item(buf_ptr);
    if(is_Buffer_empty(buf_ptr) == 0){
        printf("CB UNIT TEST: 9/10 - <READING MORE ELEMENTS THAN PRESENT> ...PASS\n"); 
        pass++;
    }  
    else{
        printf("CB UNIT TEST: 9/10 - <READING MORE ELEMENTS THAN PRESENT> ...FAIL\n"); 
        fail++;
    }       
    
    // test to check if the buff pointer has been freed after using the free function
    no_of_tests++;
    destroy(buf_ptr);
    if(buf_ptr -> buff == NULL){
        printf("CB UNIT TEST: 10/10 - <DYNAMIC MEMORY SUCCESSFULLY CLEARED> ...PASS\n"); 
        pass++;
    }  
    else{
        printf("CB UNIT TEST: 10/10 - <DYNAMIC MEMORY SUCCESSFULLY CLEARED> ...FAIL\n"); 
        fail++;
    }    
    
    
    // printing the result of the tests
    if(pass == no_of_tests){
        printf("CIRCBUFF UNIT TEST SUITE: PASS (%d/%d PASS)\n", pass, no_of_tests);
    }
    else{
        printf("CIRCBUFF UNIT TEST SUITE: FAIL (%d/%d PASS)\n", pass, no_of_tests);
    }    
    

}




 /* Defining the display_mallinfo() function to display information about the heap allocation. This has been looked up from http://man7.org/linux/man-pages/man3/mallinfo.3.html and hence the copyright information below */
 
 /* Copyright (c) 2012 by Michael Kerrisk <mtk.manpages@gmail.com>

    License for mallinfo.3:

    Permission is granted to make and distribute verbatim copies of this
    manual provided the copyright notice and this permission notice are
    preserved on all copies.

    Permission is granted to copy and distribute modified versions of this
    manual under the conditions for verbatim copying, provided that the
    entire resulting derived work is distributed under the terms of a
    permission notice identical to this one.

    Since the Linux kernel and libraries are constantly changing, this
    manual page may be incorrect or out-of-date.  The author(s) assume no
    responsibility for errors or omissions, or for damages resulting from
    the use of the information contained herein.  The author(s) may not
    have taken the same level of care in the production of this manual,
    which is licensed free of charge, as they might when working
    professionally.

    Formatted or processed versions of this manual, if unaccompanied by
    the source, must acknowledge the copyright and authors of this work.

    void display_mallinfo(void)
    {
           struct mallinfo mi;
           mi = mallinfo();

           printf("Total non-mmapped bytes (arena):       %d\n", mi.arena);
           printf("# of free chunks (ordblks):            %d\n", mi.ordblks);
           printf("# of free fastbin blocks (smblks):     %d\n", mi.smblks);
           printf("# of mapped regions (hblks):           %d\n", mi.hblks);
           printf("Bytes in mapped regions (hblkhd):      %d\n", mi.hblkhd);
           printf("Max. total allocated space (usmblks):  %d\n", mi.usmblks);
           printf("Free bytes held in fastbins (fsmblks): %d\n", mi.fsmblks);
           printf("Total allocated space (uordblks):      %d\n", mi.uordblks);
           printf("Total free space (fordblks):           %d\n", mi.fordblks);
           printf("Topmost releasable block (keepcost):   %d\n", mi.keepcost);
    }



// calling the unit tests function in the main
int main(){

	CircBuf_t buf;			    // creating a structure instance
	CircBuf_t *buf_ptr = &buf;  // creating a pointer to structure instance
	
	#ifdef UNIT_TESTS
	unit_testing(buf_ptr);      // testing all modules (unit testing)
	#endif
	
	//using mallinfo to find information on the current heap allocation
	printf("\n\nDisplaying information about current memory allocation:\n");
//	display_mallinfo();
  
  	return 0;
}

*/