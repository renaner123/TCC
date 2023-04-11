#include "sys/alt_stdio.h"
#include "alt_types.h"
#include <io.h>
#include <system.h>
#include <stdio.h>
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_fifo.h"
#include "altera_avalon_fifo_util.h"
#include "altera_avalon_fifo_regs.h"
# define ALMOST_EMPTY 1
# define ALMOST_FULL 1000               //
#include <stdio.h>

int init_input_fifo_rx(){
	int return_code = ALTERA_AVALON_FIFO_OK;
	return_code = altera_avalon_fifo_init(FIFO_RX_IN_CSR_BASE,0,ALMOST_EMPTY,ALMOST_FULL);
	altera_avalon_fifo_init(FIFO_RX_IN_CSR_BASE,0,ALMOST_EMPTY,ALMOST_FULL);
	return return_code;
}

int init_input_fifo_tx(){
	int return_code = ALTERA_AVALON_FIFO_OK;
	return_code = altera_avalon_fifo_init(FIFO_TX_IN_CSR_BASE,0,ALMOST_EMPTY,ALMOST_FULL);
	altera_avalon_fifo_init(FIFO_TX_IN_CSR_BASE,0,ALMOST_EMPTY,ALMOST_FULL);
	return return_code;
}


int main()
{
	printf("Hello from Nios II!\n");
	alt_32 result_count = 0x00;
	init_input_fifo_tx();
	init_input_fifo_rx();
	int i =0;

	//joga o reset pra 0 pra iniciar o tdm_cont
	IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
	//joga o reset para 1
	IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 0);

	for(i=0;i<10;i++){
		  //result_count = IORD_ALTERA_AVALON_FIFO_DATA(FIFO_0_OUT_BASE);0
		  result_count=altera_avalon_fifo_read_fifo(FIFO_RX_OUT_BASE, FIFO_RX_IN_CSR_BASE);
		  altera_avalon_fifo_read_backpressure(FIFO_RX_OUT_BASE);
		  usleep(1000000);
		  printf("%lu \t ",result_count);
		  altera_avalon_fifo_clear_event(FIFO_RX_OUT_BASE,FIFO_RX_IN_CSR_BASE);
	};



  return 0;
}







/*printf("Hello from Nios II!\n");
alt_32 result_count;
int i =0;

IOWR(TX_EN_BASE,0,0x01);

//altera_avalon_fifo_init(FIFO_0_BASE,)

for(i=0;i<10;i++){
	  result_count = IORD_ALTERA_AVALON_FIFO_DATA(FIFO_0_OUT_BASE);
	  printf("%d %032x\n",result_count, result_count);
}*/


