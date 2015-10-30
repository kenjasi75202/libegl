# TUTORIAL FAZENDO UM PERSONAGEM MOVER-SE PELO TECLADO COM LIBEGL: #

Bom vamos montar um personagem que deve se mover pelas setas do teclado
gerando animações diferentes para cada tecla.

O primeiro a se fazer é abrir um esqueleto de base da libegl.

Salve como e nomeie ele com o nome de sua preferência.

**OBS.: NÃO irei usar ORIENTAÇÃO A OBJETOS por se tratar de TUTORIAL PARA INICIANTES.**

teremos então o seguinte código:
```
#include <iostream>
#include <string>
#include <sstream>
#include "engcomp_glib.h"

using namespace std;

int main(void)
{
	egl_inicializar(1024,768);
	
	while(!key[KEY_ESC])
	{
	


		egl_desenha_frame();
	}

	egl_finalizar();

	return 0;
}
END_OF_MAIN();
```
Devemos então criar nossos objetos de imagem, que serão heroi\_esquerda, heroi\_direita, heroi\_abaixa, heroi\_cima, parado\_direita, parado\_esquerda.
Depois de criar os objetos temos de carregá-los com nossas imagens.

Assim nosso código muda para:
```
#include <iostream>
#include <string>
#include <sstream>
#include "engcomp_glib.h"

using namespace std;

int main(void)
{
	egl_inicializar(1024,768);
	
	imagem heroi_esquerda;
	imagem heroi_direita;
	imagem heroi_abaixa;
	imagem heroi_cima;
	imagem parado_direita;
	imagem parado_esquerda;
	
	heroi_esquerda.carregar("esquerda1.png");
	heroi_esquerda.carregar("esquerda2.png");
	heroi_esquerda.carregar("esquerda3.png");
	
	heroi_direita.carregar("direita1.png");
	heroi_direita.carregar("direita2.png");
	heroi_direita.carregar("direita3.png");
	
	heroi_abaixa.carregar("abaixa1.png");
	
	heroi_cima.carregar("cima.png");
	
	parado_direita.desenha("parado_direita.png");
	
	parado_esquerda.desenha("parado_esquerda.png");
	
	while(!key[KEY_ESC])
	{
	


		egl_desenha_frame();
	}

	egl_finalizar();

	return 0;
}
END_OF_MAIN();
```
Pronto temos nossas imagens, mas precisamos das posições deste personagem, então
devemos criar as variaveis posX e posY e inicia-las com uma posição na tela, para então desenhar-mos o personagem.

Assim temos:
```
#include <iostream>
#include <string>
#include <sstream>
#include "engcomp_glib.h" 

using namespace std; //a partir daqui vou passar a pular esta parte do código, mas o importante é saber que ela existe

int main(void)
{
	egl_inicializar(1024,768);
	
	imagem heroi_esquerda;
	imagem heroi_direita;
	imagem heroi_abaixa;
	imagem heroi_cima;
	imagem parado_direita;
	imagem parado_esquerda;
	
	heroi_esquerda.carregar("esquerda1.png");
	heroi_esquerda.carregar("esquerda2.png");
	heroi_esquerda.carregar("esquerda3.png");
	
	heroi_direita.carregar("direita1.png");
	heroi_direita.carregar("direita2.png");
	heroi_direita.carregar("direita3.png");
	
	heroi_abaixa.carregar("abaixa1.png");
	
	heroi_cima.carregar("cima.png");
	
	parado_direita.desenha("parado_direita.png");
	
	parado_esquerda.desenha("parado_esquerda.png");
	
	int posX = 250, posY=600; //reparem que usei apenas uma linha para as duas variaveis.
	
	while(!key[KEY_ESC])
	{
		parado_direita.desenha(posX,posY);


		egl_desenha_frame();
	}

	egl_finalizar();

	return 0;
}
END_OF_MAIN();
```
Desta forma desenhamos apenas o personagem na posição da direita então devemos fazer melhor
que isso, criaremos uma variavel de posição chamada position que nos dará o sentido do player
quando ele parar. Quando for 1 ele irá parar na posicção esquerda e quando for 2 irá parar na
posição direita.

