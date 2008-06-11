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

02/06/2008
Adição de suporte a arquivos .PNG (via ALPNG)

04/06/2008
desenha_transparente(...)
Adição da classe CPolygon - Teste de uma coordenada (x,y,z) dentro de
um polígono 2D ou 3D.

Versão: 2.1 Beta 

*/

#include "library_version.h"
#include "alpng.h"
#include <string>
#include <vector>

using namespace std;


#ifdef __cplusplus
   extern "C" {
#endif

#define EGL_CALL_CONV _cdecl

extern bool egl_init;
extern BITMAP *tela;

extern int res_x; 
extern int res_y;
extern bool egl_debug;
extern string msg_erro;


bool EGL_CALL_CONV egl_inicializar(int w, int h, bool janela = false );

void EGL_CALL_CONV egl_finalizar();

void EGL_CALL_CONV egl_desenha_frame(bool limpa = true, bool sync = false);

void EGL_CALL_CONV egl_texto(string txt, int x, int y, int cR=255, int cG=255, int cB=255);

void EGL_CALL_CONV egl_sleep(int milisec);

void EGL_CALL_CONV egl_pixel(int x,int y, int vermelho, int verde, int azul);

void EGL_CALL_CONV egl_linha(int x1,int y1, int x2,int y2, int vermelho, int verde, int azul);

void EGL_CALL_CONV egl_retangulo(int x1,int y1, int x2,int y2, int vermelho, int verde, int azul);

void EGL_CALL_CONV egl_erro(string mensagem);

void EGL_CALL_CONV read_string(char *str_to, int size, int x, int y);

void EGL_CALL_CONV egl_ler_string_teclado(string &buffer, int tamanho_buffer, int x, int y);

class imagem
{
protected:
	vector<BITMAP*> bmp;
	int index;
	int curr;
	int tempo;
	int vel;

public:
	imagem(const imagem& cp);
	imagem();
	~imagem();

	imagem& operator=(const imagem &r);
	bool operator==(const imagem &r);
	bool operator!=(const imagem &r);

	BITMAP* obter_bitmap();
	void obter_tamanho(int &w, int &h);
	void obter_dimensoes(int &altura, int &largura, unsigned int index);
	int getResX();
	int getResY();
	void setar_tempo_animacao(int veloc);
	bool carregar(string arquivo);	
	bool carregar(string arquivo, int x, int y, int largura, int altura);
	bool desenha(int x, int y, bool borda=false);
	bool desenha_transparente(int x, int y, int trans=128);
	bool desenha_rotacionado(int x, int y, long rotacao );
	bool desenha_espelhado(int x, int y, bool horiz=true, bool vert=false );
	bool colide(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
	bool colide(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2, imagem &sprite2);
	void clonarBitmap(const imagem& cp);
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
	void desenha_transparente(int x, int y, int trans=128);
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

/*
	Código adaptado de http://www.codeproject.com/KB/recipes/geometry.aspx
	Autor: Chris Maunder
	Site: Code Project - http://www.codeproject.com
*/
struct POINT_3D
{
	float x,y,z;
};

class CPolygon
{
public:
	CPolygon(void);
	virtual ~CPolygon(void);
	int	GetSize() { return m_point3D.size(); }
	bool PointIn(POINT_3D P);				
	void RemoveAll();
	void Add(POINT_3D point);				
	void BoundingBox(POINT_3D &bottomLeft, POINT_3D &topRight);
private:
	std::vector<POINT_3D>  m_point3D;
};


#ifdef __cplusplus
   }
#endif
