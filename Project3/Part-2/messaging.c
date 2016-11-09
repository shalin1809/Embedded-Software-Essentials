/******************************************************
*   File: messaging.c
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
*   Date Edited: 11 Nov 2016
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

#include "messaging.h"


extern CircBuf_t *rx_buffer;
extern CircBuf_t *tx_buffer;

void decode_message (void){   
    int total_data = 0;    
    //while(!(UART0->S1 & 0x20)) {}       //wait for receive buffer full
    __wfi();
    message.Command =  (int)remove_item(rx_buffer);
    UART0_WriteChar('c');
    //while(!(UART0->S1 & 0x20)) {}       //wait for receive buffer full
    __wfi();
    message.length =   (uint8_t)remove_item(rx_buffer);
    UART0_WriteChar('l');
    for(; total_data<message.length; total_data++){
        //while(!(UART0->S1 & 0x20)) {}       //wait for receive buffer full
        __wfi();
        message.data[total_data] = (uint8_t)remove_item(rx_buffer);
    }
    message.data[total_data] = '\0';
    UART0_WriteChar('d');
    //while(!(UART0->S1 & 0x20)) {}       //wait for receive buffer full
    __wfi();
    message.checksum = ((uint16_t)remove_item(rx_buffer)<<8);
    //while(!(UART0->S1 & 0x20)) {}       //wait for receive buffer full
    __wfi();
    message.checksum |= (uint16_t)remove_item(rx_buffer);
        
    if(checksum_validate()== CHKSUM_FAIL)
    {
        ack_nack(NACK);
        LOG_0("Message corrupted",17);
    }
    else{
        ack_nack(ACK);
        LOG_0("Transmit successful",19);
        if(message.Command == LED_TOGGLE){
            if(*message.data == OFF){
                LED_Control('0');                     //For LED off
            }
            else if(*message.data == BLUE){
                LED_Control('1');                     //For LED BLUE
            }
            else if(*message.data == GREEN){
                LED_Control('2');                     //For LED GREEN
            }
            else if(*message.data == CYAN){
                LED_Control('3');                     //For LED CYAN
            }
            else if(*message.data == RED){
                LED_Control('4');                     //For LED RED
            }
            else if(*message.data == PINK){
                LED_Control('5');                     //For LED PINK
            }
            else if(*message.data == ORANGE){
                LED_Control('6');                     //For LED ORANGE
            }
            else if(*message.data == WHITE){
                LED_Control('7');                     //For LED WHITE
            }
        }
        else if(message.Command == BRIGHTNESS){
            if(*message.data == TEN_PERCENT){
                LED_SET_BRIGHTNESS((int)TEN_PERCENT);    //Set brightness to TEN_PERCENT    
            }
            else if(*message.data == TWENTY_PERCENT){
                LED_SET_BRIGHTNESS(TWENTY_PERCENT);    //Set brightness to TWENTY_PERCENT    
            }
            else if(*message.data == THIRTY_PERCENT){
                LED_SET_BRIGHTNESS(THIRTY_PERCENT);    //Set brightness to THIRTY_PERCENT    
            }
            else if(*message.data == FORTY_PERCENT){
                LED_SET_BRIGHTNESS(FORTY_PERCENT);    //Set brightness to FORTY_PERCENT    
            }
            else if(*message.data == FIFTY_PERCENT){
                LED_SET_BRIGHTNESS(FIFTY_PERCENT);    //Set brightness to FIFTY_PERCENT    
            }
            else if(*message.data == SIXTY_PERCENT){
                LED_SET_BRIGHTNESS(SIXTY_PERCENT);    //Set brightness to SIXTY_PERCENT    
            }
            else if(*message.data == SEVENTY_PERCENT){
                LED_SET_BRIGHTNESS(SEVENTY_PERCENT);    //Set brightness to SEVENTY_PERCENT    
            }
            else if(*message.data == EIGHTY_PERCENT){
                LED_SET_BRIGHTNESS(EIGHTY_PERCENT);    //Set brightness to EIGHTY_PERCENT    
            }
            else if(*message.data == NINTY_PERCENT){
                LED_SET_BRIGHTNESS(NINTY_PERCENT);    //Set brightness to NINTY_PERCENT    
            }
            else if(*message.data == HUNDRED_PERCENT){
                LED_SET_BRIGHTNESS(HUNDRED_PERCENT);    //Set brightness to HUNDRED_PERCENT    
            }
        }
    }        
}

void ack_nack (CMDS reply){
    UART0_WriteChar(reply);
}


ERR checksum_validate (void){
    int i=0;
    uint16_t check_sum;

	check_sum = message.Command + (uint16_t)message.length;
	for(;i<((message.length));i++)
	{
		check_sum += (uint16_t)message.data[i];
	}
	if(check_sum == message.checksum)
		return CHKSUM_PASS;
	else
		return CHKSUM_FAIL;
}


