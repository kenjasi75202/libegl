#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "allegro//include//allegro.h"
#include "engcomp_glib.h"

using namespace std;


struct retan
{
	float rx1,ry1,rx2,ry2;
};


int main(int argc, char *argv[])
{
	if(argc < 2) 
	{
		cout << "ERRO: um .BMP deve ser passado como parametro!";
		return 1;
	}

	egl_inicializar(1024,768);

	char texto[512];
	int x,y,difx,dify,sw,sh;
	bool ret;
	struct retan curr;
	vector<struct retan> vr;

	bool trim;
	struct retan curr_trim;
	

	imagem sprites;
	if(!sprites.carregar(argv[1]))
	{
		egl_erro("Erro tentando carregar:"+(string)argv[1]);
		return 2;
	}
	
	imagem mouse;
	mouse.carregar("sprites//mouse.bmp");

	imagem ajuda;
	ajuda.carregar("sprites//help_teclado.bmp");

	x = 0; y = 0;
	sprites.obter_tamanho(sw,sh);
	
	difx = sw - 1024;
	if(difx < 0) difx = 0;

	dify = sh - 768;
	if(dify < 0) dify = 0;

	ret = false;
	trim = false;

	float vel = 0.1;

	bool deletando = false;

	while(!key[KEY_ESC])
	{
		if(dify && !trim && !ret)
		{
			if(key[KEY_PGUP] && (y<0))
			{
				y++;
			}
			if(key[KEY_PGDN] && (y > -dify))
			{
				y--;
			}

		}

		if(difx && !trim && !ret)
		{
			if(key[KEY_DEL] && (x<0))
			{
				x++;
			}
			if(key[KEY_END] && (x > -difx))
			{
				x--;
			}

		}

		sprites.desenha(x,y);

		if ( (mouse_b & 1) && !ret && !trim )
		{
			ret = true;
			curr.rx1 = curr.rx2 = mouse_x;
			curr.ry1 = curr.ry2 = mouse_y;
		}

		if(ret)
		{
			curr.rx2 = mouse_x;
			curr.ry2 = mouse_y;
			egl_retangulo(curr.rx1,curr.ry1,curr.rx2,curr.ry2,255,255,255);
			if(!(mouse_b & 1)) 
			{
				
				curr_trim = curr;
				trim = true;
				ret = false;
			}
		}

		for(int i =0; i < vr.size(); i++)
			egl_retangulo(vr[i].rx1+x,vr[i].ry1+y,vr[i].rx2+x,vr[i].ry2+y,128,128,128);

		if(trim)
		{
			if(!key[KEY_LCONTROL])
			{
				if(key[KEY_UP]) 
				{
					curr_trim.ry1 -= vel;
					curr_trim.ry2 -= vel;
				}
				if(key[KEY_DOWN]) 
				{
					curr_trim.ry1 += vel;
					curr_trim.ry2 += vel;
				}
				if(key[KEY_LEFT]) 
				{
					curr_trim.rx1 -= vel;
					curr_trim.rx2 -= vel;
				}
				if(key[KEY_RIGHT]) 
				{
					curr_trim.rx1 += vel;
					curr_trim.rx2 += vel;
				}


			}
			else
			{
    			if(!key[KEY_LSHIFT])
				{
					if(key[KEY_UP]) curr_trim.ry1-=vel;
					if(key[KEY_DOWN]) curr_trim.ry2+=vel;
					if(key[KEY_LEFT]) curr_trim.rx1-=vel;
					if(key[KEY_RIGHT]) curr_trim.rx2+=vel;
				}
				else
				{
					if(key[KEY_UP]) curr_trim.ry1+=vel;
					if(key[KEY_DOWN]) curr_trim.ry2-=vel;
					if(key[KEY_LEFT]) curr_trim.rx1+=vel;
					if(key[KEY_RIGHT]) curr_trim.rx2-=vel;
				}
			}

			egl_retangulo(curr_trim.rx1,curr_trim.ry1,curr_trim.rx2,curr_trim.ry2,255,0,0);

			if(key[KEY_ENTER])
			{
				trim = false;

				curr_trim.rx1 -= x;
				curr_trim.rx2 -= x;
				curr_trim.ry1 -= y;
				curr_trim.ry2 -= y;

				vr.push_back(curr_trim);

			}
		}

		if(key[KEY_D] && (!trim) && (!ret) && (vr.size()>0))
		{
			trim = true;
			curr_trim = vr[vr.size()-1];
			curr_trim.rx1 += x;
			curr_trim.rx2 += x;
			curr_trim.ry1 += y;
			curr_trim.ry2 += y;
		}

		if(!deletando && key[KEY_BACKSPACE] && (!trim) && (!ret) && (vr.size()>0))
		{
			deletando = true;
			vr.pop_back();
		}
		if(deletando && !key[KEY_BACKSPACE]) deletando = false;


		if(ret)
		{
			sprintf(texto,"Pos:(%d,%d) Ret(%.0f,%.0f,%.0f,%.0f)",-x,-y,curr.rx1,curr.ry1,curr.rx2-curr.rx1,curr.ry2-curr.ry1);
		}
		else
		{
			if(trim)
			{
				sprintf(texto,"Pos:(%d,%d) Ret(%.0f,%.0f,%.0f,%.0f)",-x,-y,curr_trim.rx1,curr_trim.ry1,curr_trim.rx2-curr_trim.rx1,curr_trim.ry2-curr_trim.ry1);
			}
			else
			{
				sprintf(texto,"Pos:(%d,%d)",-x,-y);
			}
		}
		egl_texto(texto,512,0);

		if(key[KEY_F1]) ajuda.desenha(187,184);

		mouse.desenha(mouse_x,mouse_y);

		egl_desenha_frame();
	}

	egl_finalizar();

	ofstream saida("cortes.txt");
	string nome(argv[1]);
	int pos = nome.find('\\');
	if(pos >=0) nome.insert(pos,"\\");

	for(int i =0; i < vr.size(); i++)
		saida << ".carregar(\"" << nome << "\"," << (int)vr[i].rx1 << "," << (int)vr[i].ry1 << "," << (int)(vr[i].rx2 - vr[i].rx1) << "," << (int)(vr[i].ry2 - vr[i].ry1) << ");" << endl;

	system("notepad cortes.txt");

	return 0;
}
END_OF_MAIN();
