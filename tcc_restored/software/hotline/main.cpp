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
	teste.monitore_channel();

    return 0;
}
