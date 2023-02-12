# Integração de ramais analógicos com FPGA utilizando processador softcore

Este repositório visa agrupar algumas informações referente ao projeto, [Integração de ramais analógicos com FPGA utilizando processador softcore](https://wiki.sj.ifsc.edu.br/images/0/04/TCC_64_RENAN_RODOLFO_DA_SILVA.pdf), que foi submetido à Coordenadoria do Curso de Engenharia de Telecomunicações do campus São José do Instituto Federal de Santa Catarina para a obtenção do diploma de Engenheiro de Telecomunicações.

## Objetivo do projeto

O objetivo do projeto foi integrar uma placa de ramal da central telefônica
Impacta 16, modelo 4990083, com um *kit* de desenvolvimento FPGA, modelo DE2-115,
para criar uma plataforma mínima para experimentações envolvendo canais digitais de
áudio e processadores sintetizados (softcores). Todas as informações, metodologias, testes e conclusões realizadas, podem ser encontradas na monografia disponível [aqui](https://wiki.sj.ifsc.edu.br/images/0/04/TCC_64_RENAN_RODOLFO_DA_SILVA.pdf).


## Projetos disnponíveis

### Gravar o projeto no *kit* de desenvolvimento FPGA DE2-115

A *branch* DE2-115 possui os arquivos

### Executar a simulação no ModelSim do projeto contido na *branch* projeto

1. Fazer o clone deste repositório e alterar para a *branch* `projeto` da seguinte maneira:
 
```
git clone https://github.com/renaner123/TCC.git
cd TCC/
git checkout projeto
```
**Obs.:** Caso não tenha o git instalado, é possível fazer o download do repositório em `Code -> Download Zip`.

2. Abrir o projeto contido no arquivo `tcc.qar` no Quartus Prime em `File -> Open Project`
3. Alterar o caminho `/path/TCC/tcc_restored` contido no *Destination folder* , deixando a pasta raíz do projeto `/path/TCC/`
4. Fazer a compilação completa do projeto (*Compile Design*)
5. Abrir o ModelSim em `Tools -> Run Simulation Tool -> RTL Simulation`
6. Executar o teste bench contido no arquivo `wave.do` usando o comando `do wave.do` na janela *Transcript*.

Na simulação do arquivo `wave.do`, o sinal `DXA_wire` está representado a entrada `DXA` e a porta `TDM0` está represetando a saída `DRA` da placa ramal.



**Obs.:** Também é possível executar o teste bench contido no arquivo `wave_debug.do`, o qual possui todos os sinais utilizados para chegar no resultado apresentado no `wave.do`.