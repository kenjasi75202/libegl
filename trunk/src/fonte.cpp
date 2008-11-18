#include "engcomp_glib.h"

fonte::fonte()
{
	ii = jj = 0;
}

fonte::~fonte()
{
}

void fonte::carregar(string arquivo, int resX, int resY)
{
	letras.resize(108); //Vetor de caracteres

	//Calcula o tamanho da letra
	ii = resY/4;
	jj = resX/26;

	int ind = 0;
	for(int i = 0; i < 4; i++)   //Recorta cada letra com o tamanho especificado
	{
		for(int j = 0; j < 26; j++)
		{
			letras[ind].carregar(arquivo,j*jj,i*ii,jj,ii);
			ind++;
		}
	}
}

//Função que escreve o texto
void fonte::desenha_texto(string txt, int x, int y)
{
	//Escreve o texto na tela
	for(int n = 0; n < txt.size(); n++)
	{
		letras[txt[n]-32].desenha(x+n*jj,y);
	}
}