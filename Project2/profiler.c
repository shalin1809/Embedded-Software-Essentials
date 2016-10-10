#include "MKL25Z4.h"

uint32_t counts = 0;   //number of timer overflows that have happened

void profiling(){
	SIM_SCGC5 |= 0x00000001;
	SIM_SCGC6 |= 0x04000000;
	SIM_SOPT2 |= 0x01000000;

	TPM2_SC = 0x00000000;
	TPM2_MOD = 210;				// To obtain a 10usec period
	TPM2_C0SC = 0x00000024;
	TPM2_C0V = 105;
	TPM2_SC = 0x00000048;		// enabling overflow interrupts
	NVIC_EnableIRQ(TPM2_IRQn);
	__enable_irq();
}


int8_t my_memmove(uint8_t *src, uint8_t *dst, uint32_t length){

    if(  ( (dst+length)  <src) && (dst < src)){       //destination has lower memory than source and does not overlap
        while(length--)
            *dst++ = *src++;
        return 0;
    }
    else if (   ( (src+length) < dst)   && ( src < dst) ){        //source has lower memory than destination and does not overlap
       while(length--)
            *dst++ = *src++;
       return 0;
    }
    else if( (src<dst) && ( (src+length) > dst)  ){               //source has lower memory than destination and overlaps
        while(length--)
            *(dst+length-1) = *(src+length-1);
        //printf("\n The memory is overlapping, it will overlap the source string");
        return 0;
    }
    else if(  ((dst+length)  >src) && (dst < src)){                 //destination has lower memory than source and overlaps
        while(length--)
            *dst++ = *src++;
        //printf("\n The memory is overlapping, it will overlap the source string");
        return 0;
    }
    else return 1;                             //Error code for fail
}


void TPM2_IRQHandler(void){
	//uint8_t bit = TPM2_SC >> 6;
	//if(TPM2_SC & (bit==1)){
		counts ++;				//incrementing the timer overflow variable
	//}
}


int main(){

	int a = 0;
	float b = 0.0;
	char src[] = "Hello";
	char dst[6];
	profiling();			//calling the profiler function
	counts = 0;				//initializing counts to 0
	my_memmove(src, dst, 5);
	__disable_irq();		//disabling interrupts
	a = counts*210 + TPM2->CNT;		//total cycles is the (mod_value*number_of_timer_overflows + current_count_in_tpm)
	b = a/20970000.00;	//b represents the time spent in the function = total cycles/clock_frequency

	return 0;
}
