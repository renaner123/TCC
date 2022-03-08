
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
  
    void Periodico();
  
    void TirarGancho(int canal);
  
    void ColocarGancho(int canal);
  
    void VerificarStatus(int canal);
  
    void TocarRing(int canal);
  
    void VerificarAtendimento(int canal);
  
    void TomDiscagem(int canal);
  
    void Atendimento(int canal);
  
    void ColocarGancho(int canal);  
        
private:
    // atributos da classe: cada objeto desta classe
    alt_u8 tx_buf[4] = {0};
  	alt_u8 rx_buf[4] = {0};
  
};


class Slave {
    private:
        Codec *codec; 

    public:
        Slave();
  
    void RespostaPeriodico();
  
    void RespostaTirarGancho(int canal);
  
    void RespostaColocarGancho(int canal);
  
    void RespostaVerificarStatus(int canal);
  
    void RespostaTocarRing(int canal);
  
    void RespostaVerificarAtendimento(int canal);
  
    void RespostaTomDiscagem(int canal);
  
    void RespostaAtendimento(int canal);
  
    void RespostaColocarGancho(int canal);                 

};


#endif	/* LE58QL021BVC_H */
