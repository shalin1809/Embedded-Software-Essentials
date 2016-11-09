/********************************************
*   File: nordic.h
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
*   Description: Header file for testing the NORDIC NRF24L01+ chip
*   			
*   		NORDIC_Write
*		NORDIC_Config
*		CE_High
*		CE_Low
*		NORDIC_Write_Multiple
*		NORDIC_Get_Status
*		NORDIC_RF_Setup
*		NORDIC_TX_Payload
*		NORDIC_TX_Flush
*		NORDIC_RX_Flush
*
********************************************************/
#ifndef INCLUDES_NRF24L01_H_
#define INCLUDES_NRF24L01_H_
#include <stdint.h>

#define NORDIC_BASE                                				(0x00)
#define NORDIC									(Nordic_struct *)NORDIC_BASE
#define NORDIC_BASE_PTR								(NORDIC)

#define __IO volatile


// SPI Command Names
#define NORDIC_R_REGISTER     (0x00)		//Read command and status registers. AAAAA = 5 bit register map address. 1-5 data bytes, LSByte first
#define NORDIC_W_REGISTER     (0x20)		//Write command and status registers. AAAAA = 5 bit register map address. 1-5 data bytes,  LSByte first
#define NORDIC_R_RX_PAYLOAD   (0x61)		//Read RX payload. 1-32 data bytes, LSByte first
#define NORDIC_W_TX_PAYLOAD   (0xA0)		//Write TX payload. 1-32 data bytes, LSByte first
#define NORDIC_FLUSH_TX       (0xE1)		//Flush TX mode. 0 data bytes
#define NORDIC_FLUSH_RX       (0xE2)		//Flush RX mode. 0 data bytes
#define NORDIC_REUSE_TX_PL    (0xE3)		//Reuse last transmitted payload. 0 data bytes
#define NORDIC_NOP            (0xFF)		//No operation. 0 data bytes


// structure containing all the registers
typedef struct {
__IO  uint8_t NORDIC_CONFIG_ADDR;
__IO  uint8_t NORDIC_EN_AA_ADDR;
__IO  uint8_t NORDIC_EN_RXADDR_ADDR;
__IO  uint8_t NORDIC_SETUP_AW_ADDR;
__IO  uint8_t NORDIC_SETUP_RETR_ADDR;
__IO  uint8_t NORDIC_RF_CH_ADDR;
__IO  uint8_t NORDIC_RF_SETUP_ADDR;
__IO  uint8_t NORDIC_STATUS_ADDR;
__I   uint8_t NORDIC_OBSERVE_TX_ADDR;
__I   uint8_t NORDIC_CD_ADDR;
__IO  uint8_t NORDIC_RX_ADDR_P0_ADDR;
__IO  uint8_t NORDIC_RX_ADDR_P1_ADDR;
__IO  uint8_t NORDIC_RX_ADDR_P2_ADDR;
__IO  uint8_t NORDIC_RX_ADDR_P3_ADDR;
__IO  uint8_t NORDIC_RX_ADDR_P4_ADDR;
__IO  uint8_t NORDIC_RX_ADDR_P5_ADDR;
__IO  uint8_t NORDIC_TX_ADDR_ADDR;
__IO  uint8_t NORDIC_RX_PW_P0_ADDR;
__IO  uint8_t NORDIC_RX_PW_P1_ADDR;
__IO  uint8_t NORDIC_RX_PW_P2_ADDR;
__IO  uint8_t NORDIC_RX_PW_P3_ADDR;
__IO  uint8_t NORDIC_RX_PW_P4_ADDR;
__IO  uint8_t NORDIC_RX_PW_P5_ADDR;
__IO  uint8_t NORDIC_FIFO_STATUS_ADDR;
	  uint8_t RESERVED_0[5];
__IO  uint8_t NORDIC_DYNPD_ADDR;
__IO  uint8_t NORDIC_FEATURE_ADDR;
} Nordic_struct, *MemMapPtr;



// Memory Map - register address defines

