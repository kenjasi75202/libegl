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
	bool inOpen;
	bool inClosed;
	int posx;
	int posy;

public:
	Tiles(void);
	~Tiles(void);
	void setTile(int num_tile, int largura, int altura);
	void setWalk(bool bw);
	void setInfo(int inf);
	bool getWalk();
	int getTileN();

	int getX();
	int getY();

	friend class TileMap;
};

// Heuristicas implementadas
#define HR_MANHATTAN 0 // padrão
#define HR_EUCLIDEAN 1 // usando distancia euclideana
#define HR_DIAGONAL  2 // favorece as diagonais
#define HR_CROSS     4 // gera caminhos mais lineares ate o destino

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
	void desenha_minimapa(int _x, int _y);
	void setPos(int _x, int _y);
	void move(int dx, int dy);
	int dX();
	int dY();
	int getW();
	int getH();
	Tiles* getTile(int _x, int _y);

	void screen2map(int x, int y, int& mx, int& my);
	void map2screen(int x, int y, int& mx, int& my);
	int XparaTela(int mx);
	int YparaTela(int my);
	bool pointColTile(int x,int y, int& cx, int& cy);
	void drawTileBorder(int x, int y, int vermelho=255, int verde=255, int azul=255);

	bool colide(int x, int y, int w, int h);
	bool colidePP(int x, int y, int w, int h, imagem* img);

// AStar
private:
	bool path;
	bool cutcor;
	bool movdiag;
	int hr;
	int gx,gy; // destino
	int sx,sy; // origem
	list<Tiles*> open;
	list<Tiles*> closed;
	int C; // custo
	int CD; // custo diagonal

	int Heuristica(int ix,int iy,int fx,int fy);
	bool Passo();
	Tiles* MenorF();
	void Adjacentes(Tiles* atual);
	void ProcessaAdjacente(int adx, int ady, int G, Tiles* atual);
	bool CutCorner(int ax, int ay, int bx, int by);
	void LimpaCaminho();
	
public:
	void setASTarOptions(int heuristic, bool cutcorner=false, bool move_diag=true);
	void desenhaClosed();
	bool CalculaCaminho(int ix,int iy,int fx,int fy);
	vector<Tiles*> GetCaminho();
};

