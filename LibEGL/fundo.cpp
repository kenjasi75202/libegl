#include "stdafx.h"
#include "engcomp_glib.h"
using namespace std;

extern bool egl_init;
extern BITMAP *tela;
extern int res_x, res_y;
extern bool egl_debug;
extern std::string msg_erro;
fundo::fundo()
{
	bmp = 0;
}
fundo::fundo(const fundo &r)
{
	nomeArquivo = r.nomeArquivo;
	carregar(r.nomeArquivo);
}
fundo& fundo::operator=(const fundo &r)
{
	nomeArquivo = r.nomeArquivo;
	carregar(r.nomeArquivo);
	return *this;
}
bool fundo::operator==(const fundo &r)
{
	if(nomeArquivo == r.nomeArquivo)
		return true;
	else
		return false;
}
bool fundo::operator!=(const fundo &r)
{
	if(nomeArquivo != r.nomeArquivo)
		return true;
	else
		return false;
}

fundo::~fundo()
{
	if(bmp) 
		destroy_bitmap(bmp);
}
bool fundo::carregar(string arquivo)
{
	if(!egl_init) 
		return false;
	if(bmp) 
		destroy_bitmap(bmp);
	bmp = load_bmp(arquivo.c_str(),0);
	if(!bmp) 
		return false;
	return true;
}

void fundo::desenha(int x, int y)
{
	if(!egl_init) 
		return;
	if(!bmp) 
		return;
	blit(bmp,tela,x,y,0,0,res_x,res_y);
}