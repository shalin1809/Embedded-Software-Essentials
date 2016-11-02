/*
 * nRF24L01.c
 *
 *  Created on: 30-Oct-2016
 *      Author: Snehal Sanghvi
 */

#include "MKL25Z4.h"
#include "spi.h"
#include "nRF24L01.h"
#include <stdint.h>

#define RF_CHANNEL 2	// channel 2 is also the default channel
#define PAYLOAD_SIZE 1	// payload size

uint8_t payload[PAYLOAD_SIZE];  // payload data

uint8_t TX_address[5] = {0XE7, 0XE7, 0XE7, 0XE7, 0XE7};

// Function to write a byte to the register
void NORDIC_Write(uint8_t register1, uint8_t value){
	int i;
	SPI_tx_byte(NORDIC_W_REGISTER|register1); //sending the write command
	for(i=0;i<500;i++){}   //setting an intermittent delay
	SPI_tx_byte(value);	   //sending the value
}


// Configuring parameters like 1 CRC byte, enable CRC, power up and set to transmit mode
void NORDIC_Config(void){
	NORDIC_Write(NORDIC_CONFIG, NORDIC_CONFIG_EN_CRC(1) | NORDIC_CONFIG_CRCO_1 | NORDIC_CONFIG_POWER_UP | NORDIC_CONFIG_PRIM_TX);
}


// setting the clock enable (CE) pin high to transmit data
void CE_High(void){
	//enabling port C
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	//Select Alternate function 1 (or gpio pin) for pin 3
	PORTC_PCR3 |= PORT_PCR_MUX(1);
	//setting direction as output
	PTC->PDDR |= 0x08;
	//making the CE pin high (active high)
	PTC->PSOR = 0x08;
}


// setting the clock enable (CE) pin low
void CE_Low(void){
	//enabling port C
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	//Select Alternate function 1 (or gpio pin) for pin 3
	PORTC_PCR3 |= PORT_PCR_MUX(1);
	//setting direction as output
	PTC->PDDR |= 0x08;
	//making the CE pin low (active high)
	PTC->PCOR = 0x08;
}


// Function to write multiple bytes to the bus - needed if transmit address is to be sent
void NORDIC_Write_Multiple(uint8_t register1, uint8_t *loc, uint8_t size) {
  uint8_t i;
  PTC->PCOR |= 0x01;    //clearing the ss bit to drive it low
  SPI_tx_byte(NORDIC_W_REGISTER|register1);

  for(i=0; i<size; i++) {
    SPI_tx_byte(loc[i]);
  }
  PTC->PSOR |= 0x01;	//setting the ss bit high
}


// Reading the value of the STATUS register by sending NOP command
uint8_t NORDIC_Get_Status(){
	uint8_t read_value;
	read_value = SPI_tx_byte(NORDIC_NOP);
	return read_value;
}


// function to set the RF parameters required for transmission.
void NORDIC_RF_Setup(void){
	//Setting a data rate of 1 Mbps, transmit power of 0dBm and the low power gain
	NORDIC_Write(NORDIC_RF_SETUP_ADDR, NORDIC_RF_DR_ONE | NORDIC_RF_PWR_ZERO | NORDIC_LNA_HCURR(1));

	//setting the RF channel no. 2
	NORDIC_Write(NORDIC_RF_CH_ADDR, RF_CHANNEL);

	// number of payload bytes we want to send and receive
	NORDIC_Write(NORDIC_RX_ADDR_P0_ADDR, PAYLOAD_SIZE);
}


// sending payload to transmit buffer to send it
void NORDIC_TX_Payload(uint8_t *payload, uint8_t Payload_size) {
	uint16_t count = 0;
	//flushes the old data
	NORDIC_TX_Flush();

	// writing the payload data
	NORDIC_Write_Multiple(NORDIC_W_TX_PAYLOAD, payload, Payload_size);

	//setting CE pin to start transmission
	CE_High();

	//setting some delay for which signal is high
	while(count!=8000){
		count++;
	}

	//stop transmission
	CE_Low();
}


// Function to flush TX
void NORDIC_TX_Flush(){
	SPI_tx_byte(NORDIC_FLUSH_TX);
}


// Function to flush RX
void NORDIC_RX_Flush(){
	SPI_tx_byte(NORDIC_FLUSH_RX);
}


/*void NORDIC_Set_TX_Address(){
	uint8_t i;

	//setting the tx address width of 5 bytes in the Setup_aw (setup address width register)
	NORDIC_Write(NORDIC_SETUP_AW, NORDIC_AW_FIVE);

	// Setting the device address
	const uint8_t TX_ADDR[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};

	//setting 5 bytes for the receive pipe 0
	// -> check NORDIC_Write(NORDIC_W_REGISTER|NORDIC_RX_PW_P0_ADDR, 0x05);

	NORDIC_Write_Multiple(NORDIC_TX_ADDR_ADDR, (uint8_t*)TX_ADDR, sizeof(TX_ADDR));

	// enable auto-ack for pipe 0
	RF_WriteRegister(NORDIC_EN_AA_ADDR, 0x00 | NORDIC_ENAA_P0(1));

	// enable data pipe 0
	RF_WriteRegister(NORDIC_EN_RXADDR_ADDR, 0x00 | NORDIC_ERX_P0(1));
}*/
