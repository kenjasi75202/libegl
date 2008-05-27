#pragma once

/*
Biblioteca de Desenvolvimento de Jogos do Curso de Engenharia da Computação da UNISINOS
by Farlei J. Heinen (30/05/2006) - farleih@gmail.com

Funções de Colisão obtidas de: Ivan Baldo - lubaldo@adinet.com.uy (PPCol Library)

10/05/2007
Versão atualizada para suporte ao Dev-Cpp com Allegro 4.2

23/03/2008
Nova versão adaptada para o Visual Studio 2008
Árvore de diretórios alterada para adição do google code

26/05/2008
Adaptação para .h/.cpp (compatibilidade)

Versão: 2.0 ALPHA 

*/

#include "library_version.h"
#include <string>

using namespace std;


#ifdef __cplusplus
   extern "C" {
#endif


extern bool egl_init;
extern BITMAP *tela;

extern int res_x; 
extern int res_y;
extern bool egl_debug;
extern string msg_erro;


bool egl_inicializar(int w, int h, bool janela = false );

void egl_finalizar();

void egl_desenha_frame(bool limpa = true, bool sync = false);

void egl_texto(string txt, int x, int y, int cR, int cG, int cB);

void egl_sleep(int milisec);

void egl_pixel(int x,int y, int vermelho, int verde, int azul);

void egl_linha(int x1,int y1, int x2,int y2, int vermelho, int verde, int azul);

void egl_retangulo(int x1,int y1, int x2,int y2, int vermelho, int verde, int azul);

void egl_erro(string mensagem);

void read_string(char *str_to, int size, int x, int y);

void egl_ler_string_teclado(string &buffer, int tamanho_buffer, int x, int y);

class imagem
{
protected:
	BITMAP* bmp[32];
	int index;
	int curr;
	int tempo;
	int vel;

public:
	imagem();
	~imagem();

	BITMAP* obter_bitmap();
	void obter_tamanho(int &w, int &h);
	int getResX();
	int getResY();
	void setar_tempo_animacao(int veloc);
	bool carregar(string arquivo);	
	bool carregar(string arquivo, int x, int y, int largura, int altura);
	bool desenha(int x, int y, bool borda=false);
	bool desenha_rotacionado(int x, int y, long rotacao );
	bool desenha_espelhado(int x, int y, bool horiz=true, bool vert=false );
	bool colide(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
	bool colide(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2, imagem &sprite2);
 };


class fundo
{
protected:
	BITMAP *bmp;

public:
	fundo();
	~fundo();

	bool carregar(string arquivo);
	void desenha(int x, int y);
};


class som
{
protected:
	SAMPLE *smp;

	int volume;
	int posicao;
	int frequencia;
    
public:
	som();
	~som();

	bool carregar(string arquivo);
	void tocar(int repetir = 0);	
	void parar();
	void ajustar(int vol, int pan=128, int freq=1000, int loop=0);	
};


#ifdef __cplusplus
   }
#endif