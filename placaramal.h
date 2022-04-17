#ifndef PLACARAMAL_H
#define	PLACARAMAL_H

#define INTERRUPCAO 0x4F
#define TAMANHOBUFFER 8
#define ENDERECOCANAL1 0xAB
#define ENDERECOCANAL2 0XAE
#define ENDERECOCANAL3 0XBA
#define ENDERECOCANAL4 0XEA
#define COMANDOREPOUSO 0XAA
#define COMANDOSTANDBY 0X02
#define FORADOGANCHO 0X02
#define PERIODICO 0X55
#define LENDOESCREVENDO 0x4A
#define CHAMANDO 0X42
#define ATENDENDO 0XA7

#include "libs/alt_types.h"
#include "libs/altera_avalon_spi_regs.h"
#include "libs/altera_avalon_spi.h"
#include "libs/system.h"
#include "libs/altera_avalon_pio_regs.h"
#include "io.h"
#include <stdio.h>
#include <unistd.h>// usleep

class Placaramal {  

  
public:
    // construtores    
    Placaramal();

    ~Placaramal() {};
  
    void periodico();
  
    void init();
  
    void tirarGancho(int canal);
  
    void colocarGancho();
    
    void tocarRing();
  
    void verificarAtendimento();
  
    void tomDiscagem();
  
    void atendimento();

    void limparbuffer();

    void definir_master_clock();

    void definir_coefienctes();

    void configurar_registradores_canais();
    
    void configurar_direcao_slic();
  
    void comando_ativar_codec();

    bool is_cfail(alt_u8 analisar_byte);


        
private:
    // atributos da classe: cada objeto desta classe
    alt_u8 tx_buf[8] = {0};
  	alt_u8 rx_buf[8] = {0};
  
};




#endif	/* PLACARAMAL_H */
