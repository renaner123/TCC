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
#define CHANNEL_1__OUT_HOOK 0xab
#define CHANNEL_2__OUT_HOOK 0xae
#define CHANNEL_1_2__OUT_HOOK 0xaf

class Placaramal{

  
	public:
		// construtores
      
		Placaramal();

		~Placaramal() {};

		void periodico(alt_u8 comando_codec);

		void init();

		void verificarAtendimento(alt_u8 canal);

		void limparBuffer();

		void definirMasterClock();

		void definirCoefienctes();

		void configurarRegistradoresCanais();

		void configurarDirecaoSlic();

		void comandoAtivarCodec();

		void configurarDebounceTime();

		void configurarTimeSlot();

		void configurarTimeRealData();
    
		void configurarInterruptMask();

        //faz um canal ringar, receber a tensão de ring fornecida pela placa fonte
		void ringarCanal();

        //Envia o comando para fazer hardware reset da codec
		void hardwareReset();

        //envia um comando de escrita e o valor a ser escrito para o codec
		void writeCodec(alt_u8 comando_codec, alt_u8 valor_comando);

        //envia algum comando de ativação ao codec, que não precisa de um valor
		void writeCodec(alt_u8 comando_codec);

        //retorna uma resposta do codec
		alt_u8 readCodec(alt_u8 comando_codec);

        //retorna true se o canal estiver fora do gancho
        bool channelIsOutHook(alt_u8 channel);

        //retorna true se o canal atendeu a chamada(ring)
        bool getAtendimento(void);
	    bool setAtendimento(bool atendimento);

        
	private:
		// atributos da classe: cada objeto desta classe
        bool Atendimento;
		alt_u8 tx_buf[8];
		alt_u8 rx_buf[8];
  
};



