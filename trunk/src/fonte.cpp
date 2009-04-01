#include "engcomp_glib.h"

fonte::fonte()
{
	ii = jj = 0;
}

fonte::~fonte()
{
}

void fonte::carregar(string arquivo)
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
			ind++;
		}
	}
}

//Função que escreve o texto
void fonte::desenha_texto(string txt, int x, int y, float space)
{
	if(!egl_init) return;


	//TODO: a variavel space esta afetando a posicao inicial
	//TODO: testar se colocou letras invalidas (>= 108)

	//Escreve o texto na tela
	for(int n = 0; n < txt.size(); n++)
	{
		letras[txt[n]-32].desenha( (x+n*jj)*space , y);
	}
}