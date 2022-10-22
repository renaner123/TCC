#include "placaramal.h"

Placaramal::Placaramal() {

}
    void Placaramal::init(){
        this->init_channel1();
        this->init_channel2(); 

        this->set_interrupt_mask(0xFE);
        this->set_interrupt_mask(0xFA);
        this->set_interrupt_mask(0xEA);
        this->set_interrupt_mask();

        printf("Valor recebido do codec: %02x: \n",this->read_codec(READ_SLIC_DIRECTION_STATUS_BITS));
    }

    void Placaramal::init_channel1(){ 

        this->channel_enable(CHANNEL_1);
        this->set_slic_direction(0x20);
        this->channel_enable(CHANNEL_1);
        this->write_codec(WRITE_IO_REGISTER,0x20);
    	this->write_codec(HARDWARE_RESET);
    	//usleep(4000000);
        this->set_master_clock();
        this->set_debounce_time();
        this->channel_enable(CHANNEL_1);
        this->set_time_slot();  
        printf("Valor recebido do codec: %02x: \n",this->read_codec(READ_SLIC_DIRECTION_STATUS_BITS));
        this->channel_enable(CHANNEL_1);
        this->read_codec(READ_IO_REGISTER);
        this->write_codec(WRITE_IO_REGISTER,0x06);
        this->channel_enable(CHANNEL_1);
        this->read_codec(READ_IO_REGISTER);
        this->channel_enable(CHANNEL_1);      
        this->write_codec(WRITE_IO_REGISTER,0x02);
        this->set_slic_direction(0x02);
        this->read_codec(0x6D);
        this->set_interrupt_mask();
        this->set_coefficients(DEFAULT_COEFFICIENT);
        this->channel_enable(CHANNEL_1);       
        this->read_codec(READ_IO_REGISTER);      
        this->channel_enable(CHANNEL_1);    
        this->write_codec(AISN_ANALOG_GAINS,0x80);
        this->filter_coefficients_gr(this->coefficient_filter_gr_channel1);
        this->filter_coefficients_gx(this->coefficient_filter_gx_channel1);
        this->set_coefficients(0x60);
        this->set_coefficients(0x30); 
        this->channel_enable(CHANNEL_1);
        this->filter_coefficients_r(this->coefficient_filter_r_channel1);
        this->filter_coefficients_z(this->coefficient_filter_z_channel1);
        this->filter_coefficients_b1(this->coefficient_filter_b1_channel1);
        this->filter_coefficients_b2(this->coefficient_filter_b2_channel1);        
        this->set_coefficients(0x37);
        this->set_coefficients(0x30);
    }

     void Placaramal::init_channel2(){ 

        this->channel_enable(CHANNEL_2);
        this->read_codec(0x53);
        this->set_slic_direction(0x1E);
        this->channel_enable(CHANNEL_2);
        this->read_codec(0x53);
        this->channel_enable(CHANNEL_2);
        this->write_codec(WRITE_IO_REGISTER,0x02);
        this->set_slic_direction(0x02);
        this->condicao_operacao();
        this->read_codec(0x6D);
        this->set_interrupt_mask();
        this->set_coefficients(DEFAULT_COEFFICIENT);
        this->channel_enable(CHANNEL_2);
        this->read_codec(0x53);
        this->channel_enable(CHANNEL_2);
        this->write_codec(AISN_ANALOG_GAINS,0x80);
        this->filter_coefficients_gr(this->coefficient_filter_gr_channel2);
        this->filter_coefficients_gx(this->coefficient_filter_gx_channel2);
        this->set_coefficients(0x30);
        this->set_coefficients(0x30);
        this->channel_enable(CHANNEL_2); 
        this->filter_coefficients_r(this->coefficient_filter_r_channel2);
        this->filter_coefficients_z(this->coefficient_filter_z_channel2);
        this->filter_coefficients_b1(this->coefficient_filter_b1_channel2);
        this->filter_coefficients_b2(this->coefficient_filter_b2_channel2);
        this->set_coefficients(0x37);
        this->set_coefficients(0x30);  
    }   

    void Placaramal::set_master_clock(){
        this->write_codec(WRITE_CHIP_CONFIGURATION_REGISTER,MASTER_CLOCK);
    }

    void Placaramal::set_debounce_time(){
        this->write_codec(WRITE_DEBOUNCE_TIME_REGISTER,DEBOUNCE_TIME);
    }

    void Placaramal::set_time_slot(){
        this->write_codec(WRITE_SET_TIMESLOT,TIME_SLOT);
    }

    void Placaramal::set_time_real_data(){
        this->write_codec(WRITE_REAL_TIME_DATA_REGISTER,TIME_REAL_DATA);
    }

    void Placaramal::set_coefficients(alt_u8 operation ){
        this->write_codec(WRITE_OPERATING_FUNCTIONS, operation);
    }

    void Placaramal::channel_enable(alt_u8 channell){
        //estático por enquanto
        this->write_codec(WRITE_CHANNEL_ENABLE,channell);
    }

    void Placaramal::set_slic_direction(alt_u8 direction ){
        this->write_codec(WRITE_SLIC_DIRECTION_STATUS_BITS, direction);        
    }  

    void Placaramal::activate_codec(){
        this->write_codec(ACTIVATE_CODEC);
    }

    void Placaramal::set_interrupt_mask(alt_u8 mask = 0xAA){
        this->write_codec(WRITE_INTERRUPT_MASK_REGISTER, mask);
    }

    void Placaramal::condicao_operacao(){
        this->write_codec(OPERATING_CONDITIONS,0x00);
    }

    void Placaramal::filter_coefficients_gr(alt_u8 coefficient_gr[2]){

        this->tx_buf[0]= GR_FILTER_COEFFICIENTS;
        alt_u8 values[2] = {0xa2, 0xa0};

        IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &this->tx_buf[0], 0, &this->rx_buf[0], 0);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 2, coefficient_gr, 0, &this->rx_buf[1], 0);
    }
    void Placaramal::filter_coefficients_gx(alt_u8 coefficient_gx[2]){
        this->tx_buf[0]= GX_FILTER_COEFFICIENTS;

        IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &this->tx_buf[0], 0, &this->rx_buf[0], 0);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 2, coefficient_gx, 0, &this->rx_buf[1], 0);
    }

    void Placaramal::filter_coefficients_r(alt_u8 coefficient_r[14]){
        this->tx_buf[0]= R_FILTER_COEFFICIENTS;

        IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &this->tx_buf[0], 0, &this->rx_buf[0], 0);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 14, coefficient_r, 0, &this->rx_buf[1], 0);
    }

    void Placaramal::filter_coefficients_z(alt_u8 coefficient_z[15]){
        this->tx_buf[0]= Z_FILTER_COEFFICIENTS;

        IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &this->tx_buf[0], 0, &this->rx_buf[0], 0);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 15, coefficient_z, 0, &this->rx_buf[1], 0);
    }

    void Placaramal::filter_coefficients_b1(alt_u8 coefficient_b1[14]){
        this->tx_buf[0]= B1_FILTER_COEFFICIENTS;

        IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &this->tx_buf[0], 0, &this->rx_buf[0], 0);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 14, coefficient_b1, 0, &this->rx_buf[1], 0);
    }

    void Placaramal::filter_coefficients_b2(alt_u8 coefficient_b2[2]){
        this->tx_buf[0]= B2_FILTER_COEFFICIENTS;

        IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 1, &this->tx_buf[0], 0, &this->rx_buf[0], 0);
        alt_avalon_spi_command(SPI_MASTER_BASE, 0, 2, coefficient_b2, 0, &this->rx_buf[1], 0);
    }

    void Placaramal::set_all_coefficients() {
		this->coefficient_filter_gr_channel1[0] = 0xa2;
		this->coefficient_filter_gr_channel1[1] = 0xa0;

		this->coefficient_filter_gx_channel1[0]  = 0x88;
		this->coefficient_filter_gx_channel1[0]  = 0x78;

 		this->coefficient_filter_r_channel1[0]  = 0x3a;
        this->coefficient_filter_r_channel1[1]  = 0xc0;
        this->coefficient_filter_r_channel1[2]  = 0x2b;
        this->coefficient_filter_r_channel1[3]  = 0x70;
        this->coefficient_filter_r_channel1[4]  = 0x23;
        this->coefficient_filter_r_channel1[5]  = 0xbe;
        this->coefficient_filter_r_channel1[6]  = 0x2d;
        this->coefficient_filter_r_channel1[7]  = 0x36;
        this->coefficient_filter_r_channel1[8]  = 0xab;
        this->coefficient_filter_r_channel1[9]  = 0xad;
        this->coefficient_filter_r_channel1[10]  = 0xab;
        this->coefficient_filter_r_channel1[11]  = 0xb6;
        this->coefficient_filter_r_channel1[12]  = 0x5c;
        this->coefficient_filter_r_channel1[13]  = 0xbf;  
        
        this->coefficient_filter_z_channel1[0]  = 0xaa;
        this->coefficient_filter_z_channel1[1]  = 0xa2;  
        this->coefficient_filter_z_channel1[2]  = 0xa3;  
        this->coefficient_filter_z_channel1[3]  = 0x4c;  
        this->coefficient_filter_z_channel1[4]  = 0xba;  
        this->coefficient_filter_z_channel1[5]  = 0xab;  
        this->coefficient_filter_z_channel1[6]  = 0xc3;  
        this->coefficient_filter_z_channel1[7]  = 0xae;  
        this->coefficient_filter_z_channel1[8]  = 0xab;  
        this->coefficient_filter_z_channel1[9]  = 0xa4;  
        this->coefficient_filter_z_channel1[10]  = 0x34;  
        this->coefficient_filter_z_channel1[11]  = 0xd1;  
        this->coefficient_filter_z_channel1[12]  = 0x66;  
        this->coefficient_filter_z_channel1[13]  = 0x9f;   

        this->coefficient_filter_b1_channel1[0]  = 0x22;   
        this->coefficient_filter_b1_channel1[1]  = 0x73;  
        this->coefficient_filter_b1_channel1[2]  = 0x34;
        this->coefficient_filter_b1_channel1[3]  = 0x2a;
        this->coefficient_filter_b1_channel1[4]  = 0x32;
        this->coefficient_filter_b1_channel1[5]  = 0xa5;
        this->coefficient_filter_b1_channel1[6]  = 0xd8;
        this->coefficient_filter_b1_channel1[7]  = 0xfe;
        this->coefficient_filter_b1_channel1[8]  = 0x87;
        this->coefficient_filter_b1_channel1[9]  = 0xd8;
        this->coefficient_filter_b1_channel1[10]  = 0x7f;
        this->coefficient_filter_b1_channel1[11]  = 0x87;
        this->coefficient_filter_b1_channel1[12]  = 0xa8;
        this->coefficient_filter_b1_channel1[13]  = 0xf0; 
  
		this->coefficient_filter_b2_channel1[0]  = 0x2e;
		this->coefficient_filter_b2_channel1[0]  = 0x01;

        //canal 2
		this->coefficient_filter_gr_channel2[0] = 0xaa;
		this->coefficient_filter_gr_channel2[1] = 0xa2;

		this->coefficient_filter_gx_channel2[0]  = 0x88;
		this->coefficient_filter_gx_channel2[0]  = 0x78;

 		this->coefficient_filter_r_channel2[0]  = 0x3a;
        this->coefficient_filter_r_channel2[1]  = 0xc0;
        this->coefficient_filter_r_channel2[2]  = 0xbb;
        this->coefficient_filter_r_channel2[3]  = 0xf0;
        this->coefficient_filter_r_channel2[4]  = 0xa2;
        this->coefficient_filter_r_channel2[5]  = 0x36;
        this->coefficient_filter_r_channel2[6]  = 0xaa;
        this->coefficient_filter_r_channel2[7]  = 0xcf;
        this->coefficient_filter_r_channel2[8]  = 0x2c;
        this->coefficient_filter_r_channel2[9]  = 0xad;
        this->coefficient_filter_r_channel2[10]  = 0xaa;
        this->coefficient_filter_r_channel2[11]  = 0xa5;
        this->coefficient_filter_r_channel2[12]  = 0xba;
        this->coefficient_filter_r_channel2[13]  = 0xae;  
        
        this->coefficient_filter_z_channel2[0]  = 0x24;
        this->coefficient_filter_z_channel2[1]  = 0xcc;  
        this->coefficient_filter_z_channel2[2]  = 0xb5;  
        this->coefficient_filter_z_channel2[3]  = 0x56;  
        this->coefficient_filter_z_channel2[4]  = 0xc3;  
        this->coefficient_filter_z_channel2[5]  = 0xa4;  
        this->coefficient_filter_z_channel2[6]  = 0x4b;  
        this->coefficient_filter_z_channel2[7]  = 0x26;  
        this->coefficient_filter_z_channel2[8]  = 0xfb;  
        this->coefficient_filter_z_channel2[9]  = 0xac;  
        this->coefficient_filter_z_channel2[10]  = 0x98;  
        this->coefficient_filter_z_channel2[11]  = 0x12;  
        this->coefficient_filter_z_channel2[12]  = 0x76;  
        this->coefficient_filter_z_channel2[13]  = 0x9f;   

        this->coefficient_filter_b1_channel2[0]  = 0xaa;   
        this->coefficient_filter_b1_channel2[1]  = 0x74;  
        this->coefficient_filter_b1_channel2[2]  = 0x25;
        this->coefficient_filter_b1_channel2[3]  = 0x3a;
        this->coefficient_filter_b1_channel2[4]  = 0x42;
        this->coefficient_filter_b1_channel2[5]  = 0x27;
        this->coefficient_filter_b1_channel2[6]  = 0xa8;
        this->coefficient_filter_b1_channel2[7]  = 0x7a;
        this->coefficient_filter_b1_channel2[8]  = 0x87;
        this->coefficient_filter_b1_channel2[9]  = 0x29;
        this->coefficient_filter_b1_channel2[10]  = 0x7a;
        this->coefficient_filter_b1_channel2[11]  = 0x87;
        this->coefficient_filter_b1_channel2[12]  = 0xa8;
        this->coefficient_filter_b1_channel2[13]  = 0x70; 
  
		this->coefficient_filter_b2_channel2[0]  = 0x2e;
		this->coefficient_filter_b2_channel2[0]  = 0x01;
    }

    bool Placaramal::is_cfail(alt_u8 analisar_byte){
       
        //printf("%02x\n",analisar_byte);
        return false;
    }

    void Placaramal::channel_ring(){
    //por enquanto está estático canal 1 
    int count = 0;   
        while (count<2) {
            this->write_codec(WRITE_CHANNEL_ENABLE,CHANNEL_1);            
            this->write_codec(WRITE_IO_REGISTER,RING_CHANNEL);
            usleep(1000000);
            this->write_codec(WRITE_IO_REGISTER,STOP_RING_CHANNEL);
            usleep(4000000);
            count ++;
        }      
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


    void Placaramal::clean_buffer(){
        for(int i=0;i<TAMANHOBUFFER;i++){
            this->tx_buf[i] = 0;
            this->rx_buf[i]= 0;
        }  
}


