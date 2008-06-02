#include "stdafx.h"
#include "engcomp_glib.h"
using namespace std;

extern bool egl_init;
extern BITMAP *tela;
extern int res_x, res_y;
extern bool egl_debug;
extern std::string msg_erro;

som::som()
:smp(0), volume(255), posicao(128), frequencia(1000)
{
}
som::som(const som &r)
{
	volume = r.volume;
	posicao = r.posicao;
	frequencia = r.frequencia;
	nomeArquivo =  r.nomeArquivo;
	carregar(r.nomeArquivo);
}
som& som::operator=(const som &r)
{
	if(*this != r)
	{
		volume = r.volume;
		posicao = r.posicao;
		frequencia = r.frequencia;
		nomeArquivo =  r.nomeArquivo;
		carregar(r.nomeArquivo);
	}
	return *this;
}
bool som::operator==(const som &r)
{
	if(volume == r.volume && posicao == r.posicao && frequencia == r.frequencia && nomeArquivo ==  r.nomeArquivo)
		return true;
	else
		return false;
}
bool som::operator!=(const som &r)
{
	if(volume != r.volume || posicao != r.posicao || frequencia != r.frequencia || nomeArquivo !=  r.nomeArquivo)
		return true;
	else
		return false;
}
som::~som()
{
	if(smp) destroy_sample(smp);
}

bool som::carregar(string arquivo)
{
	if(!egl_init) 
		return false;
	if(smp) 
		destroy_sample(smp);
	smp = load_wav(arquivo.c_str());
	if(!smp) 
	{
		egl_erro("Erro carregando arquivo: " + arquivo);
		egl_debug = true;
		return false;
	}
	return true;
}
void som::tocar(int repetir)
{
	if(!smp) 
		return;
	play_sample(smp,volume,posicao,frequencia,repetir);
}
void som::parar()
{
	if(!smp) return;
	stop_sample(smp);
}
void som::ajustar(int vol, int pan, int freq, int loop)
{
	if(!smp) 
		return;
	adjust_sample(smp, vol,  pan, freq, loop);
	volume = vol;
	posicao = pan;
	frequencia = freq;
}