Tambem devemos criar uma variavel movimento e um switch lendo essa variavel que será alterada
conforme o jogador pressiona as teclas.
```
int main(void)
{
	egl_inicializar(1024,768);
	
	imagem heroi_esquerda;
	imagem heroi_direita;
	imagem heroi_abaixa;
	imagem heroi_cima;
	imagem parado_direita;
	imagem parado_esquerda;
	
	heroi_esquerda.carregar("esquerda1.png");
	heroi_esquerda.carregar("esquerda2.png");
	heroi_esquerda.carregar("esquerda3.png");
	
	heroi_direita.carregar("direita1.png");
	heroi_direita.carregar("direita2.png");
	heroi_direita.carregar("direita3.png");
	
	heroi_abaixa.carregar("abaixa1.png");
	
	heroi_cima.carregar("cima.png");
	
	parado_direita.desenha("parado_direita.png");
	
	parado_esquerda.desenha("parado_esquerda.png");
	
	int posX = 250, posY=600, position = 2, movimento = 0; //reparem que usei apenas uma linha para as duas variaveis.
	
	while(!key[KEY_ESC])
	{
		if (movimento ==0)
			{
				if (position ==2)
					parado_direita.desenha(posX,posY);
				else
					parado_esquerda.desenha(posX, posY);
			}
		if (key[KEY_RIGHT])
			movimento = 1;
		if (key[KEY_LEFT])
			movimento =2;
		if (key[KEY_UP])
			movimento = 3;
		if(key[KEY_DOWN])
			movimento = 4;
		
		switch(movimento)
		{
		case 1:
			heroi_direita.desenha(posX,posY);
			position=2;//para que quando parar ele fique virado para a direita.
			break;
		case 2:
			heroi_esquerda.desenha(posX,posY);
			position = 1;//para ficar na posição esquerda quando parado.
			break;
		case 3:
			heroi_cima.desenha(posX,posY);
			break;
		case 4:
			heroi_abaixado.desenha(posX,posY);
			break;
		}

		egl_desenha_frame();
	}

	egl_finalizar();

	return 0;
}
END_OF_MAIN();
```
Muito bem nosso heroi já se mexe, mas fica plantado no omesmo lugar, então o que fazer.

Temos de incrementar a posição X quanto este vai para a direita e decrementar a posição Y
quando ele vai para a esquerda. Bom mas ele vai sumir da tela, o que faremos??

Atribuiremos um limite a ele, então se passar de 1020 setaremos sua posição em 1020, e se
for abaixo de 5 setaremos sua posição como 5, então nosso código final fica assim:
```
int main(void)
{
	egl_inicializar(1024,768);
	
	imagem heroi_esquerda;
	imagem heroi_direita;
	imagem heroi_abaixa;
	imagem heroi_cima;
	imagem parado_direita;
	imagem parado_esquerda;
	
	heroi_esquerda.carregar("esquerda1.png");
	heroi_esquerda.carregar("esquerda2.png");
	heroi_esquerda.carregar("esquerda3.png");
	
	heroi_direita.carregar("direita1.png");
	heroi_direita.carregar("direita2.png");
	heroi_direita.carregar("direita3.png");
	
	heroi_abaixa.carregar("abaixa1.png");
	
	heroi_cima.carregar("cima.png");
	
	parado_direita.desenha("parado_direita.png");
	
	parado_esquerda.desenha("parado_esquerda.png");
	
	int posX = 250, posY=600, position = 2, movimento = 0; //reparem que usei apenas uma linha para as duas variaveis.
	
	while(!key[KEY_ESC])
	{
		if (movimento ==0)
			{
				if (position ==2)
					parado_direita.desenha(posX,posY);
				else
					parado_esquerda.desenha(posX, posY);
			}
		if (key[KEY_RIGHT])
			movimento = 1;
		if (key[KEY_LEFT])
			movimento =2;
		if (key[KEY_UP])
			movimento = 3;
		if(key[KEY_DOWN])
			movimento = 4;
		
		switch(movimento)
		{
		case1:
			heroi_direita.desenha(posX,posY);
			posX++;
			if (posX > 1020) posX=1020;
			position=2;//para que quando parar ele fique virado para a direita.
			break;
		case 2:
			heroi_esquerda.desenha(posX,posY);
			posX--;
			if (posX < 5) posX = 5;
			position = 1;//para ficar na posição esquerda quando parado.
			break;
		case 3:
			heroi_cima.desenha(posX,posY);
			break;
		case 4:
			heroi_abaixado.desenha(posX,posY);
			break;
		}

		egl_desenha_frame();
	}

	egl_finalizar();

	return 0;
}
END_OF_MAIN();
```
Feito nosso personagem se move pelo cenário tranquilamente, tente agora atribuir a
ele outros movimentos como atirar, SALTAR (Este é um tanto complicado), golpear, correr,
coisas assim.

Qualquer duvida sobre este tuto mande email para jonesvg@gmail.com.

Até o próximo tutorial e abraços.