# MINI MANUAL #

**CLASSE IMAGEM**

A classe imagem é a ferramenta usada para carregar e desenhar arquivos de imagens
através da LibEGL.

Primeiro passo a ser dado para se usar a classe é criar um objeto desta classe como
visto abaixo:
```
imagem sprites;
```
Deste modo criamos o objeto sprites derivado da classe imagem.

O próximo passo é carregar um arquivo de imagem no objeto imagem seguindo o exemplo:
```
sprites.carregar("caminho do arquivo");
```
Se desejar criar uma animação basta carregar as frames uma após a outra:
```
sprites.carregar("caminho da frame1");
sprites.carregar("caminho da frame2");
sprites.carregar("caminho da frame3");
```
**OBS.: Aconselho a usar todas as frames do mesmo tamanho para evitar problemas de colisão.**

Podemos ainda setar quantas a velocidade das frames:
```
sprites.setar_tempo_animacao(valor de velocidade dos frames);
```
Agora que carregamos o objeto com a imagem devemos desenhá-lo:

**Obs.: Criar o objeto e carregá-lo são declarações feitas fora do while (loop) principal.**
```
sprites.desenha(posição no eixo X, posição no eixo Y);
```
Entre parenteses ficam as posições nos eixos X e Y da tela aonde o objeto será desenhado,
esta declaração deve ser feita dentro do while (loop) principal.

**DESENHANDO ESPELHADO:**

Para desenhar de forma espelhada devemos usar o metodo desenha\_espelhado da seguinte forma:
```
sprites.desenha_sepelhado(posição eixo X, posição eixo Y, espelhamento na horizontal está 
setado automaticamente para espelhar na vertical coloque false aqui e true no vertical, 
espelhamento na vertical setado como false para espelhar na vertical coloque false na 
horizontal e true aqui);
```
**COLISÃO:**

Na EGL pode-se setar colisão entre duas imagens, para tanto deve-se setar com o próximo metodo:
```
sprites.colide(posX, posY, sprites.getResX(), sprites.getResY(), pos2X, pos2Y, image2.getResX(), image2.getResY(), image2);
```
Aonde posX é a posição da imagem principal no eixo X e posY é a posição da imagem no eixo Y, getResX e getResY setam altura e largura da imagem, é aconselhavel que se a imagem for uma animação todas as frames tenham o mesmo tamanho, se não podem haver problemas, pos2X e pos2Y são as posições da segunda imagem nas coordenadas X e Y, image2.getResX() e getResY() setam altura e largura da imagem2 e imagem2 indica qual é o segundo objeto do efeito de colisão.

**CLASSE SOM:**

Para criarmos um som em EGL se faz nescessário que ele seja PCM e envelopado em WAVE.

Como na classe imagem precisamos gerar um objeto de som e carregar um arquivo de som neste objeto.
```
som wave; // Criei um objeto de som chamado wave.

wave.carregar("caminho do arquivo de som");
```
Podemos então ajustar o som em seu volume, pan, frequencia e quantidade de repetições.
```
wave.ajustar(volume, pan, frequencia, loop);//Pan, frequencia e loop já estão previamente ajustados.
```
Então agora é só tocarmos o som.
```
wave.tocar(repetições); // Repetições já esta setado em 0;
```
**OBS.: Aconselho a se for musica colocar para iniciar antes do loop principal, pois senão a musica iniciará diversas vezes causando problemas de som.**

**OBS 2.: Se for utilizar o tocar dentro do loop para efeitos sonoros coloque este efeito dentro de um evento.**
Exemplo:
```
if(evento == 0)
{
	wave.tocar();
	evento = 100;
}
else
	evento --;
```
> Assim o som apenas tocará quando evento for 0, se não irá diminuir evento até que este chegue a 0;

**CLASSE FONTE:**

Pode-se carregar na lib EGL certos tipos de fontes, estes são imagens de letras que a EGL reconhece como fonte se forem carregadas em um objeto da classe fonte. Existem exemplos de arquivos de fonte na pasta egl/fonts, estes arquivos contem a formatação exata de uma fonte EGL e deve-se seguir o mesmo formato para que se use outras fontes em conjunto com a EGL.

Primeiro criamos um objeto de fonte e depois carregamos este objeto.
```
fonte arial;

arial.carregar("font.bmp");
```
Para se desenhar um texto na tela usando este objeto deve-se fazer da seguinte maneira:
```
arial.desenha_texto("texto que deve aparecer na tela", eixo X, eixo Y);
```

Abaixo temos um exemplo de código:
```
#include <iostream>
#include <string>
#include <sstream>
#include "engcomp_glib.h" // incluindo a lib da EGL no projeto.

using namespace std;

int main(void)
{
	egl_inicializar(1024,768);//iniciando a EGL com resolução de 1024 por 768.
	
	imagem sprite;//criando o objeto de imagem.
	sprite.carregar("guerreiro1.png");//Se o arquivo estiver na mesma pasta do projeto não é nescessário colocar 
									 //o restante do caminho, apenas o noome basta.
	sprite.carregar("guerreiro2.png");
	sprite.carregar("guerreiro3.png");
	sprite.carregar("guerreiro4.png");//Todas as frames da animação.
	sprite.setar_tempo_animacao(10); // A velocidade das frames será de 10.
	
	som grito;
	grito.carregar("grito.wav");//Aqui tambem se o arquivo estiver na mesma pasta do projeto não se faz 
								 //nescessário passar toda a localização.
	grito.ajustar(12,125,1000,0);
	grito.tocar();//O som irá tocar sem Loop.

	fonte arial;
	arial.carregar("fonte.bmp");//O mesmo que em imagem e som, o arquivo na pasta do projeto.

	while(!key[KEY_ESC])//Loop até que se pressione ESC.
	{
		arial.desenha_texto("Aprendendo Lib EGL para criacao de jogos", 400, 400); //Aqui estamos escrevendo com fontes desenhadas na tela.
		sprite.desenha(250,100);//A animação será desenhada nas coordenadas 250 do eixo X e 100 do eixo Y.
		
		egl_desenha_frame();
	}

	egl_finalizar();

	return 0;
}
END_OF_MAIN();//Na EGL se faz nescessário o END OF MAIN, sem ele o programa não funciona.
```
Qualquer Duvida escreva um e-mail para jonesvg@gmail.com