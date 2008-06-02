#include "stdafx.h"
#include "engcomp_glib.h"
using namespace std;

extern bool egl_init;
extern BITMAP *tela;
extern int res_x, res_y;
extern bool egl_debug;
extern std::string msg_erro;

imagem::imagem()
:index(-1), curr(0), vel(30), tempo(30)
{
	for(int i =0;i < 32;i++) 
		bmp[i] = 0;
}
imagem::imagem(const imagem &r)
{
	index = -1;
	curr = r.curr;
	vel = r.vel;
	tempo = r.tempo;
	clonarBitmap(r);
}
imagem& imagem::operator=(const imagem &r)
{
	if(*this != r)
	{
		index =- 1;
		curr = r.curr;
		vel = r.vel;
		tempo = r.tempo;
		clonarBitmap(r);
	}
	return *this;
}
bool imagem::operator==(const imagem &r)
{
	if(index == r.index && curr == r.curr && vel == r.vel && tempo == r.tempo)
		return true;
	else
		return false;
}
bool imagem::operator!=(const imagem &r)
{
	if(index != r.index || curr != r.curr || vel != r.vel || tempo == r.tempo)
		return true;
	else
		return false;
}
imagem::~imagem()
{
	for(int i =0;i <= index;i++)
		if(bmp[i]) destroy_bitmap(bmp[i]);
}

BITMAP* imagem::obter_bitmap()
{
	if(!egl_init) 
		return 0;
	if(index < 0) 
		return 0;

	return bmp[curr];
}

void imagem::obter_tamanho(int &w, int &h)
{
	if(!egl_init) 
		return;
	if(index < 0) 
		return;

	w = bmp[0]->w;
	h = bmp[0]->h;
}

void imagem::obter_dimenssoes(int &altura, int &largura, unsigned int index)
{
	if(!egl_init || index < 0) 
		return;
	largura = bmp[index]->w;
	altura = bmp[index]->h;
}
void imagem::setar_tempo_animacao(int veloc)
{
	vel = tempo = veloc;
}

bool imagem::carregar(string arquivo)
{
	bool sucesso(false);
	if(egl_init) 
	{
		index++;
		if(index <= 32) 
		{
			bmp[index] = load_bmp(arquivo.c_str(),0);
			if(!bmp[index]) 
			{
				index--;
				egl_erro("Erro carregando arquivo: " + arquivo);
				egl_debug = true;
			}
			else
			{
				armazenarInfo(arquivo, 0, 0, 0, 0, true);
				sucesso = true;
			}
		}
	}
	return sucesso;
}

bool imagem::carregar(string arquivo, int x, int y, int largura, int altura)
{
	bool sucesso(false);
	if(egl_init) 
	{
		index++;
		if(index <= 32) 
		{
			bmp[index] = create_bitmap(largura,altura);
			BITMAP* bmp_temp = load_bmp(arquivo.c_str(),0);
			if(!bmp_temp) 
			{
				index--;
				egl_erro("Erro carregando arquivo: " + arquivo);
				egl_debug = true;
			}
			else
			{
				blit(bmp_temp, bmp[index], x,y,0,0,largura,altura);
				destroy_bitmap(bmp_temp);
				armazenarInfo(arquivo, x, y, largura, altura, false);
				sucesso = true;
			}
		}
	}
	return sucesso;
}

bool imagem::desenha(int x, int y, bool borda)
{
	if(!egl_init) 
		return false;
	if(index < 0) 
		return false;
	draw_sprite(tela,bmp[curr],x,y);
	if(borda) 
		egl_retangulo(x,y,x+bmp[curr]->w,y+bmp[curr]->h,255,255,255);
	tempo--;
	if(!tempo)
	{
		curr++;
		tempo = vel;
		if(curr > index) 
		{
			curr = 0;
			return false;
		}
	}
	return true;
}

