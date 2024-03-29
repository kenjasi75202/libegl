#include "engcomp_glib.h"

fonte::fonte()
{
	ii = jj = 0;
}

fonte::~fonte()
{
}

//TODO: adicionar parametro para indicar fonte global
void fonte::carregar(string arquivo, bool global)
{
	if(!egl_init) return;

	int resX;
	int resY;

	// Obtem o tamanho da imagem
	imagem* imgt = new imagem();
	imgt->carregar(arquivo);
	resX = imgt->getResX();
	resY = imgt->getResY();
	delete imgt;

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
			letras[ind].setGlobal(global);
			ind++;
		}
	}
}

//Fun��o que escreve o texto
void fonte::desenha_texto(string txt, int x, int y, float space)
{
	if(!egl_init) return;
	
	//Escreve o texto na tela
	int pos;
	for(int n = 0; n < txt.size(); n++)
	{
		pos = txt[n]-32;
		if(pos < 108)
			letras[pos].desenha( (x+n*(jj*space)) , y);
	}
}
