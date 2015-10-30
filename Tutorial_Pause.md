# PAUSANDO O JOGO #

Uma grande sacada para o player que irá jogar em seu jogo é ele poder pausar e ir comer um lanchinho ou quando a mãe dele chamar para lavar a louça ou sei lá, o cara ta apertadão e precisa ir ao banheiro... bom para isso mostrarei um método rápido, simples e fácil de fazer.

Começaremos pela Base como sempre:

```
#include <iostream>
#include <string>
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

Agora que temos a base iremos trabalhar apenas no main, aqui precisaremos de um novo loop dentro do loop principal do jogo. Então:

```
int main(void)
{
        egl_inicializar(1024,768);
        bool pausa;
        while(!key[KEY_ESC])
        {
                while(!pausa)
                {

                       egl_desenha_frame();// Já explico o porque deste desenha frame.
                }


                egl_desenha_frame();
        }

        egl_finalizar();

        return 0;
}
```

Certo criamos um loop que irá se desfazer a partir de uma variavel bool e é claro devemos declarar esta variavel, o desenha frame dentro deste loop é para podermos colocar alguma imagem nele.

Bom, mas assim ainda não conseguimos pausar nosso jogo não é, precisamos de um comando para pausar, este comando deve setar nosso bool pausa como true, então vejamos como fica:

```
 while(!pausa)
                {
                   if (key[KEY_ENTER]) 
			{
			      pausa = true;
			}
                   egl_desenha_frame();
                }
```

Será que apenas fazer isso resolve?? Teste seu programa e veja.

Não conseguiu ver?? Certo acho que devemos então colocar algo ali para nos dar a indicação de que o programa pausou, vamos então criar um objeto fonte e carregá-lo com uma fonte e lá no loop fora do loop pausa vamos escrever "JOGO PARADO".

```
int main(void)
{
        egl_inicializar(1024,768);
        bool pausa;
        fonte pause;
        pause.carregar("font1.bmp");
        while(!key[KEY_ESC])
        {
                while(!pausa)
                {
                       if (key[KEY_ENTER]) 
			{
			      pausa = true;
			}
                       egl_desenha_frame();
                }

                pause.desenha_texto("JOGO PARADO", 850, 400);
                egl_desenha_frame();
        }

        egl_finalizar();

        return 0;
}
```

Certo, teste agora vamos ver o que acontece.

Apareceu a escrita e você não consegue sair do pause não é, isso porque não temos ainda um comando que nos faça voltar. Precisamos de um comando que faça a bool pausa retornar a ser false vejamos abaixo:
```
while(!key[KEY_ESC])
        {
               
                    while(!pausa)
                    {
                       if (key[KEY_ENTER]) 
			{
			      pausa = true;
			}
                       egl_desenha_frame();
                    }
                
                if(key[KEY_ENTER])
			{
				pausa = false;
			}

                pause.desenha_texto("JOGO PARADO", 850, 400);
                egl_desenha_frame();
        }
```

Teste o jogo agora e veja o que acontece.

A fonte não sai da tela não é, isso porque nós a desenhamos, mas não mandamos que ela parasse de desenhar. Para isso coloque o comando de desenhar o texto dentro de um comando que só trabalhe quando pausa for true, teste novamente.

Agora o ENTER está disparando e fazendo o jogo pausar diversas vezes certo, ele pausa, sai do pause e entra de novo, a EGL lê o pressionamento das teclas muito rápido, então a cada vez que você pressiona uma tecla é como se tivesse pressionado diversas vezes, resolvemos isso com um contador, este deve estar ligado ao comando que lê o ENTER, vejamos como fica:

```
int main(void)
{
	egl_inicializar(1024,768);
	fonte arial;
	int cont;//Contador
	arial.carregar("font1.bmp");
	bool pausa;
	pausa = false;
	while(!key[KEY_ESC])
	{
		while(!pausa)
				{
					cont++;//Contando
					if (cont> 100)
						if (key[KEY_ENTER]) 
						{
							pausa = true;
							cont = 0;//Iniciando o contador.
						}

					egl_desenha_frame();
				}
		cont++;//Contando
		if (cont>100)
			if(key[KEY_ENTER])
			{
				pausa = false;
				cont = 0;//Iniciando o ccontador.
			}
		
		if (pausa) arial.desenha_texto("JOGO PARADO",850,400);
		
		egl_desenha_frame();
	}

	egl_finalizar();

	return 0;
}
```

Com o contador sabemos que ao precionarmos ENTER só irá contar como uma vez e só contará uma nova vez quando o contador chegar a 100, isso deve nos dar alguns milesegundos.

Teste e veja.

Bom agora esta tudo certo, mas o jogo só sai quando pausamos e então precionamos ESC, se não ele não sai, teremos então de adicionar ao loop do jogo um novo aspecto para sair, que deverá ser a tecla ESC.

Abaixo segue o código completo:

```
#include <iostream>
#include <string>
#include <sstream>
#include "engcomp_glib.h"

using namespace std;

int main(void)
{
	egl_inicializar(1024,768);
	fonte arial;
	int cont;
	arial.carregar("font1.bmp");
	bool pausa;
	//pausa = false;
	while(!key[KEY_ESC])
	{
		while(!pausa && !key[KEY_ESC])//Aqui deve-se adicionar a tecla ESC.
				{
					cont++;
					if (cont> 100)
						if (key[KEY_ENTER]) 
						{
							pausa = true;
							cont = 0;
						}

					egl_desenha_frame();
				}
		cont++;
		if (cont>100)
			if(key[KEY_ENTER])
			{
				pausa = false;
				cont = 0;
			}
		
		if (pausa) arial.desenha_texto("JOGO PARADO",850,400);
		
		egl_desenha_frame();
	}

	egl_finalizar();

	return 0;
}
END_OF_MAIN();
```

Bom era isso, temos mais um tutorial finalizado, qualquer duvida mande um e-mail para jonesvg@gmail.com, abraços e até o próximo tutorial.