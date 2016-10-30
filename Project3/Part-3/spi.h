/*
 * spi.h
 *
 *  Created on: 29-Oct-2016
 *      Author: Snehal Sanghvi
 */

#ifndef INCLUDES_SPI_H_
#define INCLUDES_SPI_H_


//setup routine to initialize the SPI module
void SPI_init(void);

//routine to transmit byte
void SPI_tx_byte(unsigned char byte);

//routine to return status of SPI
uint8_t SPI_status(void);

#endif /* INCLUDES_SPI_H_ */
