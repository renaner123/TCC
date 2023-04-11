## Trabalho de conclusão de curso

### Executar o projeto no *kit* FPGA DE2-115

Neste *branch* existe um arquivo chamado `tcc.qar`, o qual pode ser utilizado para abrir o projeto no software Quartus Prime (foi utilizado a versão standard 20.1). No repositório também existe o diretório `tcc_restored/software/hotline` que possui as implementações em C++ criadas para fazer o controle da placa de ramal por meio do processador softcore Nios II. Para ser possível testar as facilidades implementadas, é necessário possuir o cenário apresentado na seção [Setup do sistema](#setup-do-sistema). Os seguintes passos descrevem as etapas necessáras para gravar o projeto no *kit*.

1. Fazer o clone deste repositório e alterar para a *branch* `de2-115` da seguinte maneira:

```
git clone https://github.com/renaner123/TCC.git
cd TCC/
git checkout de2-115
```
> Caso não tenha o git instalado, é possível fazer o download do repositório em `Code -> Download Zip`
> 
2. Abrir o projeto contido no arquivo `tcc.qar` no Quartus Prime em `File -> Open Project`
3. Fazer a compilação completa do projeto (*Compile Design*)
4. Fazer a gravação do VHDL no *kit* em `Tools -> Programmer`

> Quando for abrir o projeto .qar, usar a pasta raiz e não o tcc_restored, assim o .gitignore irá funcionar