#define NORDIC_CONFIG_REG(base)                    		 ((base)->NORDIC_CONFIG_ADDR)
#define NORDIC_EN_AA_REG(base)       				 ((base)->NORDIC_EN_AA_ADDR)
#define NORDIC_EN_RXADDR_REG(base)   				 ((base)->NORDIC_EN_RXADDR_ADDR)
#define NORDIC_SETUP_AW_REG(base)   				 ((base)->NORDIC_SETUP_AW_ADDR)
#define NORDIC_SETUP_RETR_REG(base)  				 ((base)->NORDIC_SETUP_RETR_ADDR)
#define NORDIC_RF_CH_REG(base)       				 ((base)->NORDIC_RF_CH_ADDR)
#define NORDIC_RF_SETUP_REG(base)    				 ((base)->NORDIC_RF_SETUP_ADDR)
#define NORDIC_STATUS_REG(base)    				 ((base)->NORDIC_STATUS_ADDR)
#define NORDIC_OBSERVE_TX_REG(base) 				 ((base)->NORDIC_OBSERVE_TX_ADDR)
#define NORDIC_CD_REG(base)    	   				 ((base)->NORDIC_CD_ADDR)
#define NORDIC_RX_ADDR_P0_REG(base) 				 ((base)->NORDIC_RX_ADDR_P0_ADDR)
#define NORDIC_RX_ADDR_P1_REG(base)  				 ((base)->NORDIC_RX_ADDR_P1_ADDR)
#define NORDIC_RX_ADDR_P2_REG(base)  				 ((base)->NORDIC_RX_ADDR_P2_ADDR)
#define NORDIC_RX_ADDR_P3_REG(base)  				 ((base)->NORDIC_RX_ADDR_P3_ADDR)
#define NORDIC_RX_ADDR_P4_REG(base)  				 ((base)->NORDIC_RX_ADDR_P4_ADDR)
#define NORDIC_RX_ADDR_P5_REG(base) 				 ((base)->NORDIC_RX_ADDR_P5_ADDR)
#define NORDIC_TX_ADDR_REG(base)    				 ((base)->NORDIC_TX_ADDR_ADDR)
#define NORDIC_RX_PW_P0_REG(base)   				 ((base)->NORDIC_RX_PW_P0_ADDR)
#define NORDIC_RX_PW_P1_REG(base)  				 ((base)->NORDIC_RX_PW_P1_ADDR)
#define NORDIC_RX_PW_P2_REG(base)  				 ((base)->NORDIC_RX_PW_P2_ADDR)
#define NORDIC_RX_PW_P3_REG(base)   				 ((base)->NORDIC_RX_PW_P3_ADDR)
#define NORDIC_RX_PW_P4_REG(base)   				 ((base)->NORDIC_RX_PW_P4_ADDR)
#define NORDIC_RX_PW_P5_REG(base)    				 ((base)->NORDIC_RX_PW_P5_ADDR)
#define NORDIC_FIFO_STATUS_REG(base) 				 ((base)->NORDIC_FIFO_STATUS_ADDR)
#define NORDIC_DYNPD_REG(base)	  				 ((base)->NORDIC_DYNPD_ADDR)
#define NORDIC_FEATURE_REG(base)				 ((base)->NORDIC_FEATURE_ADDR)


