#include "MKL25Z4.h"

void UART0_init(void);

char UART0_ReadChar(void);

__inline void UART0_WriteChar(char byte);
    
void UART0_WriteString(char string[]);

void UART0_ReadString(char * str);
