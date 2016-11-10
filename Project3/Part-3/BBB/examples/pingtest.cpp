/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * Example RF Radio Ping Pair
 *
 * This is an example of how to use the RF24 class.  Write this sketch to two different nodes,
 * connect the role_pin to ground on one.  The ping node sends the current time to the pong node,
 * which responds by sending the value back.  The ping node can then see how long the whole cycle
 * took.
 */

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "RF24.h"

#include "nRF24L01.h"

//
// Hardware configuration
//

RF24 radio(115, 117);

int mod_config = 0;
int status_val;
int mod_status = 0;
int pwr_val;
int mod_pwr_level=0;
int mod_addr=0;
int mod_fifo=0;


// sets the role of this unit in hardware.  Connect to GND to be the 'pong' receiver
// Leave open to be the 'ping' transmitter
const int role_pin = 7;

//
// Topology
//

// Radio pipe addresses for the 2 nodes to communicate.
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

//
// Role management
//
// Set up role.  This sketch uses the same software for all the nodes
// in this system.  Doing so greatly simplifies testing.  The hardware itself specifies
// which node it is.
//
// This is done through the role_pin
//

// The various roles supported by this sketch
typedef enum { role_ping_out = 1, role_pong_back } role_e;

// The debug-friendly names of those roles
const char* role_friendly_name[] = { "invalid", "Ping out", "Pong back"};

// The role of the current running sketch
role_e role;

void setup(void)
{
  //
  // Role
  //

  // set up the role pin
 // pinMode(role_pin, INPUT);
  //digitalWrite(role_pin,HIGH);
 // delay(20); // Just to get a solid reading on the role pin

  // read the address pin, establish our role
  //if ( ! digitalRead(role_pin) )
    role = role_ping_out;
  //else
  //  role = role_pong_back;

  //
  // Print preamble:
  //

  //Serial.begin(115200);
  //printf_begin();
  printf("\n\rRF24/examples/pingpair/\n\r");
  printf("ROLE: %s\n\r",role_friendly_name[role]);

  //
  // Setup and configure rf radio
  //

  radio.begin();

  // optionally, increase the delay between retries & # of retries
  radio.setRetries(15,15);

  // optionally, reduce the payload size.  seems to
  // improve reliability
//  radio.setPayloadSize(8);
 radio.setChannel(0x4c);
     radio.setPALevel(RF24_PA_MAX);

  //
  // Open pipes to other nodes for communication
  //

  // This simple sketch opens two pipes for these two nodes to communicate
  // back and forth.
  // Open 'our' pipe for writing
  // Open the 'other' pipe for reading, in position #1 (we can have up to 5 pipes open for reading)

  if ( role == role_ping_out )
  {
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);
  }
  else
  {
    radio.openWritingPipe(pipes[1]);
    radio.openReadingPipe(1,pipes[0]);
  }

  //
  // Start listening
  //

  radio.startListening();

  //
  // Dump the configuration of the rf unit for debugging
  //

  radio.printDetails();
}

void loop(void)
{

  //Verifying if a write to the CONFIG register works
  mod_config++;
  radio.write_register(CONFIG, _BV(PWR_UP)|_BV(PRIM_RX));

  if(radio.read_register(CONFIG)==0x03){
        if(mod_config==1)
        cout<<"NORDIC CONFIG successful!"<<endl;
  }

  // verifying if the status register gives the correct value
  mod_status++;
  status_val =  radio.get_status();
  if(status_val==0x0e){
        if(mod_status==1)
 //Verifying if a write to the CONFIG register works
  mod_config++;
  radio.write_register(CONFIG, _BV(PWR_UP)|_BV(PRIM_RX));

  if(radio.read_register(CONFIG)==0x03){
        if(mod_config==1)
        cout<<"NORDIC CONFIG successful!"<<endl;
  }

  // verifying if the status register gives the correct value
  mod_status++;
  status_val =  radio.get_status();
  if(status_val==0x0e){
        if(mod_status==1)
                cout<<"NORDIC status received is 0x0e"<<endl;
 }
 

// Verifying if the power transmitted is actually -6dBm (or RF_PWR_HIGH)
 mod_pwr_level++;
 radio.write_register(RF_SETUP, _BV(RF_PWR_HIGH)|_BV(RF_DR_HIGH));
 if(radio.read_register(RF_SETUP)==( _BV(RF_PWR_HIGH)|_BV(RF_DR_HIGH))){
//      if(mod_pwr_level == 1)
//              cout<<"NORDIC RF power level is RF_PWR_HIGH (or -6dBm)"<<endl;
 }


// Reading the value of the fifo_status register
mod_fifo++;
int fifo_var = radio.read_register(FIFO_STATUS);
 

// Verifying if the power transmitted is actually -6dBm (or RF_PWR_HIGH)
 mod_pwr_level++;
 radio.write_register(RF_SETUP, _BV(RF_PWR_HIGH)|_BV(RF_DR_HIGH));
 if(radio.read_register(RF_SETUP)==( _BV(RF_PWR_HIGH)|_BV(RF_DR_HIGH))){
//      if(mod_pwr_level == 1)
//              cout<<"NORDIC RF power level is RF_PWR_HIGH (or -6dBm)"<<endl;
 }


// Reading the value of the fifo_status register
mod_fifo++;
int fifo_var = radio.read_register(FIFO_STATUS);
        if(mod_fifo==1){
                printf("\nNORDIC FIFO_status is %x ",fifo_var);
                cout<<"NORDIC FIFO_status is "<<radio.read_register(FIFO_STATUS)<<endl;
  }


// setting the TX address
mod_addr++;
radio.write_register(TX_ADDR, 0xE7E7E7E7E7ll);
        if(mod_addr==1)
                cout<<"NORDIC TX address is :"<<radio.read_register(TX_ADDR)<<endl;
}



int main(int argc, char** argv)
{
        setup();
        while(1)
                loop();

        return 0;
}


// vim:cin:ai:sts=2 sw=2 ft=cpp
