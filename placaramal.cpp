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

    IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
    alt_avalon_spi_command(SPI_MASTER_BASE, 0, TAMANHOBUFFER, this->tx_buf, 0, this->rx_buf, 0);
    
    this->limparbuffer();
}

void Placaramal::periodico(){ 
    this->tx_buf[0] = PERIODICO;

    IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
    alt_avalon_spi_command(SPI_MASTER_BASE, 0, TAMANHOBUFFER, this->tx_buf, 0, this->rx_buf, 0);
    
    this->limparbuffer();
   
}

void Placaramal::tirarGancho(int canal) {

    this->tx_buf[1] = INTERRUPCAO;

    if(canal==1){        
        this->tx_buf[1] = ENDERECOCANAL1;
    }else if (canal==2)
    {
        this->tx_buf[1] = ENDERECOCANAL2;
    }else if(canal ==3){
        this->tx_buf[1] = ENDERECOCANAL3;     
    }else if(canal==4){
        this->tx_buf[1] = ENDERECOCANAL3;       
    }    

    this->tx_buf[2] = LENDOESCREVENDO;        

    IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
    alt_avalon_spi_command(SPI_MASTER_BASE, 0, TAMANHOBUFFER, this->tx_buf, 0, this->rx_buf, 0);
    
    this->limparbuffer();
   
}


void Placaramal::colocarGancho() { 
    this->tx_buf[0] = INTERRUPCAO;
    this->tx_buf[1] = COMANDOREPOUSO;

    IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
    alt_avalon_spi_command(SPI_MASTER_BASE, 0, TAMANHOBUFFER, this->tx_buf, 0, this->rx_buf, 0);
    
    this->limparbuffer(); 

}

void Placaramal::tocarRing() {
    //Canal 1 ligando pro canal 2
    this->tx_buf[0] = ATENDENDO;

    IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
    alt_avalon_spi_command(SPI_MASTER_BASE, 0, TAMANHOBUFFER, this->tx_buf, 0, this->rx_buf, 0);
    
    this->limparbuffer();  
}


void Placaramal::verificarAtendimento() {
    //Verificar se recebeu 0x42

    }


void Placaramal::tomDiscagem(){ 
    //Canal 1 ligando pro canal 2
    this->tx_buf[0] = PERIODICO;
    this->tx_buf[1] = CHAMANDO;

    IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
    alt_avalon_spi_command(SPI_MASTER_BASE, 0, TAMANHOBUFFER, this->tx_buf, 0, this->rx_buf, 0);
    
    this->limparbuffer();   
}


void Placaramal::atendimento() {
     //Canal 1 ligando pro canal 2
    this->tx_buf[0] = INTERRUPCAO;
    this->tx_buf[1] = ATENDENDO;

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

Slave::Slave () {

}

 void Slave::respostaPeriodico(){};

 void Slave::respostaTirarGancho(alt_u8 comando){};

 void Slave::respostaColocarGancho(alt_u8 comando){};

 void Slave::respostaVerificarStatus(alt_u8 comando){};

 void Slave::respostaTocarRing(alt_u8 comando){};

 void Slave::respostaVerificarAtendimento(alt_u8 comando){};

 void Slave::respostaTomDiscagem(alt_u8 comando){};

 void Slave::respostaAtendimento(alt_u8 comando){};


