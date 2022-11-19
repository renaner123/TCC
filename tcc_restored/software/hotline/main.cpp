#include "placaramal.h"
#include "alt_types.h"
#include "altera_avalon_spi_regs.h"
#include "altera_avalon_spi.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "io.h"
#include <stdio.h>
#include <unistd.h>// usleep


int main(int argc, char **argv)
{
	Placaramal teste;

	teste.init();
	teste.ringar_canal();//5 toques e somente o canal 1

    return 0;
}


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
