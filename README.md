# TP2-cg
Sistema solar

Desenvolvido por: Alex Meireles Santos Almeida e Darmes Araujo Dias.

1) Para realizar a instalação das bibliotecas necessárias, devemos acessar o Terminal do Linux. Para isso, pressione ctrl + alt + t ou procure por Terminal no Menu Linux.

2) Após abrir o Terminal, precisamos verificar se todas as informações dos pacotes de fontes já instaladas estão configuradas na versão mais recente, caso não esteja, será feita a atualização. Para isso, execute o comando no terminal:
sudo apt-get update

Coloque sua senha para fazer a verificação e aguarde a finalização.

3) Após seu sistema concluir as atualizações, iremos instalar alguns mecanismos necessários para desenvolvermos alguns processos, pelo comando via terminal:

sudo apt-get install build-essential

No meu caso, todas ferramentas já estão instaladas. Entretanto, caso apareça uma mensagem perguntando se deseja continuar, pressione s e logo em seguida enter.

4) A partir de agora iremos instalar todas as bibliotecas, você deve criar um diretório, e nesse diretório criar um arquivo de texto, nele você
deve inserir isso:
#!/bin/bash 
#avisando o terminal que o nosso script está escrito em bash

FILE="/tmp/out.$$"

#Utilizar o modo administrador para rodar o script
if [[ "$EUID" -ne "0" ]]; then
    echo "Esse script deve ser executado em modo administrador, portanto, "#sudo su" em seu terminal linux, e depois deve digitar sua senha" !>&2
    exit 1
fi
#comandos para instalar as bibliotecas que serão utilizadas
apt-get update -y
apt-get install freeglut3 -y
apt-get install freeglut3-dev -y
apt-get install g++ cmake -y
apt-get install g++ -y
apt-get install binutils-gold -y
apt-get install libglew-dev -y
apt-get install libglew1.5-dev libglm-dev -y
apt-get install libsoil-dev -y
apt-get install mesa-common-dev -y
glxinfo | grep OpenGl

Após copiar e colar, você deve salvar com extensão .sh.

5) Após salvar, você deve entrar no terminal e entrar no diretório que foi salvo, e depois deve escreve sudo su(entrando no modo administrador) e
colocar sua senha, depois escreva chmod +x nomedoarquivo.sh(tornando o arquivo executável).

6) Depois disso é só rodar com ./nomedoarquivo.sh 

7) Todas bibliotecas instaladas! Para jogar baixe o zip do repositório ou faça um git-clone para seu desktop. Se tiver baixado o zip primeiramente descomprima os arquivos, depois acesse a pasta da última versão com o comando:
cd 'pasta-onde-foi-clonado-ou-baixado'/TP2-cg

e depois dê o comando:

make run

Instruções do programa:

Setas para direita e esquerda movimentam a camera em torno do sol para direita e esquerda, respectivamente, fazendo com que a velocidade de rotação do sistema aumente ou diminua.
Setas para cima e para baixo movimentam a camera em torno do sol para cima e para baixo, respectivamente.
A tecla "l" desliga/liga a luz do sistema solar.
As teclas left mouse e right mouse, dão zoom e tiram zoom, respectivamente.
A tecla "Esc" sai do programa.
A tecla "o" ativa o modo de órbitas visíveis.
A tecla "p" pausa o sistema solar.
As teclas "F1" e "F2" fazem a posição do observador ir para frente e para trás, podendo se movimentar entre os planetas.
A tecla "c" alterna a câmera entre uma visão superior e uma visão lateral.

Itens adicionais implementados:
Reshape, satélites naturais, modo de órbitas visíveis e funcionalidade das teclas "F1" e "F2".
