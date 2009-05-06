#pragma once

// macro com um alias para a instancia do singleton
#define iSC TileCache::instance()

class TileCache
{
public:
	void desenhar(int index,int x, int y);
	int carregar(string arquivo);
	int localizar(string arquivo);
	imagem* getImagem(int index);
	int getNumTiles();

// Singleton
	static TileCache* instance();
	static void destruir();

private:
	static TileCache* inst;
	vector<imagem*> vetor;
	vector<string> mapa;
	
	TileCache();
	~TileCache();
};

class Tiles
{
private:
	int lar,alt; // largura, altura
	int sprite; // posicao do sprite no cache 
	
	// AStar info
	int info;
	int cost;
	bool walkable;
	Tiles* anterior;
	int F,G,H;

public:
	Tiles(void);
	~Tiles(void);
	void setTile(int num_tile, int largura, int altura);
	void setWalk(bool bw);
	void setInfo(int inf);
	bool getWalk();
	int getTileN();
};

class TileMap
{
private:
	vector<vector<Tiles*> > mapa;
	string arquivo;

	int tx,ty;  // largura e altura em num. de tiles
	int lx,ly;  // tamanho de cada tile (32x32, 64x64, etc.)
	int px, py; // posicao do mapa em relacao a tela

	int mapaW, mapaH; // largura e altura do mapa em pixels

public:
	TileMap(void);
	~TileMap(void);
	bool inicializa(string arq);
	void desenha();
	void setPos(int _x, int _y);
	void move(int dx, int dy);
	int dX();
	int dY();
	int getW();
	int getH();

	void screen2map(int x, int y, int& mx, int& my);
	void map2screen(int x, int y, int& mx, int& my);
	int XparaTela(int mx);
	int YparaTela(int my);
	bool pointColTile(int x,int y, int& cx, int& cy);
	void drawTileBorder(int x, int y, int vermelho=255, int verde=255, int azul=255);

	bool colide(int x, int y, int w, int h);
	bool colidePP(int x, int y, int w, int h, imagem* img);

};

