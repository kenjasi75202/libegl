#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <math.h>
#include "engcomp_glib.h"

using namespace std;

#include "TileEngine.h"

TileMap::TileMap(void)
{
	px = py = 0;
	path = false;
	cutcor = false;
	movdiag = true;
	hr = HR_MANHATTAN;

	C = 10;
	CD = 14; // sqrt(2) * C
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
			mapa[x][y]->posx = x;
			mapa[x][y]->posy = y;
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
				{
					iSC->desenhar(mapa[x][y]->getTileN(),wx,wy);
				}
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

Tiles* TileMap::getTile(int _x, int _y)
{
	return mapa[_x][_y];
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

//////////////////////////
// ASTAR
//////////////////////////

void TileMap::desenhaClosed()
{
	int wx, wy;
	wx = px;
	wy = py;
	char txt[32];
	for(int y = 0; y < ty; y++, wy+=ly)
	{
		if( (wy>-ly) && (wy<(res_y+ly)) )
			for(int x = 0; x < tx; x++, wx+=lx)
			{
				if( (wx>-lx) && (wx<(res_x+lx)) )
				{
					if( (mapa[x][y]->inClosed) || (mapa[x][y]->inOpen) )
					{
						drawTileBorder(x,y);
						_itoa_s(mapa[x][y]->F,txt,10);
						egl_texto(txt,wx+2,wy+2);
						_itoa_s(mapa[x][y]->G,txt,10);
						egl_texto(txt,wx+2,wy+11);
						_itoa_s(mapa[x][y]->H,txt,10);
						egl_texto(txt,wx+2,wy+21);
					}
				}
			}
		wx = px;
	}
}

int TileMap::Heuristica(int ix,int iy,int fx,int fy)
{
	switch(hr)
	{
		default:
		case HR_MANHATTAN :  
			return ( C * (abs(ix-fx) + abs(iy-fy)) );
		case HR_EUCLIDEAN : 
			return ( C * sqrt(pow(ix-fx,2.0) + pow(iy-fy,2.0)) );
		case HR_DIAGONAL:
		{
			int h_diagonal = min(abs(ix-fx), abs(iy-fy));
			int h_straight = (abs(ix-fx) + abs(iy-fy));
			return CD * h_diagonal + C * (h_straight - 2*h_diagonal);
		}
		case HR_CROSS:
		{
			int heu = C * (abs(ix-fx) + abs(iy-fy));
			int cross = abs((ix - fx)*(sy - fy) - (sx - fx)*(iy - fy));
			return (heu + cross)/2.0;
		}
	}
}

Tiles* TileMap::MenorF()
{
	if(open.empty()) return NULL; 

	int mF;
	Tiles* mT = NULL;
	list<Tiles*>::iterator mit;
	list<Tiles*>::iterator it;
	it = open.begin();
	
	mF = (*it)->F;
	mT = (*it);
	mit = it;
	it++;
	
	while(it != open.end())
	{
		if( (*it)->F < mF)
		{
			mF = (*it)->F;
			mT = (*it);
			mit = it;
		}
		it++;
	}
	open.erase(mit);
	mT->inOpen = false;

	closed.push_back(mT);
	mT->inClosed = true;
	
	if( (mT->posx == gx) && (mT->posy == gy) ) path = true;
	return mT;
}

// Evita Cortar por Cantos fechados : se move na diagonal E possui alguma adjacente nas paralelas
// ax,ay = origem
// bx,by = destino
bool TileMap::CutCorner(int ax, int ay, int bx, int by)
{
	if(cutcor) return false;

	if (bx == ax-1) 
	{
		if (by == ay-1)
		{
			
			if (mapa[ax-1][ay]->walkable == false || mapa[ax][ay-1]->walkable == false)
				return true;
		}
		else 
			if (by == ay+1)
			{
				if (mapa[ax][ay+1]->walkable == false || mapa[ax-1][ay]->walkable == false) 
					return true;
			}
	}
	else 
		if (bx == ax+1)
		{
			if (by == ay-1)
			{
				if (mapa[ax][ay-1]->walkable == false || mapa[ax+1][ay]->walkable == false) 
					return true;
			}
			else 
				if (by == ay+1)
				{
					if (mapa[ax+1][ay]->walkable == false || mapa[ax][ay+1]->walkable == false)
						return true;
				}
		}	
	return false;
}

void TileMap::ProcessaAdjacente(int adx, int ady, int G, Tiles* atual)
{
	Tiles* adT;

	if( (adx>=0) && (adx<tx) && (ady>=0) && (ady<ty))
	{
		if( !CutCorner(atual->getX(),atual->getY(),adx,ady) )
		{
			adT = mapa[adx][ady];
			G = G + atual->G;
			if( adT->walkable && !(adT->inClosed))
			{
				if(!adT->inOpen)
				{
					adT->anterior = atual;
					adT->G = G;
					adT->H = Heuristica(adx,ady,gx,gy);
					adT->F = adT->H + G;
					adT->inOpen = true;
					open.push_back(adT);
				}
				else
				{
					if( G < adT->G)
					{
						adT->anterior = atual;
						adT->G = G;				
						adT->F = adT->H + G;
					}
				}
			}
		}
	}

}

void TileMap::Adjacentes(Tiles* atual)
{
	int adx,ady,G;
	int ax = atual->posx;
	int ay = atual->posy;
	
	// G: custo do movimento
	//  10 = movimento normal - C
	//  14 = movimento diagonal - CD

	adx = ax; ady = ay-1; G = C;
	ProcessaAdjacente(adx,ady,G,atual);

	adx = ax+1; ady = ay; G = C;
	ProcessaAdjacente(adx,ady,G,atual);
	
	adx = ax; ady = ay+1; G = C;
	ProcessaAdjacente(adx,ady,G,atual);
	
	adx = ax-1; ady = ay; G = C;
	ProcessaAdjacente(adx,ady,G,atual);

	if(movdiag)
	{
		adx = ax-1; ady = ay-1; G = CD;
		ProcessaAdjacente(adx,ady,G,atual);
		
		adx = ax+1; ady = ay-1; G = CD;
		ProcessaAdjacente(adx,ady,G,atual);

		adx = ax+1; ady = ay+1; G = CD;
		ProcessaAdjacente(adx,ady,G,atual);
		
		adx = ax-1; ady = ay+1; G = CD;
		ProcessaAdjacente(adx,ady,G,atual);
	}
}

bool TileMap::Passo()
{
	Tiles* atual;

	// acha o menor F e retira da lista de open, colocando na lista de closed
	atual = MenorF();
	if( (!path) && (atual) )
	{
		Adjacentes(atual);
		return false;
	}
	else
		return true;
}

void TileMap::LimpaCaminho()
{
	list<Tiles*>::iterator it;

	it = closed.begin();
	while(it != closed.end())
	{
		(*it)->inClosed = false;
		it++;
	}

	it = open.begin();
	while(it != open.end())
	{
		(*it)->inOpen = false;
		it++;
	}

	path = false;
	closed.clear();
	open.clear();
}

// ix,iy = inicio
// fx,fy = destino
bool TileMap::CalculaCaminho(int ix,int iy,int fx,int fy)
{
	// valida posicoes de inicio e fim
	if( (ix < 0) || (ix >= tx) ) return false; if( (iy < 0) || (iy >= ty) ) return false;
	if( (fx < 0) || (fx >= tx) ) return false; if( (fy < 0) || (fy >= ty) ) return false;

	// inicializa as estruturas de dados
	LimpaCaminho();

	// seta o inicio;
	sx = ix; sy = iy;

	// seta o destino
	gx = fx; gy = fy;
	

	// se o inicio não for walkable não existe caminho. retorna imediatamente
	if( !(mapa[ix][iy]->walkable) ) return path;

	// inicia a procura a partir do inicio
	mapa[ix][iy]->anterior = NULL;
	mapa[ix][iy]->G = 0;
	mapa[ix][iy]->H = Heuristica(ix,iy,fx,fy);
	mapa[ix][iy]->F = mapa[ix][iy]->H;
	mapa[ix][iy]->inOpen = true;
	open.push_back(mapa[ix][iy]);

	// executa a busca, passo a passo
	while(!Passo())
	{
		if(open.empty()) return false;
	}

	return path;
}

// retorna um vetor com os tiles que fazem parte do caminho
vector<Tiles*> TileMap::GetCaminho()
{
	vector<Tiles*> cam;

	if(path)
	{
		// faz um traceback do destino até o inicio, usando o ponteiro do anterior
		Tiles* atual = mapa[gx][gy];
		while(atual)
		{
			cam.push_back(atual);
			atual = atual->anterior;
		}
	}

	return cam;
}

void TileMap::setASTarOptions(int heuristic, bool cutcorner,bool move_diag)
{
	hr = heuristic;
	cutcor = cutcorner;
	movdiag = move_diag;
}