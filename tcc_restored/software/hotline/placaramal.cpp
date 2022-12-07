#include "placaramal.h"

Placaramal::Placaramal() {

}

    void Placaramal::init(){

    	this->write_codec(HARDWARE_RESET);
		usleep(4000000);
        this->set_master_clock(MASTER_CLOCK);
        //#usleep(1000000);
        printf("Valor recebido do codec: %02x: \n",this->read_codec(READ_CHIP_CONFIGURATION_REGISTER));
        this->set_debounce_time(DEBOUNCE_TIME);
        this->set_time_slot(TIME_SLOT);
        printf("Valor recebido do codec: %02x: \n",this->read_codec(READ_SLIC_DIRECTION_STATUS_BITS));
        this->channel_enable(CHANNEL_1);
        this->set_interrupt_mask(INTERRUPT_MASK);
        this->set_coefficients(0x00);
        this->set_slic_direction(DIRECTION_SLIC_CD1_CD2);
        this->activate_codec();
        printf("Valor recebido do codec: %02x: \n",this->read_codec(READ_SLIC_DIRECTION_STATUS_BITS));

        this->write_codec(WRITE_CHANNEL_ENABLE,CHANNEL_1);
        this->write_codec(WRITE_IO_REGISTER,0x1E);
        this->write_codec(WRITE_CHANNEL_ENABLE,0x08);
        this->write_codec(WRITE_IO_REGISTER,0x1E);

    }

    void Placaramal::set_master_clock(alt_u8 clock){
        this->write_codec(WRITE_CHIP_CONFIGURATION_REGISTER, clock);
    }

    void Placaramal::set_debounce_time(alt_u8 debounce){
        this->write_codec(WRITE_DEBOUNCE_TIME_REGISTER, debounce);
    }
    
    void Placaramal::set_time_slot(alt_u8 time_slot){
        this->write_codec(WRITE_SET_TIMESLOT,time_slot);
    }

    void Placaramal::set_time_real_data(){
        this->write_codec(WRITE_REAL_TIME_DATA_REGISTER,TIME_REAL_DATA);
    }

    void Placaramal::set_coefficients(alt_u8 operation){
        this->write_codec(WRITE_OPERATING_FUNCTIONS, operation);
    }

    void Placaramal::channel_enable(alt_u8 channell){
        //est�tico por enquanto
        this->write_codec(WRITE_CHANNEL_ENABLE,channell);
    }

    void Placaramal::set_slic_direction(){
        this->write_codec(WRITE_SLIC_DIRECTION_STATUS_BITS,DIRECTION_SLIC_CD1_CD2);
    }

    void Placaramal::set_slic_direction(alt_u8 direction){
        this->write_codec(WRITE_SLIC_DIRECTION_STATUS_BITS, direction);
    }

    void Placaramal::activate_codec(){
        this->write_codec(ACTIVATE_CODEC);
    }

    void Placaramal::set_interrupt_mask(alt_u8 mask){
        this->write_codec(WRITE_INTERRUPT_MASK_REGISTER, mask);
    }

    void Placaramal::operating_conditions(){
        this->write_codec(OPERATING_CONDITIONS,0x00);
    }

    bool Placaramal::is_cfail(alt_u8 analisar_byte){

        //printf("%02x\n",analisar_byte);
        return false;
    }

    void Placaramal::init_channel1(){
        this->write_codec(WRITE_CHANNEL_ENABLE,CHANNEL_1);
        this->write_codec(AISN_ANALOG_GAINS,0x00);
        this->set_coefficients(0x3F);
        this->set_coefficients(0x3F);
        this->write_codec(AISN_ANALOG_GAINS,0x00);
        this->activate_codec();
        this->transmit_time_slot(0x00);
        this->receive_time_slot(0x00);

    }

    void Placaramal::init_channel2(){

        this->write_codec(WRITE_CHANNEL_ENABLE,CHANNEL_2);
        this->write_codec(AISN_ANALOG_GAINS,0x80);
        this->write_codec(WRITE_CHANNEL_ENABLE,CHANNEL_2);
        this->set_coefficients(0x3F);
        this->set_coefficients(0x3F);
        this->write_codec(AISN_ANALOG_GAINS,0x00);
        this->activate_codec();
        this->transmit_time_slot(0x01);
        this->receive_time_slot(0x01);
    }

    void Placaramal::channel_ring(){
    int count = 0;

    IOWR_ALTERA_AVALON_PIO_DATA(RST_QSYS_BASE, 1);
    usleep(500000);
    IOWR_ALTERA_AVALON_PIO_DATA(RST_QSYS_BASE, 0);

    this->init_channel1();
    this->init_channel2();

        while (count<2) {
            this->write_codec(WRITE_CHANNEL_ENABLE,CHANNEL_1);
            this->write_codec(WRITE_IO_REGISTER,RING_CHANNEL);
            usleep(1000000);
            this->write_codec(WRITE_IO_REGISTER,STOP_RING_CHANNEL);
            usleep(4000000);
            count ++;
        }
        this->write_codec(WRITE_CHANNEL_ENABLE,CHANNEL_2);
        this->write_codec(AISN_ANALOG_GAINS,0x00);
        this->set_coefficients(0x3F);
        this->write_codec(WRITE_IO_REGISTER,0x1F);
    }

    alt_u8 Placaramal::read_codec(alt_u8 comando_codec){
        this->clean_buffer();
        this->tx_buf[0]=comando_codec;

        IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &this->tx_buf[0], 0, &this->rx_buf[0], 0);

        IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 0);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 0, &this->tx_buf[0], 1, &this->rx_buf[0], 0);
        return this->rx_buf[0];
    }

    void Placaramal::write_codec(alt_u8 comando_codec, alt_u8 valor_comando){

        this->clean_buffer();
        this->tx_buf[0]=comando_codec;
        this->tx_buf[1]=valor_comando;

        IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &this->tx_buf[0], 0, &this->rx_buf[0], 0);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &this->tx_buf[1], 0, &this->rx_buf[1], 0);
    }

    void Placaramal::write_codec(alt_u8 comando_codec){
        this->clean_buffer();
        this->tx_buf[0]=comando_codec;

        IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &this->tx_buf[0], 0, &this->rx_buf[0], 0);
    }

    void Placaramal::transmit_time_slot(alt_u8 timeslot){
        this->write_codec(TRANSMIT_TIME_SLOT, timeslot);
    }

    void Placaramal::receive_time_slot(alt_u8 timeslot){
        this->write_codec(RECEIVE_TIME_SLOT, timeslot);
    }
    void Placaramal::monitore_channel(){
    	while(true){
    	usleep(3000000);
    	alt_u8 retorno = this->read_codec(WRITE_REAL_TIME_DATA_REGISTER_CLEAR_INTERRUPT);
    	if(retorno==0xAE){
    		channel_ring();
    	}
    	printf("Valor recebido do codec: %02x: \n", retorno);
    	}
    }


    void Placaramal::clean_buffer(){
        for(int i=0;i<TAMANHOBUFFER;i++){
            this->tx_buf[i] = 0;
            this->rx_buf[i]= 0;
        }
}
