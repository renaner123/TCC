
#ifndef LE58QL021BVC_H
#define	LE58QL021BVC_H

#include "alt_types.h"
#include "altera_avalon_spi_regs.h"
#include "altera_avalon_spi.h"
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "io.h"
#include <stdio.h>
#include <unistd.h>// usleep

class Codec {  

  
public:
    // construtores    
    Codec();
  
    void periodico();
  
    void init();
  
    void tirarGancho(alt_u8 comando, int canal);
  
    void colocarGancho(alt_u8 comando, int canal);
  
    void verificarStatus(alt_u8 comando, int canal);
  
    void tocarRing(alt_u8 comando, int canal);
  
    void verificarAtendimento(alt_u8 comando, int canal);
  
    void tomDiscagem(alt_u8 comando, int canal);
  
    void atendimento(alt_u8 comando, int canal);
  
    void colocarGancho(alt_u8 comando, int canal);  
        
private:
    // atributos da classe: cada objeto desta classe
    alt_u8 tx_buf[4] = {0};
  	alt_u8 rx_buf[4] = {0};
  
};


class Slave {
    private:
        Codec *codec; 
        alt_u8 tx_buf[4] = {0};
        alt_u8 rx_buf[4] = {0};

    public:
        Slave();
  
    void respostaPeriodico();
  
    void respostaTirarGancho(alt_u8 comando);
  
    void respostaColocarGancho(alt_u8 comando);
  
    void respostaVerificarStatus(alt_u8 comando);
  
    void respostaTocarRing(alt_u8 comando);
  
    void respostaVerificarAtendimento(alt_u8 comando);
  
    void respostaTomDiscagem(alt_u8 comando);
  
    void respostaAtendimento(alt_u8 comando);
  
    void respostaColocarGancho(alt_u8 comando);                 

};


#endif	/* LE58QL021BVC_H */