bool imagem::desenha_rotacionado(int x, int y, long rotacao )
{
	if(!egl_init) 
		return false;
	if(index < 0) 
		return false;
	rotacao = rotacao%256;
	rotate_sprite(tela,bmp[curr],x,y,itofix(rotacao));
	tempo--;
	if(!tempo)
	{
		curr++;
		tempo = vel;
		if(curr > index) 
		{
			curr = 0;
			return false;
		}
	}
	return true;
}
bool imagem::desenha_espelhado(int x, int y, bool horiz, bool vert)
{
	if(!egl_init) 
		return false;
	if(index < 0) 
		return false;
	if(horiz && vert)
	{
		draw_sprite_vh_flip(tela,bmp[curr],x,y);
	}
	else
	{
		if(horiz) draw_sprite_h_flip(tela,bmp[curr],x,y);
		if(vert) draw_sprite_v_flip(tela,bmp[curr],x,y);
	}
	tempo--;
	if(!tempo)
	{
		curr++;
		tempo = vel;
		if(curr > index) 
		{
			curr = 0;
			return false;
		}
	}
	return true;
}
bool imagem::colide(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	return (!( ((x1)>=(x2)+(w2)) || 
		((x2)>=(x1)+(w1)) || 
		((y1)>=(y2)+(h2)) || 
		((y2)>=(y1)+(h1)) ));
}
bool imagem::colide(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2, imagem &sprite2)
{
	if(!egl_init) 
		return false;
	if(index < 0) 
		return false;
	if(!colide(x1,y1,w1,h1,x2,y2,w2,h2)) 
		return false;
	int dx1, dx2, dy1, dy2; //We will use this deltas...
	int fx,fy,sx1,sx2; //Also we will use this starting/final position variables...
	int maxw, maxh; //And also this variables saying what is the maximum width and height...
	int depth; //This will store the color depth value...
	char CHARVAR; //We will use these to store the transparent color for the sprites...
	short SHORTVAR;
	long LONGVAR;
	BITMAP *spr1;
	BITMAP *spr2;
	spr1 = bmp[curr];
	spr2 = sprite2.obter_bitmap();

	//First we need to see how much we have to shift the coordinates of the sprites...
	if(x1>x2) {
		dx1=0;      //don't need to shift sprite 1.
		dx2=x1-x2;  //shift sprite 2 left. Why left? Because we have the sprite 1 being on the right of the sprite 2, so we have to move sprite 2 to the left to do the proper pixel perfect collision...
	} else {
		dx1=x2-x1;  //shift sprite 1 left.
		dx2=0;      //don't need to shift sprite 2.
	}
	if(y1>y2) {
		dy1=0;
		dy2=y1-y2;  //we need to move this many rows up sprite 2. Why up? Because we have sprite 1 being down of sprite 2, so we have to move sprite 2 up to do the proper pixel perfect collision detection...
	} else {
		dy1=y2-y1;  //we need to move this many rows up sprite 1.
		dy2=0;
	}

	//Then, we have to see how far we have to go, we do this seeing the minimum height and width between the 2 sprites depending in their positions:
	if(w1-dx1 > w2-dx2) {
		maxw=w2-dx2;
	} else {
		maxw=w1-dx1;
	}
	if(h1-dy1 > h2-dy2) {
		maxh=h2-dy2;
	} else {
		maxh=h1-dy1;
	}
	maxw--;
	maxh--;

	fy=dy1;
	fx=dx1;
	dy1+=maxh;
	dy2+=maxh;
	sx1=dx1+maxw;
	sx2=dx2+maxw;

	depth=bitmap_color_depth(spr1); //Get the bitmap depth...

	if(depth==8) {
		CHARVAR=bitmap_mask_color(spr1); //Get the transparent color of the sprites...
		for(; dy1>=fy; dy1--,dy2--) { //Go through lines...
			for(dx1=sx1,dx2=sx2; dx1>=fx; dx1--,dx2--) { //Go through the X axis...
				if((spr1->line[dy1][dx1]!=CHARVAR) && (spr2->line[dy2][dx2]!=CHARVAR)) return true; //Both sprites don't have transparent color in that position, so, theres a collision and return collision detected!
			}
		}
	} else {
		if(depth==16 || depth==15) {
			SHORTVAR=bitmap_mask_color(spr1); //Get the transparent color of the sprites...
			for(; dy1>=fy; dy1--,dy2--) { //Go through lines...
				for(dx1=sx1,dx2=sx2; dx1>=fx; dx1--,dx2--) { //Go through the X axis...
					if(( ((short *)spr1->line[dy1])[dx1]!=SHORTVAR) && ( ((short *)spr2->line[dy2])[dx2]!=SHORTVAR)) return true; //Both sprites don't have transparent color in that position, so, theres a collision and return collision detected!
				}
			}
		} else {
			if(depth==32) {
				LONGVAR=bitmap_mask_color(spr1); //Get the transparent color of the sprites...
				for(; dy1>=fy; dy1--,dy2--) { //Go through lines...
					for(dx1=sx1,dx2=sx2; dx1>=fx; dx1--,dx2--) { //Go through the X axis...
						if(( ((long *)spr1->line[dy1])[dx1]!=LONGVAR) && ( ((long *)spr2->line[dy2])[dx2]!=LONGVAR)) return true; //Both sprites don't have transparent color in that position, so, theres a collision and return collision detected!
					}
				}
			} else {
				if(depth==24) {
					CHARVAR=bitmap_mask_color(spr1)>>16; //if the order is RGB, this will contain B...
					SHORTVAR=bitmap_mask_color(spr1)&0xffff; //if the order is RGB, this will contain GR...
					for(; dy1>=fy; dy1--,dy2--) { //Go through lines...
						for(dx1=sx1,dx2=sx2; dx1>=fx; dx1--,dx2--) { //Go through the X axis...
							if( (*((short *)(spr1->line[dy1]+(dx1)*3))!=SHORTVAR) && (spr1->line[dy1][(dx1)*3+2]!=CHARVAR)  &&  (*((short *)(spr2->line[dy2]+(dx2)*3))!=SHORTVAR) && (spr2->line[dy2][(dx2)*3+2]!=CHARVAR) ) return true; //Both sprites don't have transparent color in that position, so, theres a collision and return collision detected!
							//I have tryed to avoid the above multiplications but it seems that GCC optimizes better than I :-))
						}
					}
				}
			}
		}
	}
	//If we have reached here it means that theres not a collision:
	return false; //Return no collision.
}
void imagem::clonarBitmap(const imagem &origem)
{
	std::vector<INFO_CLONAGEM>::const_iterator it;
	for(it = origem.infoClonagem.begin(); it != origem.infoClonagem.end(); it++)
	{
		if(it->ignorarDimenssoes)
		{
			carregar(it->nomeArquivo);
		}
		else
		{
			carregar(it->nomeArquivo, it->x, it->y, it->largura, it->altura);
		}
	}
}
void imagem::armazenarInfo(const std::string &nomeArquivo, int x, int y, int largura, int altura, bool ignorarDimenssoes)
{
	INFO_CLONAGEM info;
	info.nomeArquivo = nomeArquivo;
	info.x = x;
	info.y = y;
	info.largura = largura;
	info.altura = altura;
	info.ignorarDimenssoes = ignorarDimenssoes;
	infoClonagem.push_back(info);
}