#define NORDIC_CONFIG                            	 NORDIC_CONFIG_REG(NORDIC_BASE_PTR)
#define NORDIC_EN_AA                            	 NORDIC_EN_AA_REG(NORDIC_BASE_PTR)
#define NORDIC_EN_RXADDR                             	 NORDIC_EN_RXADDR_REG(NORDIC_BASE_PTR)
#define NORDIC_SETUP_AW                          	 NORDIC_SETUP_AW_REG(NORDIC_BASE_PTR)
#define NORDIC_SETUP_RETR                          	 NORDIC_SETUP_RETR_REG(NORDIC_BASE_PTR)
#define NORDIC_RF_CH                           	 	 NORDIC_RF_CH_REG(NORDIC_BASE_PTR)
#define NORDIC_RF_SETUP                           	 NORDIC_RF_SETUP_REG(NORDIC_BASE_PTR)
#define NORDIC_STATUS                           	 NORDIC_STATUS_REG(NORDIC_BASE_PTR)
#define NORDIC_OBSERVE_TX                            	 NORDIC_OBSERVE_TX_REG(NORDIC_BASE_PTR)
#define NORDIC_CD                           	    	 NORDIC_CD_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_ADDR_P0                            	 NORDIC_RX_ADDR_P0_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_ADDR_P1                            	 NORDIC_RX_ADDR_P1_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_ADDR_P2                          	 NORDIC_RX_ADDR_P2_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_ADDR_P3                          	 NORDIC_RX_ADDR_P3_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_ADDR_P4                          	 NORDIC_RX_ADDR_P4_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_ADDR_P5                          	 NORDIC_RX_ADDR_P5_REG(NORDIC_BASE_PTR)
#define NORDIC_TX_ADDR					 NORDIC_TX_ADDR_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_PW_P0                           	 NORDIC_RX_PW_P0_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_PW_P1                           	 NORDIC_RX_PW_P1_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_PW_P2                           	 NORDIC_RX_PW_P2_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_PW_P3                           	 NORDIC_RX_PW_P3_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_PW_P4                           	 NORDIC_RX_PW_P4_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_PW_P5                          	 NORDIC_RX_PW_P5_REG(NORDIC_BASE_PTR)
#define NORDIC_FIFO_STATUS                           NORDIC_FIFO_STATUS_REG(NORDIC_BASE_PTR)
#define NORDIC_DYNPD                           	 	 NORDIC_DYNPD_REG(NORDIC_BASE_PTR)
#define NORDIC_FEATURE                         		 NORDIC_FEATURE_REG(NORDIC_BASE_PTR)


// CONFIG Register Bits
#define NORDIC_CONFIG_MASK_RX_DR(x)  (uint8_t)((uint8_t)(x)<<6)  	// Mask interrupt caused by RX_DR 1: Interrupt not reflected on the IRQ pin 0: Reflect RX_DR as active low interrupt on the IRQ pin
#define NORDIC_CONFIG_MASK_TX_DS(x)  (uint8_t)((uint8_t)(x)<<5)	 	// Mask interrupt caused by TX_DS 1: Interrupt not reflected on the IRQ pin 0: Reflect TX_DS as active low interrupt on the IRQ pin
#define NORDIC_CONFIG_MASK_MAX_RT(x) (uint8_t)((uint8_t)(x)<<4)  	// Mask interrupt caused by MAX_RT 1: Interrupt not reflected on the IRQ pin. 0: Reflect MAX_RT as active low interrupt on the IRQ pin
#define NORDIC_CONFIG_EN_CRC(x)      (uint8_t)((uint8_t)(x)<<3)		// Enable CRC. Forced high if one of the bits in EN_AA is high
#define NORDIC_CONFIG_CRCO_1      	 (0x00)  						// CRC encoding scheme for 1 byte
#define NORDIC_CONFIG_CRCO_2 	  	 (0x04)							// CRC encoding scheme for 2 bytes
#define NORDIC_CONFIG_POWER_UP    	 (0x02)  						// 1: Power up
#define NORDIC_CONFIG_POWER_DOWN  	 (0x00)  						// 0: Power down
#define NORDIC_CONFIG_PRIM_RX     	 (0x01)  						// 1: PRX
#define NORDIC_CONFIG_PRIM_TX     	 (0x00)  						// 0: PTX


// EN_AA Register Bits
#define NORDIC_ENAA_ALL        (0x3F)							//Enable auto-acknowledgment for all pipes
#define NORDIC_ENAA_P5(x)      (uint8_t)((uint8_t)(x)<<5)		//Enable auto-acknowledgment for pipe 5
#define NORDIC_ENAA_P4(x)      (uint8_t)((uint8_t)(x)<<4)		//Enable auto-acknowledgment for pipe 4
#define NORDIC_ENAA_P3(x)      (uint8_t)((uint8_t)(x)<<3)		//Enable auto-acknowledgment for pipe 3
#define NORDIC_ENAA_P2(x)      (uint8_t)((uint8_t)(x)<<2)		//Enable auto-acknowledgment for pipe 2
#define NORDIC_ENAA_P1(x)      (uint8_t)((uint8_t)(x)<<1)		//Enable auto-acknowledgment for pipe 1
#define NORDIC_ENAA_P0(x)      (uint8_t)((uint8_t)(x)<<0)		//Enable auto-acknowledgment for pipe 0
#define NORDIC_ENAA_NONE       (0x00)							//Enable auto-acknowledgment none of the pipes


