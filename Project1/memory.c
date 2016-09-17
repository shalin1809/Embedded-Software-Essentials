#include"memory.h"

inline void move(uint8_t *src, uint8_t *dst, uint32_t length){            //Move string on successful overlapping validation. Used in memmove
    while(length--)
        *dst++ = *src;
}



/*
my_memmove will copy the values from src to dst for the length of bytes provided 
*/

int8_t my_memmove(uint8_t *src, uint8_t *dst, uint32_t length){   
      
    if(  ( (*(dst+length))  <*src) && (*dst < *src)){       //destination has lower memory than source and does not overlap
        move(src,dst,length);
    }
    else if (   ( (*(src+length)) < *dst)   && ( *src < *dst) ){        //source has lower memory than destination and does not overlap
       move(src,dst,length);
    }
    else return 1;                             //Error code for fail
}


/* 
my_memzero will turn all elements of the memory space to '0'
*/

int8_t my_memzero(uint8_t *src, uint32_t length){
        while(length--)
            *src++ = 0;
}

/*
my_reverse reverses all the characters of the string
*/
int8_t my_reverse(uint8_t *src, uint32_t length){
    if(length<0) // check for negative length
    return 1;
    else if(length>INT_MAX) //check for integer overflow
    return 2;
    else if(length ==0) //check for 0 length
    return 3;
    else{
        if(((*(src+length)))!='\0') //check for NULL ending
        return 4;
        else{
            int i;
            char temp=0;
            for(i=0;i<length/2;i++) //loop to reverse string
            {
                temp=*(src+i);
                *(src+i) = *(src+length-i-1);
                *(src+length-i-1)=temp;
            }
            return 0;
        }
    }
}      


