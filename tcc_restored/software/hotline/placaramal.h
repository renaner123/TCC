#include "alt_types.h"
#include "altera_avalon_spi_regs.h"
#include "altera_avalon_spi.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "io.h"
#include <stdio.h>
#include <unistd.h>// usleep

//Comandos utilizados para configurar a codec
#define WRITE_CHIP_CONFIGURATION_REGISTER 0X46              //         |01000110
#define READ_CHIP_CONFIGURATION_REGISTER 0X47               //         |01000111
#define WRITE_DEBOUNCE_TIME_REGISTER 0xC8                   //         |11001000
#define WRITE_CHANNEL_ENABLE 0x4A                           //         |01001010
#define WRITE_SET_TIMESLOT 0X44                             //         |01000100
#define WRITE_INTERRUPT_MASK_REGISTER 0X6C                  //         |01101100
#define WRITE_REAL_TIME_DATA_REGISTER 0X4D                  //         |01001101
#define WRITE_REAL_TIME_DATA_REGISTER_CLEAR_INTERRUPT 0X4F  //         |01001111
#define WRITE_OPERATING_FUNCTIONS 0X60                      //         |01100000
#define WRITE_SLIC_DIRECTION_STATUS_BITS 0X54               //         |01010100
#define READ_SLIC_DIRECTION_STATUS_BITS 0X55                //         |01010101
#define ACTIVATE_CODEC 0x0E                                 //         |00001110
#define WRITE_IO_REGISTER 0X52                              //         |01010010
#define READ_IO_REGISTER 0X53                               //         |01010011
#define RING_CHANNEL 0X1C                                   //         |00011100
#define STOP_RING_CHANNEL 0X1E                              //         |00011110
#define HARDWARE_RESET 0X04
#define TRANSMIT_TIME_SLOT 0x40
#define RECEIVE_TIME_SLOT 0x42
#define HARDWARE_RESET 0X04
#define OPERATING_CONDITIONS 0x70
#define AISN_ANALOG_GAINS 0x50
#define GR_FILTER_COEFFICIENTS 0x82
#define GX_FILTER_COEFFICIENTS 0x80
#define R_FILTER_COEFFICIENTS 0x8A
#define Z_FILTER_COEFFICIENTS 0x84
#define B1_FILTER_COEFFICIENTS 0x86
#define B2_FILTER_COEFFICIENTS 0x96
#define TRANSMIT_TIME_SLOT 0x40
#define RECEIVE_TIME_SLOT 0x42

//VALORES USADOS NAS CONFIGURACOES
#define MASTER_CLOCK 0X12     //2.048 Mhz - PCLK            //         |00010010
#define DEBOUNCE_TIME 0X3C                                  //         |00111100
#define TIME_SLOT 0X00        //FS sincronizado com borda negativa do PCLK
#define INTERRUPT_MASK 0XAA                                 //         |10101010
#define TIME_REAL_DATA 0XAA                                 //         |10101010
#define DEFAULT_COEFFICIENT 0X00
#define DIRECTION_SLIC_CD1_CD2 0X02 //CD1 INPUT - CD2 OUTPUT           |00000010
#define TAMANHOBUFFER 8
#define CHANNEL_1 0x01
#define CHANNEL_2 0x02

class Placaramal{


	public:
		// construtores
		Placaramal();

		~Placaramal() {};

		void periodical();

		void init();

		void init_channel1();

		void init_channel2();

		void take_hook(int canal);

		void put_hook();

		void veirify_attendance();

		void dial_tone();

		void attendance();

		void clean_buffer();

		void set_master_clock(alt_u8 clock);

		void set_coefficients(alt_u8 operation);

		void channel_enable(alt_u8 channell);

		void set_slic_direction(alt_u8 direction);

		void set_slic_direction();

		void activate_codec();

		void operating_conditions();

		void set_debounce_time(alt_u8 debounce);

		void set_time_slot(alt_u8 time_slot);

		void set_time_real_data();

		void set_interrupt_mask(alt_u8 mask);


		void transmit_time_slot(alt_u8 timeslot);

		void receive_time_slot(alt_u8 timeslot);

		void channel_ring();

		void hardware_reset();

		void write_codec(alt_u8 comando_codec, alt_u8 valor_comando);

		void write_codec(alt_u8 comando_codec);

		void monitore_channel();

		alt_u8 read_codec(alt_u8 comando_codec);

		bool is_cfail(alt_u8 analisar_byte);



	private:
		// atributos da classe: cada objeto desta classe
		alt_u8 tx_buf[8];
		alt_u8 rx_buf[8];

		alt_u8 coefficient_filter_gr_channel1[2] ;
		alt_u8 coefficient_filter_gx_channel1[2] ;
		alt_u8 coefficient_filter_r_channel1[14]  ;
        alt_u8 coefficient_filter_z_channel1[15] ;
        alt_u8 coefficient_filter_b1_channel1[14] ;
        alt_u8 coefficient_filter_b2_channel1[2]  ;

		alt_u8 coefficient_filter_gr_channel2[2] ;
		alt_u8 coefficient_filter_gx_channel2[2] ;
		alt_u8 coefficient_filter_r_channel2[14] ;
        alt_u8 coefficient_filter_z_channel2[15] ;
        alt_u8 coefficient_filter_b1_channel2[14];
        alt_u8 coefficient_filter_b2_channel2[2] ;
};


