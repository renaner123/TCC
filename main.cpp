/*
 * Teste plataforma para acesso do CODEC da placa de ramal.
 * A plataforma multiplexa o MISO e MOSI em um sinal bidirecional
 * chamado DIO.
 *
 * Existe um slave SPI para apoiar no teste. Depois sera
 * substituido pelo CODEC.
 *
 * Controle TX_en:
 *    0: read slave
 *    1: write slave
 *
 * Autor: Roberto de Matos
 *  														*/
/////////////////////////////////
//
#include "libs/alt_types.h"
#include "libs/altera_avalon_spi_regs.h"
#include "libs/altera_avalon_spi.h"
#include "libs/system.h"
#include "libs/altera_avalon_pio_regs.h"
#include "io.h"
#include <stdio.h>
#include <unistd.h>// usleep

int main(void) {
	printf("Entered Main\n");

	printf("Testing SPI: \n");

	alt_u8 tx_buf[4] = {0};
	alt_u8 rx_buf[4] = {0};
    alt_u32 base ={};
	tx_buf[0] = 0x10;
	tx_buf[1] = 0x20;
	tx_buf[2] = 0x40;
	tx_buf[3] = 0x80;

	while (1) {

		printf("Escrevendo no CODEC 4 bytes: \n");
		IOWR_ALTERA_AVALON_PIO_DATA(base, 1);
		alt_avalon_spi_command(base, 0, 4, &tx_buf[0], 0, &rx_buf[0], 0);

		// Coloca um valor no buffer de saida do slave para ser enviado ao master.
		IOWR_ALTERA_AVALON_SPI_TXDATA(base, 0xAA);

		printf("Lendo do CODEC 4 bytes: \n");
		IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 0);
		alt_avalon_spi_command(base, 0, 0, &tx_buf[0], 4, &rx_buf[0], 0);

		usleep(1000000);

	} // end while

	return 0;

} // end main