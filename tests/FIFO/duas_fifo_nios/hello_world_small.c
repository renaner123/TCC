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
# define ALMOST_FULL 1000               //FIFO Depth 1024
#include <stdio.h>

int init_input_fifo1(){
	int return_code = ALTERA_AVALON_FIFO_OK;
	return_code = altera_avalon_fifo_init(FIFO_0_IN_CSR_BASE,0,ALMOST_EMPTY,ALMOST_FULL);
	altera_avalon_fifo_init(FIFO_0_IN_CSR_BASE,0,ALMOST_EMPTY,ALMOST_FULL);
	return return_code;
}
int init_input_fifo2(){
	int return_code = ALTERA_AVALON_FIFO_OK;
	return_code = altera_avalon_fifo_init(FIFO_1_IN_CSR_BASE,0,ALMOST_EMPTY,ALMOST_FULL);
	altera_avalon_fifo_init(FIFO_1_IN_CSR_BASE,0,ALMOST_EMPTY,ALMOST_FULL);
	return return_code;
}
int main()
{
	int i =0, level;
	//alt_32 result_cont;
	long int data[200];
	long int data2[200];
	init_input_fifo1();
	init_input_fifo2();
	alt_32 dado1 = 0x01;
	alt_32 dado2 = 0x02;
	alt_32 dado3 = 0x03;
	alt_32 dado4 = 0x04;
	alt_32 dado5 = 0x05;
	IOWR(TX_EN_BASE, 0, 0x1);

	printf("STATUS = %d\n", altera_avalon_fifo_read_status(FIFO_0_IN_CSR_BASE, ALTERA_AVALON_FIFO_STATUS_ALL));
	level=altera_avalon_fifo_read_level(FIFO_0_IN_CSR_BASE);
	printf("\nLevel=%u\n",level);

	altera_avalon_fifo_write_fifo(FIFO_0_IN_BASE,FIFO_0_IN_CSR_BASE,dado1);
	altera_avalon_fifo_write_fifo(FIFO_0_IN_BASE,FIFO_0_IN_CSR_BASE,dado2);
	altera_avalon_fifo_write_fifo(FIFO_0_IN_BASE,FIFO_0_IN_CSR_BASE,dado3);
	altera_avalon_fifo_write_fifo(FIFO_0_IN_BASE,FIFO_0_IN_CSR_BASE,dado4);
	altera_avalon_fifo_write_fifo(FIFO_0_IN_BASE,FIFO_0_IN_CSR_BASE,dado5);

	for(i=0;i<5;i++)
	 {
		//result[i]=IORD_ALTERA_AVALON_FIFO_DATA(FIFO_0_OUT_BASE);
		//printf("%u", FIFO_0_IN_CSR_USE_AVALONMM_READ_SLAVE);
		//printf("%u", FIFO_0_IN_CSR_USE_BACKPRESSURE);
		//printf("%u", FIFO_0_IN_CSR_USE_READ_CONTROL);
		//printf("%u", FIFO_0_IN_CSR_USE_REGISTER);
		data[i]=altera_avalon_fifo_read_fifo(FIFO_0_OUT_BASE, FIFO_0_IN_CSR_BASE);
		printf("data=%u recebido na fifo_0, escrevendo na fifo_1 \n" ,data[i]);
		altera_avalon_fifo_write_fifo(FIFO_1_IN_BASE,FIFO_1_IN_CSR_BASE,data[i]);
		usleep(1000000);
		//altera_avalon_fifo_clear_event(FIFO_0_OUT_BASE, 0x1);
		//IORD_ALTERA_AVALON_PIO_CLEAR_BITS(FIFO_0_OUT_BASE);
		//result_cont = IORD_ALTERA_AVALON_FIFO_DATA(FIFO_0_OUT_BASE);
		//printf("%d %032x\n",result_cont, result_cont);
	   }
	i=0;
	for(i=0;i<5;i++)
	 {
		data2[i]=altera_avalon_fifo_read_fifo(FIFO_1_OUT_BASE, FIFO_1_IN_CSR_BASE);
		printf("data=%u recebido na fifo_1 \n" ,data2[i]);
		usleep(1000000);
		//result_cont = IORD_ALTERA_AVALON_FIFO_DATA(FIFO_0_OUT_BASE);
		//printf("%d %032x\n",result_cont, result_cont);
	   }
	//printf("\nFull=%d\n", altera_avalon_fifo_read_almostfull(FIFO_0_IN_CSR_BASE));
	//printf("Empty=%d\n",altera_avalon_fifo_read_almostempty(FIFO_0_IN_CSR_BASE));


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
