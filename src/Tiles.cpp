#include <iostream>
#include <string>
#include <sstream>
#include "engcomp_glib.h"

using namespace std;

#include "TileEngine.h"

Tiles::Tiles(void)
{
	inOpen = false;
	inClosed = false;
	cost = 0;
}

Tiles::~Tiles(void)
{
}

void Tiles::setTile(int num_tile, int largura, int altura)
{
	sprite = num_tile;
	lar = largura;
	alt = altura;
}

void Tiles::setWalk(bool bw)
{
	walkable = bw;
}

void Tiles::setInfo(int inf)
{
	info = inf;
}

bool Tiles::getWalk()
{
	return walkable;
}

int Tiles::getTileN()
{
	return sprite;
}

int Tiles::getX()
{
	return posx;
}
int Tiles::getY()
{
	return posy;
}