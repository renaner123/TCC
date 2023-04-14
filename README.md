# Integração de ramais analógicos com FPGA utilizando processador softcore

Este *branch* possui alguns testes realizados para avaliar e entender o funcionamento de escrita e leitura das FIFOs quando controladas pelo Nios e quando controladas pela FPGA.


- [Integração de ramais analógicos com FPGA utilizando processador softcore](#integração-de-ramais-analógicos-com-fpga-utilizando-processador-softcore)
  - [FIFOs on Nios](#fifos-on-nios)
  - [FIFOs on Nios - Repassando pela FPGA](#fifos-on-nios---repassando-pela-fpga)
  - [FIFOs on Chip](#fifos-on-chip)
## FIFOs on Nios 

Para este teste, foram adicionados dois blocos IP FIFO, para serem controladas pelo Nios, através do *Platform Designer*, uma para FIFO de recepção e um para FIFO de transmissão, além dos blocos de memória, Nios, etc. As FIFOs são controladas por um PIO chamado TX_EN, no qual habilita e desabilita a escrita nas FIFOs. 

O arquivo utilizado para testar o comportamento, feito em `C`, e o arquivo `.qar` do projeto se encontram neste diretório [aqui](tests/FIFO/duas_fifo_nios/).

<details>
<summary>Resultado da simulação no Eclipse</summary>
<br>

  ![](tests/FIFO/duas_fifo_nios/double_fifo_nios.PNG)

</details>

## FIFOs on Nios - Repassando pela FPGA

 Esse outro teste, é semelhante ao FIFOs on Nios 1, mas com a adição de um bloco chamado `teste.vhd` que repassa os dados escritos na FIFO TX pelo Nios para a FIFO RX através da FPGA, que é posteriormente é lido pelo Nios.

 ![Diagrama de blocos do cenário de teste](tests/FIFO/fifo_tx_fifo_rx/teste-fifo.drawio.png)

O arquivo utilizado para testar o comportamento, feito em `C`, o arquivo `.qar` do projeto e o RTL do projeto se encontram neste diretório [aqui](tests/FIFO/fifo_tx_fifo_rx//).

<details>
<summary>Resultado da simulação no Eclipse</summary>
<br>

  ![](tests/FIFO/fifo_tx_fifo_rx/saida_software.PNG)

</details>



## FIFOs on Chip

Também foi gerado um exemplo utilizando duas FIFOs criadas em memória na FPGA, disponíveis no catálogo da Altera, com um bloco contador. O projeto, o RTL do projeto e os arquivos utilizados para simulação estão [aqui](tests/FIFO/dxa_fifo_catalogo/). O arquivo `C` para controle do Nios foi uma adaptação dos códigos utilizados Nos exemploes anteriores.

> Nesse caso, é possível encontrar algumas dificuldades em relação ao domínio de *clock* diferente existente entre a FPGA e o Nios.
