#pragma once

/*
Biblioteca de Desenvolvimento de Jogos do Curso de Engenharia da Computação da UNISINOS
by Farlei J. Heinen (30/05/2006) - farleih@gmail.com

Funções de Colisão obtidas de: Ivan Baldo - lubaldo@adinet.com.uy (PPCol Library)
*/

#include "library_version.h"
#include <string>
#include <vector>
#include <list>

using namespace std;

//tipos de cursores
#define CURSOR_NENHUM MOUSE_CURSOR_NONE
#define CURSOR_EGL MOUSE_CURSOR_ALLEGRO
#define CURSOR_SETA MOUSE_CURSOR_ARROW
#define CURSOR_CARREGANDO MOUSE_CURSOR_BUSY
#define CURSOR_PERGUNTA MOUSE_CURSOR_QUESTION
#define CURSOR_EDITAR MOUSE_CURSOR_EDIT

#define EGL_CALL_CONV _cdecl

/*
#ifdef __cplusplus
   extern "C" {
#endif
*/

extern bool egl_init;
extern SDL_Surface* tela;

extern SDL_Event eventos;
extern bool key[323];

extern int mouse_x;
extern int mouse_y;
extern int mouse_b;

extern int res_x; 
extern int res_y;
extern Uint32 clear_color;
extern bool egl_debug;
extern string msg_erro;

bool EGL_CALL_CONV egl_inicializar(int w, int h, bool janela = false );

void EGL_CALL_CONV egl_finalizar();

void EGL_CALL_CONV egl_desenha_frame(bool limpa = true, bool sync = false);

void EGL_CALL_CONV egl_pixel(int x,int y, int vermelho, int verde, int azul);

void EGL_CALL_CONV egl_processa_eventos();

void EGL_CALL_CONV egl_sleep(int milisec);

void EGL_CALL_CONV egl_erro(string mensagem);

void EGL_CALL_CONV egl_linha(int x1,int y1, int x2,int y2, int vermelho, int verde, int azul);

void EGL_CALL_CONV egl_retangulo(int x1,int y1, int x2,int y2, int vermelho, int verde, int azul);

/*

void EGL_CALL_CONV egl_texto(string txt, int x, int y, int cR=255, int cG=255, int cB=255);

void EGL_CALL_CONV read_string(char *str_to, int size, int x, int y);

void EGL_CALL_CONV egl_ler_string_teclado(string &buffer, int tamanho_buffer, int x, int y);

void EGL_CALL_CONV egl_cursor(int tipo_cursor);

void EGL_CALL_CONV egl_cursor(string caminho);

*/

///////////////////////////////////////////////////////////////////////////////////////

/*

class imagem
{
protected:
	vector<BITMAP*> bmp;
	int index;
	int curr;
	int tempo;
	int vel;

	int type; // 0:normal, 1:PNG
	bool decl_global; // indica declaracao global

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
	void setGlobal(bool global=true);
	bool carregar(string arquivo, bool global=false);	
	bool carregar(string arquivo, int x, int y, int largura, int altura);
	bool desenha(int x, int y, bool borda=false);
	bool desenha_transparente(int x, int y, int trans=128);
	bool desenha_rotacionado(int x, int y, long rotacao );
	bool desenha_espelhado(int x, int y, bool horiz=true, bool vert=false );
	bool colide(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
	bool colide(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2, imagem &sprite2);
	bool colide(int x1, int y1, int x2, int y2, imagem &sprite2);
	
	void clonarBitmap(const imagem& cp);
protected:
	// // atributo de status para indicar falha 
	bool falha;
	// atributo com a mensagem relacionada com a falha
	string falha_str;
};

// Classe fonte bitmap: contribuicao de Luan Carlos Nesi
// 18/11/2008
class fonte
{
private:

	vector<imagem> letras;
	int ii,jj;

public:
	fonte();
	~fonte();

	void carregar(string arquivo, bool global=false);
	void desenha_texto(string txt, int x, int y, float space=0.5f);
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


enum TIPO_SOM {T_WAV, T_MID};

class som
{
protected:
	SAMPLE *smp;
	MIDI *mid;

	TIPO_SOM tipo;

	int volume;
	int posicao;
	int frequencia;

	int voice;
    
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
	bool final();
private:
	std::string nomeArquivo;
};

//	Código adaptado de http://www.codeproject.com/KB/recipes/geometry.aspx
//	Autor: Chris Maunder
//	Site: Code Project - http://www.codeproject.com

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

#include "TileEngine.h"

#ifdef __cplusplus
   }
#endif

 */