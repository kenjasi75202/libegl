# TUTORIAL "ALO MUNDO" COM LIBEGL FONTS #

**NÃO IREI USAR ORIENTAÇÃO A OBJETOS POR SE TRATAR DE TUTORIAL PARA INICIANTES.**

Bom e por que não fazer um tutorial "ALO MUNDO" com as fontes da LibEgl?? Então mãos a obra.

Primeiramente devemos trabalhar com a base da EGL cujo código está logo abaixo:

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

Pela primeira vez iremos esmiuçar este código:

```
#include <iostream> // Incluir InPut e OutPut no código.
#include <string> // Incluir o tipo de váriavel String no código.
#include "engcomp_glib.h" // Incluir os métodos da EGL no seu programa.
```

Estes Includes te darão metódos minimos para trabalhar com a EGL, pelo menos neste tutorial.

```
using namespace std; //Trabalhar com o namespace standard.
```

Todas as classes, objetos e funções da biblioteca padrão C++ estão definidas dentro do namespace std.

```
int main(void)
{
	egl_inicializar(1024,768);
```

O main do programa, na linha egl\_inicializar teremos a resolução da janela da egl, aqui estamos setando ela em 1024 por 768.

```
while(!key[KEY_ESC])
	{
	


		egl_desenha_frame();
	}
```

O loop principal do programa aonde a egl desenhara volta após volta os frames do jogo.

```
egl_finalizar();

	return 0;
}
END_OF_MAIN();
```

Aqui finalizamos a egl e como estamos usando int main() devemos retornar algo ao finalizar o main então retornamos 0. END\_OF\_MAIN(); é a linha que inaliza totalmente os trabalhos, sem ela a egl não funciona, isto vem direto do Allegro.

Então depois destas explicações entramos no tutorial em si.

```
int main(void)
{
	egl_inicializar(1024,768);
	fonte arial;

        arial.carregar("fonte.bmp");
	while(!key[KEY_ESC])
```

Aqui criamos o objeto arial da classe fonte e o carregamos com o arquivo fonte.bmp, existem nas pastas da egl alguns exemplos deste tipo de fontes, aqui estamos criando o objeto e carregando ele dentro do main.

```
       while(!key[KEY_ESC])
	{
	        arial.desenha_texto("Alo Mundo!",512,384);


		egl_desenha_frame();
	}
```

Dentro do while fazemos a egl desenhar na tela a frase "Alo Mundo!", simples assim.

Chegamos ao fim deste tutorial, abraços e até o próximo.