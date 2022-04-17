#include "placaramal.h"

Placaramal::Placaramal() {

}
/*
int alt_avalon_spi_command(alt_u32 base, alt_u32 slave,
                           alt_u32 write_length, const alt_u8 * write_data,
                           alt_u32 read_length, alt_u8 * read_data,
                           alt_u32 flags);
*/

void Placaramal::init(){ 
    
    this->definir_master_clock();
    

    this->is_cfail(this->tx_buf[0]);

/*     IOWR_ALTERA_AVALON_PIO_DATA(TX_EN_BASE, 1);
    alt_avalon_spi_command(SPI_MASTER_BASE, 0, TAMANHOBUFFER, this->tx_buf, 0, this->rx_buf, 0);
    
    this->limparbuffer(); */
}


    void Placaramal::definir_master_clock(){
        this->tx_buf[0] = 0x4A;
        //46/47h
        //D7 1 ou 0                              D0  
        //INTM CHP SMODE CMODE CSEL3 CSEL2 CSEL1 CSEL0 
        //46h -> 0  0  1  1  1  0  1  0  (3ah)  P/ 8.192 MHz,  TTL-compatible, Signaling on PCM highway, PCLK
        //CFAIL tem que ir pra 0 em 400us. Loop para verificar o bit 2(D5) da resposta 
        //55h <- 0  0  0* 0  0  0  0  1  (01h)  |00h ou 01h deve receber isso.
    }

    void Placaramal::definir_coefienctes(){
        //60/61h
        //definir coeficientes padroes 
        // Compressed/Linear A/µ EGR(–8.984 db) EGX(6 db) EX(1 Hz) ER(1 Hz) EZ(0) EB(0)
        // 60-> 0  0  0  0  0  0  0  0  (00h)   P/ Código compactado usando A-law usando coeficientes padrões      
        // se usar 61h deve receber 00h por padrão.
    }

    void Placaramal::configurar_registradores_canais(){
        //4A/4Bh
        //bit 0(EC1) for channel 1, bit 1(EC2) for channel 2, bit 2(EC3) for channel 3, and bit 3(EC4) for channel 4.
        //RSVD RBE VMODE* LPM EC4 EC3 EC2 EC1
        //4A -> 0  0  0  0  0  0  1  1  (03h)   P/ ativar canal 1 e 2 para receber comandos 
                                              //e * é VOUT=VREF through a resistor when channel is deactivated
    }

    void Placaramal::configurar_direcao_slic(){
        //54/55h
        //The output latches can be written with Command 52h;
        //The inputs can be read with Command 53h
        //C[3-5] não são usados 
        //CD1 é entrada para sensor de gancho
        //CD2 é saída para gerar ring
        //RSVD CSTAT CFAIL IOD5(C5) IOD4(C4) IOD3(C3) IOD2(CD2) IOD1(CD1) 
        //54 -> 0  0  0  0  0  0  1  0   (02h)        P/Deixar        
        
    }  
    void Placaramal::comando_ativar_codec(){
        /*This command places the device in the Active state and sets CSTAT = 1. 
        No valid PCM data is transmitted until after the third FS pulse is received 
        following the execution of the Activate command*/
        // -> 0Eh
        // Verificar se o CSTAT foi para 1 com 55h, verificar o bit 'x'  0x00 0000  
    }

    bool Placaramal::is_cfail(alt_u8 analisar_byte){
       
        //printf("%02x\n",analisar_byte);
        return false;
    }

void Placaramal::limparbuffer(){
    for(int i=0;i<TAMANHOBUFFER;i++){
        this->tx_buf[i] = {};
        this->rx_buf[i] = {};
    }  
}


