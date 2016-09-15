#include"reverse.h"
#include<limits.h>

char reverse_string(char *str, int length)
{
    if(length<0) // check for negative length
    return 1;
    else if(length>INT_MAX) //check for integer overflow
    return 2;
    else if(length ==0) //check for 0 length
    return 3;
    else
    {
        if(*(str+length+1)!='\0') //check for NULL ending
        return 4;
        else
        {
            int i;
            char temp=0;
            for(i=0;i<length/2;i++) //loop to reverse string
            {
                temp=*(str+i);
                *(str+i) = *(str+length-i-1);
                *(str+length-i-1)=temp;
            }
            return 0;
        }
    }
}
