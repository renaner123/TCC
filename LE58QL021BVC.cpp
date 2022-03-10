#include "libs/LE58QL021BVC.h"

Codec ::Codec () {

}

void Codec::init(){ 
   
}

void Codec::periodico(){ 
   
}


void Codec::tirarGancho(alt_u8 comando, int canal) {
 
}


void Codec::colocarGancho(alt_u8 comando, int canal) { 
   

}

void Codec::verificarStatus(alt_u8 comando, int canal){ 
   
}


void Codec::tocarRing(alt_u8 comando, int canal) {
 
}


void Codec::verificarAtendimento(alt_u8 comando, int canal) { 

}


void Codec::tomDiscagem(alt_u8 comando, int canal){ 
   
}


void Codec::atendimento(alt_u8 comando, int canal) {
 
}


Slave ::Slave () {

}

 void Slave::respostaPeriodico(){};

 void Slave::respostaTirarGancho(alt_u8 comando){};

 void Slave::respostaColocarGancho(alt_u8 comando){};

 void Slave::respostaVerificarStatus(alt_u8 comando){};

 void Slave::respostaTocarRing(alt_u8 comando){};

 void Slave::respostaVerificarAtendimento(alt_u8 comando){};

 void Slave::respostaTomDiscagem(alt_u8 comando){};

 void Slave::respostaAtendimento(alt_u8 comando){};
