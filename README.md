## Trabalho de conclusão de curso
### Executar a simulação do projeto

Neste *branch* existe dois arquivos de *testbench* que podem ser simulados através da ferramenta ModelSim, integrada ao Quartus, para fazer a análise do comportamento dos blocos utilizados na implementação do projeto. Para isso, os seguintes passos devem ser executados:

1. Fazer o clone deste repositório e alterar para a *branch* `projeto` da seguinte maneira:
 
```
git clone https://github.com/renaner123/TCC.git
cd TCC/
git checkout projeto
```
> Caso não tenha o git instalado, é possível fazer o download do repositório em `Code -> Download Zip`

2. Abrir o projeto contido no arquivo `tcc.qar` no Quartus Prime em `File -> Open Project`
3. Alterar o caminho `/path/TCC/tcc_restored` contido no *Destination folder* , deixando a pasta raíz do projeto `/path/TCC/`
4. Fazer a compilação completa do projeto (*Compile Design*)
5. Abrir o ModelSim em `Tools -> Run Simulation Tool -> RTL Simulation`
6. Executar o teste bench contido no arquivo `wave.do` usando o comando `do wave.do` na janela *Transcript*.

Na simulação do arquivo `wave.do`, o sinal `DXA_wire` está representado a entrada `DXA` e a porta `TDM0` está represetando a saída `DRA` da placa ramal.

> Também é possível executar o teste bench contido no arquivo `wave_debug.do`, o qual possui todos os sinais utilizados para chegar no resultado apresentado no `wave.do`.

> Quando for abrir o projeto .qar, usar a pasta raiz e não o tcc_restored, assim o .gitignore irá funcionar
