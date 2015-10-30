# TUTORIAL CRIANDO TELA DE INTRODUÇÃO E GAME OVER NA LIB EGL: #

**NÃO IREI USAR ORIENTAÇÃO A OBJETOS POR SE TRATAR DE TUTORIAL PARA INICIANTES.**

Telas de introdução e game Over são itens esseciais para jogos certo, mas como criá-las
em jogos programados com libegl, simples, você deve usar mais de um loop (while).

Como fazer então, primeiro devemos abrir a base da egl e salvá-la com outro nome.

Agora vejamos o codigo da base:
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

Você tem um while principal que sairá quando teclar ESC, bom aqui antes deste while criaremos outro while
que fara as vezes de introdução. E depois deste um que irá fazer as vezes de Game Over.

Vejamos como ficará:

```
#include <iostream>
#include <string>
#include <sstream>
#include "engcomp_glib.h"

using namespace std;

int main(void)
{
	egl_inicializar(1024,768);
	
	while(!key[KEY_ENTER])
	{
	
	egl_desenha_frame();
	}
	
	while(!key[KEY_ESC])
	{
	


		egl_desenha_frame();
	}
	
	while(!key[KEY_ENTER])
	{
	
	egl_desenha_frame();
	}

	egl_finalizar();

	return 0;
}
END_OF_MAIN();
```

Note que usei o egl\_desenha\_frame() em todos os loops, isso é indispensável.

Bom, mas aqui sabemos que aparecerá uma tela preta no inicio, quando apertarmos ENTER
iniciará o loop do jogo, ao teclarmos ESC iremos para o Game OVER, uma tela preta tambem
e novamente precionando ENTER sairemos do jogo.

Podemos aqui criar um novo loop (while) que aninhe estes três primeiro para que ao darmos
ENTER em Game Over retorne para a tela de introdução. Mas então devemos setar uma forma de
sair do jogo (sair dete while), pois ESC ou ENTER não poderemos usar, a forma mais facil seria
setar condição de game over, como vidas para o player e deixar o ESC para o loop que aninha
a todos, mas isso você deve fazer, assim como colocar imagens de fundo para intro e game over,
uma dica seria usar booleanas para game over, enquanto false o jogo rola tranquilo, mas quando
true sai do jogo e entra em game over.

Qualquer duvida mande e-mail para jonesvg@gmail.com.

Abraços e até o proximo tutorial.