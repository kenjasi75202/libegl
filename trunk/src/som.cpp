#include "engcomp_glib.h"


som::som()
:smp(0), mid(0), volume(255), posicao(128), frequencia(1000), voice(-1)
{
}
som::som(const som &r)
{
	volume = r.volume;
	posicao = r.posicao;
	frequencia = r.frequencia;
	nomeArquivo =  r.nomeArquivo;
	carregar(r.nomeArquivo);
	voice = r.voice;
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
		voice = r.voice;
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
	if(mid) destroy_midi(mid);
}

bool som::carregar(string arquivo)
{
	if(!egl_init) 
		return false;
	
	string extensao;
	extensao = arquivo.substr(arquivo.find_last_of(".")+1, arquivo.length());

	if (extensao == "wav" || extensao == "wave")
		tipo = T_WAV;
	else if (extensao == "mid" || extensao == "midi")
		tipo = T_MID;

	if (tipo == T_WAV)
	{
		if(smp)
		{
			destroy_sample(smp);
			voice = -1;
		}
		smp = load_wav(arquivo.c_str());
		if(!smp) 
		{
			egl_erro("Erro carregando arquivo: " + arquivo);
			egl_debug = true;
			return false;
		}
	} else if (tipo == T_MID) 
	{
		if(mid)
		{
			destroy_midi(mid);
			voice = -1;
		}
		mid = load_midi(arquivo.c_str());
		if(!mid) 
		{
			egl_erro("Erro carregando arquivo: " + arquivo);
			egl_debug = true;
			return false;
		}
	}
	return true;
}
void som::tocar(int repetir)
{
	if (tipo == T_WAV)
	{
		if(!smp) 
			return;
		voice = play_sample(smp,volume,posicao,frequencia,repetir);
	} else if (tipo == T_MID)
	{
		if(!mid) 
			return;
		voice = play_midi(mid,repetir);
	}
}
void som::parar()
{
	if (tipo == T_WAV)
	{
		if(!smp) return;
		stop_sample(smp);
	} else if (tipo == T_MID)
	{
		if(!mid) return;
		stop_midi();
	}
}
void som::ajustar(int vol, int pan, int freq, int loop)
{
	if (tipo == T_WAV)
	{
		if(!smp) 
			return;
		adjust_sample(smp, vol,  pan, freq, loop);
		volume = vol;
		posicao = pan;
		frequencia = freq;
	} else if (tipo == T_MID)
	{
		egl_erro("Não é possível ajustar um som no formato MIDI");
		egl_debug = true;
	}
}
bool som::final()
{
	if (tipo == T_WAV) {
		if(!smp) return true;
	} else if (tipo == T_MID) {
		if(!mid) return true;
	}
	if(voice < 0) return true;

	if(voice_get_position(voice) < 0) 
		return true;
	else
		return false;
}