// EN_RXADDR Register Bits
#define NORDIC_ERX_P5(x)		(uint8_t)((uint8_t)(x)<<5)		//Enable data pipe 5
#define NORDIC_ERX_P4(x)		(uint8_t)((uint8_t)(x)<<4)		//Enable data pipe 4
#define NORDIC_ERX_P3(x)		(uint8_t)((uint8_t)(x)<<3)		//Enable data pipe 3
#define NORDIC_ERX_P2(x)		(uint8_t)((uint8_t)(x)<<2)		//Enable data pipe 2
#define NORDIC_ERX_P1(x)		(uint8_t)((uint8_t)(x)<<1 )		//Enable data pipe 1
#define NORDIC_ERX_P0(x)		(uint8_t)((uint8_t)(x)<<0)		//Enable data pipe 0


// Setup of address widths SETUP_AW Register Bits
#define NORDIC_AW_ILLEGAL	(0x00)		//Illegal rx/tx address field width
#define NORDIC_AW_THREE		(0x01)		//rx/tx address field width of 3 bytes
#define NORDIC_AW_FOUR		(0x02)		//rx/tx address field width of 4 bytes
#define NORDIC_AW_FIVE		(0x03)		//rx/tx address field width of 5 bytes


// Setup of automatic retransmission
//setting the auto retransmit delays
#define NORDIC_ARD_250		(0x00)		//Wait for 250 us - auto retransmit delay
#define NORDIC_ARD_500		(0x10)		//Wait for 500 us
#define NORDIC_ARD_750		(0x20)		//Wait for 750 us
#define NORDIC_ARD_1000		(0x30)		//Wait for 1000 us
#define NORDIC_ARD_1250		(0x40)		//Wait for 1250 us
#define NORDIC_ARD_1500		(0x50)		//Wait for 1500 us
#define NORDIC_ARD_1750		(0x60)		//Wait for 1750 us
#define NORDIC_ARD_2000		(0x70)		//Wait for 2000 us
#define NORDIC_ARD_2250		(0x80)		//Wait for 2250 us
#define NORDIC_ARD_2500		(0x90)		//Wait for 2500 us
#define NORDIC_ARD_2750		(0xA0)		//Wait for 2750 us
#define NORDIC_ARD_3000		(0xB0)		//Wait for 3000 us
#define NORDIC_ARD_3250		(0xC0)		//Wait for 3250 us
#define NORDIC_ARD_3500		(0xD0)		//Wait for 3500 us
#define NORDIC_ARD_3750		(0xE0)		//Wait for 3750 us
#define NORDIC_ARD_4000		(0xF0)		//Wait for 4000 us

//setting the auto-retransmit counts
#define NORDIC_ARC_0		(0x00)		//disable auto retransmit
#define NORDIC_ARC_1		(0x01)		//upto 1 retransmit on fail of AA
#define NORDIC_ARC_2		(0x02)		//upto 2 retransmit on fail of AA
#define NORDIC_ARC_3		(0x03)		//upto 3 retransmit on fail of AA
#define NORDIC_ARC_4		(0x04)		//upto 4 retransmit on fail of AA
#define NORDIC_ARC_5		(0x05)		//upto 5 retransmit on fail of AA
#define NORDIC_ARC_6		(0x06)		//upto 6 retransmit on fail of AA
#define NORDIC_ARC_7		(0x07)		//upto 7 retransmit on fail of AA
#define NORDIC_ARC_8		(0x08)		//upto 8 retransmit on fail of AA
#define NORDIC_ARC_9		(0x09)		//upto 9 retransmit on fail of AA
#define NORDIC_ARC_10		(0x0A)		//upto 10 retransmit on fail of AA
#define NORDIC_ARC_11		(0x0B)		//upto 11 retransmit on fail of AA
#define NORDIC_ARC_12		(0x0C)		//upto 12 retransmit on fail of AA
#define NORDIC_ARC_13		(0x0D)		//upto 13 retransmit on fail of AA
#define NORDIC_ARC_14		(0x0E)		//upto 14 retransmit on fail of AA
#define NORDIC_ARC_15		(0x0F)		//upto 15 retransmit on fail of AA


