#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include "engcomp_glib.h"

using namespace std;

#include "TileEngine.h"

TileMap::TileMap(void)
{
	px = py = 0;
}

TileMap::~TileMap(void)
{
}

bool TileMap::inicializa(string arq)
{
	int delta;
	int tilesX, tilesY;
	int larg, alt;
	string tile_num;
	string nome_arq;
	tile_num = "*";

	ifstream arq_mapa(arq.c_str());
	if(!arq_mapa.is_open()) return false;

	arq_mapa >> tilesX >> tilesY;
	arq_mapa >> larg >> alt;

	delta = iSC->getNumTiles();

	arq_mapa >> tile_num;
	while(arq_mapa >> nome_arq)
	{
		iSC->carregar(nome_arq);
		arq_mapa >> tile_num;
		if(tile_num == "*") break;
	}
	
	if( (tilesX < 1) || (tilesY < 1)) return false;

	mapa.resize(tilesX);
	for(int i = 0; i < tilesX; i++)
		mapa[i].resize(tilesY);

	tx = tilesX; ty = tilesY;
	lx = larg; ly = alt;

	mapaW = tx*lx;
	mapaH = ty*ly;

	int tile_atual;
	for(int y = 0; y < tilesY; y++)
	{
		for(int x = 0; x < tilesX; x++)
		{
			arq_mapa >> tile_atual;
			if(tile_atual >= 0) tile_atual += delta;
			mapa[x][y] = new Tiles();
			mapa[x][y]->setTile(tile_atual,larg,alt);
		}
	}
	
	string sep;
	arq_mapa >> sep;
	if(sep != "*") return false;

	int bw_atual;
	for(int y = 0; y < tilesY; y++)
	{
		for(int x = 0; x < tilesX; x++)
		{
			arq_mapa >> bw_atual;
			mapa[x][y]->setWalk((bool)bw_atual);
		}
	}

	arq_mapa >> sep;
	if(sep != "*") return false;
	
	for(int y = 0; y < tilesY; y++)
	{
		for(int x = 0; x < tilesX; x++)
		{
			arq_mapa >> bw_atual;
			mapa[x][y]->setInfo(bw_atual);
		}
	}

	return true;
}

void TileMap::desenha()
{
	int wx, wy;
	wx = px;
	wy = py;
	for(int y = 0; y < ty; y++, wy+=ly)
	{
		if( (wy>-ly) && (wy<(res_y+ly)) )
			for(int x = 0; x < tx; x++, wx+=lx)
			{
				if( (wx>-lx) && (wx<(res_x+lx)) )
					iSC->desenhar(mapa[x][y]->getTileN(),wx,wy);
			}
		wx = px;
	}
}

void TileMap::setPos(int _x, int _y)
{
	px = _x;
	py = _y;
}
void TileMap::move(int dx, int dy)
{
	px += dx;
	py += dy;
}
int TileMap::dX() // deslocamento em relacao a tela
{
	return px;
}
int TileMap::dY()
{
	return py;
}
int TileMap::getW()
{
	return mapaW;
}
int TileMap::getH()
{
	return mapaH;
}
void TileMap::screen2map(int x, int y, int& mx, int& my)
{
	mx = x-px;
	my = y-py;
}
void TileMap::map2screen(int x, int y, int& mx, int& my)
{
	mx = x+px;
	my = y+py;
}

int TileMap::XparaTela(int mx)
{
	return mx+px;
}

int TileMap::YparaTela(int my)
{
	return my+py;
}

bool TileMap::pointColTile(int x,int y, int& cx, int& cy)
{
	if( (x<0) || (y<0) ) return false;
	if( (x >= tx*lx) || (y >= ty*ly) ) return false;
	cx = x/lx;
	cy = y/ly;
	return true;
}
void TileMap::drawTileBorder(int x, int y, int vermelho, int verde, int azul)
{
	int x1,x2,y1,y2;
	x1 = (x*lx)+px; x2 = (x1+lx);
	y1 = (y*ly)+py; y2 = (y1+ly);

	egl_linha(x1,y1,x2,y1,vermelho,verde,azul);
	egl_linha(x2,y1,x2,y2,vermelho,verde,azul);
	egl_linha(x2,y2,x1,y2,vermelho,verde,azul);
	egl_linha(x1,y2,x1,y1,vermelho,verde,azul);
}

// colide: somente para sprites menores que os tiles
bool TileMap::colide(int x, int y, int w, int h)
{
	int tilx, tily;
	if(pointColTile(x,y,tilx,tily) )
	{
		if(!(mapa[tilx][tily]->getWalk())) return true;
	}
	if(pointColTile(x+w,y,tilx,tily) )
	{
		if(!(mapa[tilx][tily]->getWalk())) return true;
	}
	if(pointColTile(x,y+h,tilx,tily) )
	{
		if(!(mapa[tilx][tily]->getWalk())) return true;
	}
	if(pointColTile(x+w,y+h,tilx,tily) )
	{
		if(!(mapa[tilx][tily]->getWalk())) return true;
	}

	return false;
}

//TODO: BUG se o mapa de colisao for maior que o tile
//TODO: bug com pngs transparentes
bool TileMap::colidePP(int x, int y, int w, int h, imagem* img) // Colide Pixel-a-Pixel
{
	imagem* img_tile;

	int tilx, tily;
	if(pointColTile(x,y,tilx,tily) )
	{
		if(!(mapa[tilx][tily]->getWalk()))
		{
			img_tile = iSC->getImagem(mapa[tilx][tily]->getTileN());
			if(img->colide(x,y,tilx*lx,tily*ly,*img_tile)) 
				return true;
		}
	}
	if(pointColTile(x+w,y,tilx,tily) )
	{
		if(!(mapa[tilx][tily]->getWalk())) 
		{
			img_tile = iSC->getImagem(mapa[tilx][tily]->getTileN());
			if(img->colide(x,y,tilx*lx,tily*ly,*img_tile)) 
				return true;
		}
	}
	if(pointColTile(x,y+h,tilx,tily) )
	{
		if(!(mapa[tilx][tily]->getWalk())) 
		{
			img_tile = iSC->getImagem(mapa[tilx][tily]->getTileN());
			if(img->colide(x,y,tilx*lx,tily*ly,*img_tile)) 
				return true;
		}
	}
	if(pointColTile(x+w,y+h,tilx,tily) )
	{
		if(!(mapa[tilx][tily]->getWalk())) 
		{
			img_tile = iSC->getImagem(mapa[tilx][tily]->getTileN());
			if(img->colide(x,y,tilx*lx,tily*ly,*img_tile)) 
				return true;
		}
	}


	return false;
}