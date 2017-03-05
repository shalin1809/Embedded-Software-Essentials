/******************************************************
*   File: messaging.h
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
*   Date Edited: 7 Destroy 2016
*
*   Description: Source file for implementing Circular buffer functions
*               -decode_message
*               -ack_nack
*               -checksum_validate
*
********************************************************/
#ifndef MESSAGING_H_
#define MESSAGING_H_

#include "stdint.h"
#include "LED.h"
#include "uart.h"
#include "Circular_buffer.h"
#include "log.h"
#include "myrtc.h"


#define MAX_DATA_LENGTH 20


/* Enumerating Commands which are known to the messaging interface*/
typedef enum CMDS_t{
    LED_TOGGLE = 1,
    BRIGHTNESS = 2,
    ACK = 3,
    NACK = 4,
    ECHO = 5,
    SET_TIME = 6,
    SET_ALARM_10SECONDS = 7,
    SET_ALARM = 8
}CMDS;

/* Structure of the message which will be transferred*/
typedef struct Message_t{
    CMDS Command;
    uint8_t length;
    uint8_t data[MAX_DATA_LENGTH];
    uint16_t checksum;
}Message;

Message message;


/*Enumerating the brightness values for the LED*/
typedef enum Brightness {		
	TEN_PERCENT = 1,
	TWENTY_PERCENT = 2,
	THIRTY_PERCENT = 3,
	FORTY_PERCENT = 4,
	FIFTY_PERCENT = 5,
	SIXTY_PERCENT = 6,
	SEVENTY_PERCENT = 7,
	EIGHTY_PERCENT = 8,
	NINTY_PERCENT = 9,
	HUNDRED_PERCENT = 10
}Brightness_t;

/* Checksum errors*/
typedef enum ERR_t {
	CHKSUM_FAIL = 1,
	CHKSUM_PASS = 2
}ERR;

/************************************
decode_message

Description: It is used to decode the received message

Parameters: None

************************************/
void decode_message (void);

/************************************
ack_nack

Description: Send ACK or NACK after validating the checksum

Parameters: reply to be sent

************************************/
void ack_nack(CMDS reply);


/************************************
checksum_validate

Description: Verifies the checksum received and returns error code 

Parameters: None

************************************/
ERR checksum_validate (void);

#endif
