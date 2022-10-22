#include "alt_types.h"
#include "altera_avalon_spi_regs.h"
#include "altera_avalon_spi.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "io.h"
#include <stdio.h>
#include <unistd.h>// usleep

//Comandos utilizados para configurar a codec				
#define WRITE_CHIP_CONFIGURATION_REGISTER 0X46              
#define READ_CHIP_CONFIGURATION_REGISTER 0X47              
#define WRITE_DEBOUNCE_TIME_REGISTER 0xC8                  
#define WRITE_CHANNEL_ENABLE 0x4A                           
#define WRITE_SET_TIMESLOT 0X44                            
#define WRITE_INTERRUPT_MASK_REGISTER 0X6C                  
#define WRITE_REAL_TIME_DATA_REGISTER 0X4D                 
#define WRITE_REAL_TIME_DATA_REGISTER_CLEAR_INTERRUPT 0X4F  
#define WRITE_OPERATING_FUNCTIONS 0X60                     
#define WRITE_SLIC_DIRECTION_STATUS_BITS 0X54              
#define READ_SLIC_DIRECTION_STATUS_BITS 0X55               
#define ACTIVATE_CODEC 0x0E                                 
#define WRITE_IO_REGISTER 0X52                             
#define READ_IO_REGISTER 0X53                              
#define RING_CHANNEL 0X1C                                   
#define STOP_RING_CHANNEL 0X1E                              
#define HARDWARE_RESET 0X04
#define OPERATING_CONDITIONS 0x70
#define AISN_ANALOG_GAINS 0x50
#define GR_FILTER_COEFFICIENTS 0x82
#define GX_FILTER_COEFFICIENTS 0x80
#define R_FILTER_COEFFICIENTS 0x8A
#define Z_FILTER_COEFFICIENTS 0x84
#define B1_FILTER_COEFFICIENTS 0x86
#define B2_FILTER_COEFFICIENTS 0x96


//VALORES USADOS NAS CONFIGURACOES
#define MASTER_CLOCK 0X92     // 2.048 Mhz - PCLK  - Open Drain        
#define DEBOUNCE_TIME 0X3C                                  
#define TIME_SLOT 0X40        //00 sincronizado com borda negativa do PCLK, 40 borda positiva
#define INTERRUPT_MASK 0XAA                                 
#define TIME_REAL_DATA 0XAA                                 
#define DEFAULT_COEFFICIENT 0X00                            
#define DIRECTION_SLIC_CD1_CD2 0X02 // 02 CD1 INPUT - CD2 OUTPUT           
#define TAMANHOBUFFER 8
#define CHANNEL_1 0x01
#define CHANNEL_2 0x02


class Placaramal{

  
	public:
		// construtores
		Placaramal();

		~Placaramal() {};

		void periodico();

		void init();
		void init_channel1();
		void init_channel2();

		void take_hook(int canal);

		void put_hook();

		void veirify_attendance();

		void dial_tone();

		void attendance();

		void clean_buffer();

		void set_master_clock();

		void set_coefficients(alt_u8 operation);

		void channel_enable(alt_u8 channell);

		void set_slic_direction(alt_u8 direction);

		void activate_codec();

		void set_debounce_time();

		void set_time_slot();

		void set_time_real_data();

		void set_interrupt_mask(alt_u8 mask);

		void condicao_operacao();

		void filter_coefficients_gr(alt_u8 coefficient_gr[2]);
		void filter_coefficients_gx(alt_u8 coefficient_gx[2]);
		void filter_coefficients_r(alt_u8 coefficient_r[14]);
		void filter_coefficients_z(alt_u8 coefficient_z[15]);
		void filter_coefficients_b1(alt_u8 coefficient_b1[14]);
		void filter_coefficients_b2(alt_u8 coefficient_b2[2]);

		void channel_ring();

		void hardware_reset();

		void write_codec(alt_u8 comando_codec, alt_u8 valor_comando);

		void write_codec(alt_u8 comando_codec);

		alt_u8 read_codec(alt_u8 comando_codec);

		bool is_cfail(alt_u8 analisar_byte);
        
	private:
		// atributos da classe: cada objeto desta classe
		alt_u8 tx_buf[8];
		alt_u8 rx_buf[8];
		alt_u8 coefficient_filter_gr_channel1[2]  = {0xa2, 0xa0};
		alt_u8 coefficient_filter_gx_channel1[2]  = {0x88, 0x78};
		alt_u8 coefficient_filter_r_channel1[14]  = {0x3a, 0xc0, 0x2b, 0x70, 0x23, 0xbe, 0x2d, 0x36, 0xab, 0xad, 0xab, 0xb6, 0x5c, 0xbf};
        alt_u8 coefficient_filter_z_channel1[15]  = {0xaa, 0xa2, 0xa3, 0x4c, 0xba, 0xab, 0xc3, 0xae, 0xab, 0xa4, 0x34, 0xd1, 0x66, 0x9f, 0x01};
        alt_u8 coefficient_filter_b1_channel1[14] = {0x22, 0x73, 0x34, 0x2a, 0x32, 0xa5, 0xd8, 0xfe, 0x87, 0xd8, 0x7f, 0x87, 0xa8, 0xf0};
        alt_u8 coefficient_filter_b2_channel1[2]  = {0x2e, 0x01};  

		alt_u8 coefficient_filter_gr_channel2[2]  = {0xAA, 0xA2};
		alt_u8 coefficient_filter_gx_channel2[2]  = {0x88, 0x78};
		alt_u8 coefficient_filter_r_channel2[14]  = {0x3A, 0xC0, 0xBB, 0xF0, 0xA2, 0x36, 0xAA, 0xCF, 0x2C, 0xAD, 0xAA, 0xA5, 0xBA, 0xAE};
        alt_u8 coefficient_filter_z_channel2[15]  = {0x24, 0xCC, 0xB5, 0x56, 0xC3, 0xA4, 0x4B, 0x26, 0xFB, 0xAC, 0x98, 0x12, 0x76, 0x9F, 0x01};
        alt_u8 coefficient_filter_b1_channel2[14] = {0xAA, 0x74, 0x25, 0x3A, 0x42, 0x27, 0xA8, 0x7A, 0x87, 0x29, 0x7A, 0x87, 0xA8, 0x70};
        alt_u8 coefficient_filter_b2_channel2[2]  = {0x2e, 0x01};  		
};



