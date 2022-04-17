
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
#include "alt_types.h"
#include "altera_avalon_spi_regs.h"
#include "altera_avalon_spi.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "io.h"
#include <stdio.h>
#include <unistd.h>// usleep


int main(void) {
	printf("Entered Main\n");

	alt_u8 tx_buf[8] = {0};
	alt_u8 rx_buf[8] = {0};

	//definir master clock e verificar se cfail foi pra 0
	tx_buf[0]= 0x46;
    tx_buf[1] = 0x32;
    tx_buf[2] = 0x55;
    tx_buf[3] = 0x04; //hardware reset


	//hardware reset
	printf("Enviando comando %02x:  para fazer um hardware reset\n", tx_buf[3]);
	IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &tx_buf[3], 0, &rx_buf[3], 0);

    usleep(10000000);

	//configurando master clock
	printf("Enviando comando %02x e ap�s %02x para configurar o master clock: \n", tx_buf[0],tx_buf[1]);
	IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &tx_buf[0], 0, &rx_buf[0], 0);
	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &tx_buf[1], 0, &rx_buf[1], 0);

	usleep(1000000);

	//verificar cfail ap�s definir masterclock
	printf("Enviando comando %02x para verificar o cfail \n", tx_buf[2]);
	IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &tx_buf[2], 0, &rx_buf[2], 0);


	IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 0);
	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 0, &tx_buf[2], 1, &rx_buf[2], 0);
	printf("Valor recebido do codec: %02x: \n",rx_buf[2]);

	//verificar se configurou o master clock
	tx_buf[0] = 0x47;
	printf("Enviando comando %02x para verificar o master clock configurado: \n", tx_buf[0]);
	IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &tx_buf[0], 0, &rx_buf[0], 0);


	IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 0);
	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 0, &tx_buf[0], 1, &rx_buf[0], 0);
	printf("Valor recebido do codec: %02x: \n",rx_buf[0]);

	usleep(1000000);

	//definir coeficientes
	tx_buf[0]= 0x60;
	tx_buf[1] = 0x00; //coeficientes padr�es

	printf("Enviando comando %02x e ap�s %02x para configurar os coeficientes \n", tx_buf[0],tx_buf[1]);
	IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &tx_buf[0], 0, &rx_buf[0], 0);
	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &tx_buf[1], 0, &rx_buf[1], 0);

	usleep(1000000);

	//verificar se configurou os coeficientes
	tx_buf[0] = 0x61;
	printf("Enviando comando %02x para verificar coeficientes configurados \n", tx_buf[0]);
	IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &tx_buf[0], 0, &rx_buf[0], 0);


	IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 0);
	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 0, &tx_buf[0], 1, &rx_buf[0], 0);
	printf("Valor recebido do codec: %02x: \n",rx_buf[0]);

	usleep(1000000);

	//Configurar registradores dos canais
	tx_buf[0] = 0x4a;
	tx_buf[1] = 0x03;

	printf("Enviando comando %02x e ap�s %02x para configurar os registradores dos canais \n", tx_buf[0],tx_buf[1]);
	IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &tx_buf[0], 0, &rx_buf[0], 0);
	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &tx_buf[1], 0, &rx_buf[1], 0);

	usleep(1000000);

	//verificar se configurou os registradores dos canais
	tx_buf[0] = 0x4b;
	printf("Enviando comando %02x para verificar registradores dos canais \n", tx_buf[0]);
	IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &tx_buf[0], 0, &rx_buf[0], 0);


	IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 0);
	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 0, &tx_buf[0], 1, &rx_buf[0], 0);
	printf("Valor recebido do codec: %02x: \n",rx_buf[0]);


	//definir direcao dos slics
	tx_buf[0]= 0x54;
	tx_buf[1] = 0x02; //CD1 e CD2

	printf("Enviando comando %02x e ap�s %02x para configurar a direcao dos slics \n", tx_buf[0],tx_buf[1]);
	IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &tx_buf[0], 0, &rx_buf[0], 0);
	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &tx_buf[1], 0, &rx_buf[1], 0);

	usleep(1000000);

	//verificar se CSTAT est� em 0 antes de ativar o codec
	tx_buf[0]= 0x55;

	printf("Enviando comando %02x para verificar o CSTAT e a direcao dos slics\n", tx_buf[0]);
	IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &tx_buf[0], 0, &rx_buf[0], 0);


	IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 0);
	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 0, &tx_buf[0], 1, &rx_buf[0], 0);
	printf("Valor recebido do codec: %02x: \n",rx_buf[0]);

	//ativar o codec
	tx_buf[0]= 0x0E;

	printf("Enviando comando %02x para ativar o codec \n", tx_buf[0]);
	IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &tx_buf[0], 0, &rx_buf[0], 0);


	usleep(1000000);

	//verificar se ativou o codec, CSTAT deve estar em 1
	tx_buf[0]= 0x55;

	printf("Enviando comando %02x para verificar se o codec ativou \n", tx_buf[0]);
	IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &tx_buf[0], 0, &rx_buf[4], 0);

	IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 0);
	alt_avalon_spi_command(SPI_MASTER_BASE, 0, 0, &tx_buf[0], 1, &rx_buf[4], 0);
	printf("Valor recebido codec: %02x: \n",rx_buf[4]);




//}





		// Coloca um valor no buffer de saida do slave para ser enviado ao master.
//		IOWR_ALTERA_AVALON_SPI_TXDATA(SPI_SLAVE_BASE, 0xAA);


		 // end while


} // end main

