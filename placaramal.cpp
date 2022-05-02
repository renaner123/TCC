#include "placaramal.h"

Placaramal::Placaramal() {

}

    void Placaramal::init(){ 
        
    	this->writeCodec(HARDWARE_RESET);
    	usleep(4000000);
        this->definirMasterClock();
        usleep(1000000);
        printf("Valor recebido do codec: %02x: \n",this->readCodec(READ_CHIP_CONFIGURATION_REGISTER));
        this->configurarDebounceTime();
        usleep(1000000);
        this->configurarTimeSlot();  
        usleep(1000000);
        printf("Valor recebido do codec: %02x: \n",this->readCodec(READ_SLIC_DIRECTION_STATUS_BITS));
        this->configurarRegistradoresCanais();
        usleep(1000000);
        this->configurarInterruptMask();
        usleep(1000000);
        this->definirCoefienctes();
        usleep(1000000);
        this->configurarDirecaoSlic();
        usleep(1000000);
        this->comandoAtivarCodec();
        printf("Valor recebido do codec: %02x: \n",this->readCodec(READ_SLIC_DIRECTION_STATUS_BITS));
    }

    void Placaramal::definirMasterClock(){
        this->writeCodec(WRITE_CHIP_CONFIGURATION_REGISTER,MASTER_CLOCK);
    }

    void Placaramal::configurarDebounceTime(){
        this->writeCodec(WRITE_CHANNEL_ENABLE,DEBOUNCE_TIME);
    }

    void Placaramal::configurarTimeSlot(){
        this->writeCodec(WRITE_SET_TIMESLOT,TIME_SLOT);
    }

    void Placaramal::configurarTimeRealData(){
        this->writeCodec(WRITE_REAL_TIME_DATA_REGISTER,TIME_REAL_DATA);
    }

    void Placaramal::definirCoefienctes(){
        this->writeCodec(WRITE_OPERATING_FUNCTIONS,DEFAULT_COEFFICIENT);
    }

    void Placaramal::configurarRegistradoresCanais(){
        //estático por enquanto
        alt_u8 channel1e2 = 0x03;
        this->writeCodec(WRITE_CHANNEL_ENABLE,channel1e2);
    }

    void Placaramal::configurarDirecaoSlic(){
        this->writeCodec(WRITE_SLIC_DIRECTION_STATUS_BITS,DIRECTION_SLIC_CD1_CD2);        
    }  

    void Placaramal::comandoAtivarCodec(){
        this->writeCodec(ACTIVATE_CODEC);
    }

    void Placaramal::configurarInterruptMask(){
        this->writeCodec(WRITE_INTERRUPT_MASK_REGISTER,INTERRUPT_MASK);
    }

    void Placaramal::ringarCanal(){
    //por enquanto está estático no canal 1 
    int count = 0;   
        while (this->Placaramal::Atendimento==false) {
            if(this->channelIsOutHook(CHANNEL_1)){
                this->Placaramal::setAtendimento(true);
                break;
            }else{
                this->writeCodec(WRITE_CHANNEL_ENABLE,CHANNEL_1);            
                this->writeCodec(WRITE_IO_REGISTER,RING_CHANNEL);
                usleep(1000000);
                this->writeCodec(WRITE_IO_REGISTER,STOP_RING_CHANNEL);
                usleep(4000000);
                count ++;
            }
        }    
        this->Placaramal::setAtendimento(false);  
    }

    alt_u8 Placaramal::readCodec(alt_u8 comando_codec){
        this->limparBuffer();
        this->tx_buf[0]=comando_codec;

        IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &this->tx_buf[0], 0, &this->rx_buf[0], 0);

        IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 0);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 0, &this->tx_buf[0], 1, &this->rx_buf[0], 0);
        return this->rx_buf[0];
    }

    void Placaramal::writeCodec(alt_u8 comando_codec, alt_u8 valor_comando){
        
        this->limparBuffer();
        this->tx_buf[0]=comando_codec;
        this->tx_buf[1]=valor_comando;

        IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &this->tx_buf[0], 0, &this->rx_buf[0], 0);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &this->tx_buf[1], 0, &this->rx_buf[1], 0);
    }

    void Placaramal::writeCodec(alt_u8 comando_codec){        
        this->limparBuffer();
        this->tx_buf[0]=comando_codec;

        IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &this->tx_buf[0], 0, &this->rx_buf[0], 0);
    }    


    bool Placaramal::channelIsOutHook(alt_u8 channel){
        this->writeCodec(WRITE_CHANNEL_ENABLE,channel);
        alt_u8 status_channel = this->readCodec(READ_IO_REGISTER);

        if(channel==CHANNEL_1 && status_channel==CHANNEL_1__OUT_HOOK){
            return true;
        }else if(channel==CHANNEL_2 && status_channel==CHANNEL_1__OUT_HOOK){
            return true;
        }else{
            return false;
        }      
    }


    void Placaramal::limparBuffer(){
        for(int i=0;i<TAMANHOBUFFER;i++){
            this->tx_buf[i] = 0;
            this->rx_buf[i]= 0;
        }  


}


