#include "placaramal.h"

Placaramal::Placaramal() {

}
/*
int alt_avalon_spi_command(alt_u32 base, alt_u32 slave,
                           alt_u32 write_length, const alt_u8 * write_data,
                           alt_u32 read_length, alt_u8 * read_data,
                           alt_u32 flags);
*/

void Placaramal::init(){ 
    
    this->tx_buf[0] = 0x4A;
    this->tx_buf[1] = 0x55;
    this->tx_buf[2] = 0x4A;
    this->tx_buf[3] = 0x54;
    this->tx_buf[4] = 0x4A;          
    this->tx_buf[5] = 0x53;
    this->tx_buf[6] = 0x52;  

    //printf("%02x\n",tx_buf[0]);



/*     IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
    alt_avalon_spi_command(SPI_MASTER_BASE, 0, TAMANHOBUFFER, this->tx_buf, 0, this->rx_buf, 0);
    
    this->limparbuffer(); */
}

/* void Placaramal::periodico(){ 
    this->tx_buf[0] = PERIODICO;

    IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
    alt_avalon_spi_command(SPI_MASTER_BASE, 0, TAMANHOBUFFER, this->tx_buf, 0, this->rx_buf, 0);
    
    this->limparbuffer();
   
}

void Placaramal::limparbuffer(){
    for(int i=0;i<TAMANHOBUFFER;i++){
        this->tx_buf[i] = {};
        this->rx_buf[i] = {};
    }  
}


