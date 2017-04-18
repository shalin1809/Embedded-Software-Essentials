#ifndef EEPROM_H_
#define EEPROM_H_

#include "MKL25Z4.h"

void i2c_init(void);
void i2c_writeByte(uint8_t slave_addr,uint8_t mem_addr,uint8_t data);
void i2c_delay(int number);
uint8_t i2c_readByte(uint8_t slave_addr,uint8_t mem_addr);

#endif
