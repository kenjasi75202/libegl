/*
Biblioteca de Desenvolvimento de Jogos do Curso de Engenharia da Computação da UNISINOS
by Farlei J. Heinen (30/05/2006) - farleih@gmail.com

Funções de Colisão obtidas de: Ivan Baldo - lubaldo@adinet.com.uy (PPCol Library)

10/05/2007
Versão atualizada para suporte ao Dev-Cpp com Allegro 4.2

23/03/2008
Nova versão adaptada para o Visual Studio 2008
Árvore de diretórios alterada para adição do google code

Versão: 2.0

*/
#pragma once
#include "allegro.h"
#include <string>
#include <vector>
bool egl_inicializar(int w, int h, bool janela = false);

void egl_finalizar();

void egl_desenha_frame(bool limpa = true, bool sync = false);

void egl_texto(std::string txt, int x, int y, int cR=255, int cG=255, int cB=255);

void egl_sleep(int milisec);

void egl_pixel(int x,int y, int vermelho, int verde, int azul);

void egl_linha(int x1,int y1, int x2,int y2, int vermelho, int verde, int azul);

void egl_retangulo(int x1,int y1, int x2,int y2, int vermelho, int verde, int azul);

void egl_erro(std::string mensagem);

// Adaptada de um exemplo de: Kronoman - Taking a string from keyboard
// BUG: não aceita acentos (perde a sincronia do cursor)
// BUG: no limite maximo do texto ele adiciona 2 chars simultaneos???
// SUGESTÃO: adicionar a possibilidade de passar uma cor como parametro
void read_string(char *str_to, int size, int x, int y);
// IMPORTANTE: essa função é síncrona !!!!
void egl_ler_string_teclado(std::string &buffer, int tamanho_buffer, int x, int y);

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
	imagem(const imagem &r);
	imagem& operator=(const imagem &r);
	bool operator==(const imagem &r);
	bool operator!=(const imagem &r);
	~imagem();
	BITMAP* obter_bitmap();
	void obter_tamanho(int &w, int &h);
	void setar_tempo_animacao(int veloc);
	bool carregar(std::string arquivo);
	bool carregar(std::string arquivo, int x, int y, int largura, int altura);
	bool desenha(int x, int y, bool borda=false);
	bool desenha_rotacionado(int x, int y, long rotacao );
	bool desenha_espelhado(int x, int y, bool horiz=true, bool vert=false );
	bool colide(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
	bool colide(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2, imagem &sprite2);
	void obter_dimenssoes(int &altura, int &largura, unsigned int index);
private:
	void clonarBitmap(const imagem &origem);
	void armazenarInfo(const std::string &nomeArquivo, int x, int y, int largura, int altura, bool ignorarDimenssoes);
	struct INFO_CLONAGEM
	{
		std::string nomeArquivo;
		int x;
		int y;
		int largura;
		int altura;
		bool ignorarDimenssoes;
	};
	std::vector<INFO_CLONAGEM> infoClonagem;
 };

class fundo
{
protected:
	BITMAP *bmp;

public:
	fundo();
	fundo(const fundo &r);
	fundo& operator=(const fundo &r);
	bool operator==(const fundo &r);
	bool operator!=(const fundo &r);
	~fundo();
	bool carregar(std::string arquivo);
	void desenha(int x, int y);
private:
	std::string nomeArquivo;
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
	som(const som &r);
	som& operator=(const som &r);
	bool operator==(const som &r);
	bool operator!=(const som &r);
	~som();
	bool carregar(std::string arquivo);
	void tocar(int repetir = 0);
	void parar();
	void ajustar(int vol, int pan=128, int freq=1000, int loop=0);
private:
	std::string nomeArquivo;
};

