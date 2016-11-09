/********************************************
*   File: spi.c
*
*   Copyrights 2016 Snehal Sanghvi and Shalin Shah
*   All Rights Reserved
*
*   The information contained herein is property of the Authors.
*   The copying and distribution of the files is prohibited except
*   by express written agreement with the Authors.
*
*
*   Author: Snehal Sanghvi and Shalin Shah
*   Date Edited: 9 Nov 2016
*
*   Description: Source file for SPI drivers
*   		
*		SPI_init
*		SPI_tx_byte
*		SPI_status
*		SPI_rx_byte
*
********************************************************/
#include "MKL25Z4.h"
#include "spi.h"
#include <stdint.h>


//initializing the spi module
void SPI_init(void){

	//Enabling the clock gate for SPI0
	SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;

	//selecting port C for SPI0 and configuring its GPIO pins
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	PORTC_PCR4 |= PORT_PCR_MUX(1); 			//Select Alternate function 1 (or gpio pin) for SPI0_PCS0 (or SPI SS)
	PORTC_PCR5 |= PORT_PCR_MUX(2);			//Select Alternate function 2 for SPI0_SCK
	PORTC_PCR6 |= PORT_PCR_MUX(2); 			//Select Alternate function 2 for SPI0_MOSI
	PORTC_PCR7 |= PORT_PCR_MUX(2); 			//Select Alternate function 2 for SPI0_MISO

	//configuring the ss pin
	PTC->PDDR |= 0x10;                      //selecting the ss pin as output (---- 1---)
	PTC->PSOR = 0x10;						//making the ss pin high (or idle, since its active low)

	//Selecting master mode for the SPI on MCU and setting CPHA to 1
	SPI0->C1 |= SPI_C1_MSTR_MASK | SPI_C1_CPHA_MASK;

	//enabling dma transfers
	//SPI_C2 = SPI_C2_TXDMAE_MASK | SPI_C2_RXDMAE_MASK;
	//SPI0->C2 = SPI_C2_SPC0_MASK | SPI_C2_BIDIROE_MASK;

	//setting a baud rate divisor of 4
	SPI0->BR = SPI_BR_SPR(1);

	//enabling the SPI module
	SPI0->C1 |= SPI_C1_SPE_MASK;
}


//function to return status of SPI
uint8_t SPI_status(void) {
	return SPI0->S;
}


//transmitting a byte
uint8_t SPI_tx_byte(unsigned char byte){
	uint8_t temp;
	PTC->PCOR |= 0x10;   //clearing the ss bit to drive it low

	//waiting for transmit buffer to become empty
	while(!(SPI_status() & 0x20)){};
	SPI0->D = byte;

	//waiting for data to become available in the receive buffer
	while(!(SPI_status() & 0x80)){};
	temp = SPI0->D;   //clears SPRF

	PTC->PSOR |= 0x10;	 //setting the ss bit high
	return temp;
}


//receiving a byte
uint8_t SPI_rx_byte(){
	uint8_t read_value;
	PTC->PCOR |= 0x10;   //clearing the ss bit to drive it low

	//waiting for transmit buffer to become empty
	while(!(SPI_status() & 0x20)){};
	SPI0_D = 0xFF;

	//waiting for data to become available in the receive buffer
	while(!(SPI_status() & 0x80)){};
	read_value = SPI0->D;

	PTC->PSOR |= 0x10;	 //setting the ss bit high
	return read_value;

}
