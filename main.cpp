#include "libs/alt_types.h"
#include "libs/altera_avalon_spi_regs.h"
#include "libs/altera_avalon_spi.h"
#include "libs/system.h"
#include "libs/altera_avalon_pio_regs.h"
#include "io.h"
#include <stdio.h>
#include <unistd.h>// usleep
#include "placaramal.h"
#include <iostream>

using namespace std;

int main(void) {

	Placaramal teste;

	teste.init();
	usleep(1000000);

	teste.tirarGancho(1);
	usleep(1000000);

	teste.tomDiscagem();
	usleep(1000000);

	teste.tocarRing();
	usleep(1000000);

	teste.atendimento();



    //printf("%02x\n",tx_buf[0]);


	// while (1) {


	// 	printf("Escrevendo no CODEC 4 bytes: \n");
	// 	IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
	// 	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 4, &tx_buf[0], 0, &rx_buf[0], 0);

	// 	// Coloca um valor no buffer de saida do slave para ser enviado ao master.
	// 	IOWR_ALTERA_AVALON_SPI_TXDATA(SPI_SLAVE_BASE, 0xAA);

	// 	printf("Lendo do CODEC 4 bytes: \n");
	// 	IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 0);
	// 	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 0, &tx_buf[0], 4, &rx_buf[0], 0);

	// 	usleep(1000000);

	// } // end while

	return 0;

} // end main