#ifndef LCD_FRDM_H_
#define LCD_FRDM_H_

#include "MKL25Z4.h"
#include "stdint.h"

/***************************************\
|* Define Ports Used for Communication *| For now, all pins should be on the same port
\***************************************/
/* Data pins must be on same port */
//uint8_t     LCD_DIR_DATA  =   (0xFF);
//uint8_t     LCD_OUT_DATA   =  (0xFF);

/* Reg Select Port */
//uint8_t     LCD_DIR_RS  =   (0xFF);
//uint8_t     LCD_OUT_RS   =  (0xFF);

/* Read/Write Port */
//uint8_t     LCD_DIR_RW  =   (0xFF);
//uint8_t     LCD_OUT_RW   =  (0xFF);

/* Enable Port */
//uint8_t     LCD_DIR_EN  =   (0xFF);
//uint8_t     LCD_OUT_EN   =  (0xFF);


/**   NO  SYMBOL NO   SYMBOL FUNCTION     KL25Z pin
*   1       VSS     Supply Ground           GND
*   2       VDD     Supply Voltage          3.3V
*   3       VO      Contrast Adj            3.3V
*   4       RS      Register Select         D7
*   5       R/W     Read/Write              D6
*   6       E       Enable Signal           D1
*   7       DB0     Data Bit 0              NC
*   8       DB1     Data Bit 1              NC
*   9       DB2     Data Bit 2              NC    
*   10      DB3     Data Bit 3              NC
*   11      DB4     Data Bit 4              D3
*   12      DB5     Data Bit 5              D2
*   13      DB6     Data Bit 6              D0
*   14      DB7     Data Bit 7              D5
*   15      A       LED Power               NC
*   16      K       LED Power               NC
**/

/*************************************\
|* Define Pins Used for Communication*|
\*************************************/
/* Data pins must be consecutive & ascending */
#define     LCD_PIN_D4        PORTD_PCR3
#define     LCD_PIN_D5        PORTD_PCR2
#define     LCD_PIN_D6        PORTD_PCR0
#define     LCD_PIN_D7        PORTD_PCR5

#define     LCD_PIN_RS        PORTD_PCR7
#define     LCD_PIN_RW        PORTD_PCR6
#define     LCD_PIN_EN        PORTD_PCR1

#define     LCD_MASK_DATA     (LCD_PIN_D7 | LCD_PIN_D6 | LCD_PIN_D5 | LCD_PIN_D4)


/*****************************************\
|* Define Useful Display Characteristics *|
\*****************************************/
#define     LCD_NUM_COLS      16
#define     LCD_NUM_ROWS      2


/***************************\
|* Define Display Commands *|
\***************************/
/* Function Set Defines */
#define     FUNCTION_SET      0x20  // Must be set to execute FUNCTION_SET_CMD
#define     INTFC_DATA_LEN    0x10  // HIGH: 8-bit interface | LOW: 4-bit interface
#define     TWO_LINE_DISP     0x08  // HIGH: 2-line display | LOW: 1-line display
#define     CHAR_FONT_SIZE    0x04  // HIGH: 5x10 dots | LOW: 5x8 dots (only usable with 1-line display)

/* Function Set Command - modify to liking */
#define     FUNCTION_SET_CMD  (FUNCTION_SET | TWO_LINE_DISP)

/* Display Initialization Defines */
#define     DISPLAY_ON        0x08  // Must be set to execute DISPLAY_ON_CMD
#define     ENTIRE_DISP_ON    0x04
#define     CURSOR_ON         0x02  // Show the cursor at current position
#define     CURSOR_BLINK_ON   0x01  // Make the cursor blink

/* Display Initialization Command - modify to liking */
#define     DISPLAY_ON_CMD    (DISPLAY_ON | ENTIRE_DISP_ON | CURSOR_ON)

/* Entry Mode Initialization Defines */
#define     ENTRY_MODE        0x04  // Must be set to execute ENTRY_MODE_CMD
#define     CURSOR_INCR       0x02  // Cursor increment on character write, else decrement
#define     DISPLAY_SHIFT_ON  0x01  // Shift display according to CURSOR_INCR

/* Entry Mode Initialization Command - modify to liking */
#define     ENTRY_MODE_CMD    (ENTRY_MODE | CURSOR_INCR)

/* Miscellaneous Commands */
#define     CLEAR_DISP_CMD    0x01  // Clear the display
#define     RET_HOME_CMD      0x02  // Return cursor to top left (0,0)


/****************************\
|* Useful Data Type Defines *|
\****************************/
#define     COMMAND           0
#define     DATA              1


/******************************\
|* Public Function Prototypes *|
\******************************/
void LCD_init(void);
void LCD_printStr(char *text);
void LCD_printChar(char character);
void LCD_sendCommand(char command);
void LCD_setCursorPosition(uint8_t row, uint8_t col);
void LCD_clearScreen(void);
void LCD_sendByte(char byteToSend, uint8_t byteType);

#endif
