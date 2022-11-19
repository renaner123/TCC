#include "placaramal.h"

Placaramal::Placaramal() {

}

    void Placaramal::init(){

    	this->write_codec(HARDWARE_RESET);
		usleep(4000000);
        this->definir_master_clock();
//#usleep(1000000);
        printf("Valor recebido do codec: %02x: \n",this->read_codec(READ_CHIP_CONFIGURATION_REGISTER));
        this->configurar_debounce_time();
        this->configurar_time_slot();
        printf("Valor recebido do codec: %02x: \n",this->read_codec(READ_SLIC_DIRECTION_STATUS_BITS));
        this->configurar_registradores_canais();
        this->configurar_interrupt_mask();
        this->set_coefficients(0x00);
        this->configurar_direcao_slic();
        this->activate_codec();
        printf("Valor recebido do codec: %02x: \n",this->read_codec(READ_SLIC_DIRECTION_STATUS_BITS));
        IOWR_ALTERA_AVALON_PIO_DATA(RST_QSYS_BASE, 1);
        usleep(50000);
        IOWR_ALTERA_AVALON_PIO_DATA(RST_QSYS_BASE, 0);
    }

    void Placaramal::definir_master_clock(){
        this->write_codec(WRITE_CHIP_CONFIGURATION_REGISTER,MASTER_CLOCK);
    }

    void Placaramal::configurar_debounce_time(){
        this->write_codec(WRITE_CHANNEL_ENABLE,DEBOUNCE_TIME);
    }

    void Placaramal::configurar_time_slot(){
        this->write_codec(WRITE_SET_TIMESLOT,TIME_SLOT);
    }

    void Placaramal::configurar_time_real_data(){
        this->write_codec(WRITE_REAL_TIME_DATA_REGISTER,TIME_REAL_DATA);
    }

    void Placaramal::set_coefficients(alt_u8 operation ){
        this->write_codec(WRITE_OPERATING_FUNCTIONS, operation);
    }

    void Placaramal::configurar_registradores_canais(){
        //estático por enquanto
        alt_u8 channel1e2 = 0x03;
        this->write_codec(WRITE_CHANNEL_ENABLE,channel1e2);
    }

    void Placaramal::configurar_direcao_slic(){
        this->write_codec(WRITE_SLIC_DIRECTION_STATUS_BITS,DIRECTION_SLIC_CD1_CD2);
    }

	void Placaramal::configurar_direcao_slic(alt_u8 operation){
		this->write_codec(WRITE_SLIC_DIRECTION_STATUS_BITS,operation);
	}

    void Placaramal::activate_codec(){
        this->write_codec(ACTIVATE_CODEC);
    }

    void Placaramal::configurar_interrupt_mask(){
        this->write_codec(WRITE_INTERRUPT_MASK_REGISTER,INTERRUPT_MASK);
    }

    bool Placaramal::is_cfail(alt_u8 analisar_byte){

        //printf("%02x\n",analisar_byte);
        return false;
    }

    void Placaramal::ringar_canal(){
    //por enquanto está estático canal 1
    int count = 0;

    this->write_codec(WRITE_CHANNEL_ENABLE,CHANNEL_1);
    this->write_codec(AISN_ANALOG_GAINS,0x00);
    this->set_coefficients(0x3F);
    this->set_coefficients(0x3F);
    this->write_codec(AISN_ANALOG_GAINS,0x00);
    this->activate_codec();
    this->transmit_time_slot(0x00);
    this->receive_time_slot(0x00);

    this->write_codec(WRITE_CHANNEL_ENABLE,CHANNEL_2);
    this->write_codec(AISN_ANALOG_GAINS,0x80);
    this->write_codec(WRITE_CHANNEL_ENABLE,CHANNEL_2);
    this->set_coefficients(0x3F);
    this->set_coefficients(0x3F);
    this->write_codec(AISN_ANALOG_GAINS,0x00);
    this->activate_codec();
    this->transmit_time_slot(0x01);
    this->receive_time_slot(0x01);

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
        this->limparbuffer();
        this->tx_buf[0]=comando_codec;

        IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &this->tx_buf[0], 0, &this->rx_buf[0], 0);

        IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 0);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 0, &this->tx_buf[0], 1, &this->rx_buf[0], 0);
        return this->rx_buf[0];
    }

    void Placaramal::write_codec(alt_u8 comando_codec, alt_u8 valor_comando){

        this->limparbuffer();
        this->tx_buf[0]=comando_codec;
        this->tx_buf[1]=valor_comando;

        IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &this->tx_buf[0], 0, &this->rx_buf[0], 0);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &this->tx_buf[1], 0, &this->rx_buf[1], 0);
    }

    void Placaramal::write_codec(alt_u8 comando_codec){
        this->limparbuffer();
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
    	printf("Valor recebido do codec: %02x: \n",this->read_codec(WRITE_REAL_TIME_DATA_REGISTER_CLEAR_INTERRUPT));
    	}
    }


    void Placaramal::limparbuffer(){
        for(int i=0;i<TAMANHOBUFFER;i++){
            this->tx_buf[i] = 0;
            this->rx_buf[i]= 0;
        }
}

