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
/* 	usleep(1000000);

	// while (1) {


	// } // end while

	return 0;
*/
} // end main