// RF Setup Register Bits
#define NORDIC_PLL_LOCK(x)					(uint8_t)((uint8_t)(x)<<4) 	//Force PLL lock signal
#define NORDIC_RF_DR_ONE					(0x00)						//Air data rate of 1Mbps
#define NORDIC_RF_DR_TWO					(0x08)						//Air data rate of 2Mbps
#define NORDIC_RF_PWR_NEGATIVE_EIGHTEEN		(0x00)						//RF output power in TX mode of -18dBm
#define NORDIC_RF_PWR_NEGATIVE_TWELVE		(0x02)						//RF output power in TX mode of -12dBm
#define NORDIC_RF_PWR_NEGATIVE_SIX			(0x04)						//RF output power in TX mode of -6dBm
#define NORDIC_RF_PWR_ZERO					(0x06)						//RF output power in TX mode of 0dBm
#define NORDIC_LNA_HCURR(x)					(uint8_t)((uint8_t)(x)<<0)	//Setup LNA gain


// STATUS Register Bits
#define NORDIC_STATUS_RX_DR(x)    	 (uint8_t)((uint8_t)(x)<<6)  	// Data ready RX FIFO interrupt
#define NORDIC_STATUS_TX_DS(x)       (uint8_t)((uint8_t)(x)<<5)  	// Data sent TX FIFO interrupt
#define NORDIC_STATUS_MAX_RT(x)      (uint8_t)((uint8_t)(x)<<4)  	// max number of tx retransmissions
#define NORDIC_STATUS_RX_P_NO_0   	 (0x00)  						// pipe 0 for payload available for reading from RX_FIFO
#define NORDIC_STATUS_RX_P_NO_1   	 (0x02)							// pipe 1 for payload available for reading from RX_FIFO
#define NORDIC_STATUS_RX_P_NO_2   	 (0x04)  						// pipe 2 for payload available for reading from RX_FIFO
#define NORDIC_STATUS_RX_P_NO_3   	 (0x06)  						// pipe 3 for payload available for reading from RX_FIFO
#define NORDIC_STATUS_RX_P_NO_4   	 (0x08)  						// pipe 4 for payload available for reading from RX_FIFO
#define NORDIC_STATUS_RX_P_NO_5   	 (0x0A)  						// pipe 5 for payload available for reading from RX_FIFO


// CARRIER DETECT
#define NORDIC_CD_CD(x)			(uint8_t)(x)	//LSB of carrier detect register


// DYNPD register
#define NORDIC_DPL_P5(x)		(uint8_t)((uint8_t)(x)<<5)		//Enable dyn. payload length data pipe 5
#define NORDIC_DPL_P4(x)		(uint8_t)((uint8_t)(x)<<4)		//Enable dyn. payload length data pipe 4
#define NORDIC_DPL_P3(x)		(uint8_t)((uint8_t)(x)<<3)		//Enable dyn. payload length data pipe 3
#define NORDIC_DPL_P2(x)		(uint8_t)((uint8_t)(x)<<2)		//Enable dyn. payload length data pipe 2
#define NORDIC_DPL_P1(x)		(uint8_t)((uint8_t)(x)<<1)		//Enable dyn. payload length data pipe 1
#define NORDIC_DPL_P0(x)		(uint8_t)((uint8_t)(x)<<0)		//Enable dyn. payload length data pipe 0


// FEATURE REGISTER
#define NORDIC_EN_DPL(x)		(uint8_t)((uint8_t)(x)<<2)		//Enable dynamic payload length
#define NORDIC_EN_ACK_PAY(x)	(uint8_t)((uint8_t)(x)<<1)		//Enables payload with ACK
#define NORDIC_EN_DYN_ACK(x)	(uint8_t)((uint8_t)(x)<<0)		//Enables the W_TX_PAYLOAD_NOACK command


// Function prototypes
void NORDIC_Write(uint8_t register1, uint8_t value);
void NORDIC_Config(void);
void CE_High(void);
void CE_Low(void);
void NORDIC_Write_Multiple(uint8_t register1, uint8_t *loc, uint8_t size);
uint8_t NORDIC_Get_Status(void);
void NORDIC_RF_Setup(void);
void NORDIC_TX_Payload(uint8_t *payload, uint8_t Payload_size);
void NORDIC_TX_Flush(void);
void NORDIC_RX_Flush(void);


#endif /* INCLUDES_NRF24L01_H_ */
