#include "MKL25Z4.h"
#include "spi.h"

int main(void) {
	SPI_init();         /* enable SPI0 */
	while(1) {
		SPI_tx_byte('a');	//transmit character 'a' to test the transmit function
	}
}
