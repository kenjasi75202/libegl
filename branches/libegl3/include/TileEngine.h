#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Macro com um alias para a instancia do singleton. </summary>
///
/// <remarks>	Tulio, 24/05/2010. </remarks>
///
/// <returns>	. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////

// macro com um alias para a instancia do singleton
#define iSC TileCache::instance()

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Classe singleton para retornar uma referência para um Tile. </summary>
///
/// <remarks>	Tulio, 24/05/2010. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Class Tiles represent each tile in map.  </summary>
///
/// <remarks>	Tulio, 24/05/2010. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////

class Tiles
{
private:
	/// <summary> Largura do tile.</summary>
	int lar;
	/// <summary> Altura do tile. </summary>
	int alt; 
	/// <summary> Posicao do sprite no cache.  </summary>
	int sprite;
	
	/// AStar info. 
	/// <summary> .  </summary>
	int info;
	/// <summary> .  </summary>
	int cost;
	/// <summary> Define se tile é transponível.  </summary>
	bool walkable;
	/// <summary> Tile anterior.  </summary>
	Tiles* anterior;
	/// <summary> Custo total do tile.  </summary>
	int F;
	/// <summary> Custo do deslocamento através tile.  </summary>
	int G;
	/// <summary> Custo do movimento pela heurística.  </summary>
	int H;
	/// <summary> Tile está na lista de abertos.  </summary>
	bool inOpen;
	/// <summary> Tile está na lista de fechados.  </summary>
	bool inClosed;
	/// <summary> Posição x do tile no mapa.  </summary>
	int posx;
	/// <summary> Posição y do tile no mapa.  </summary>
	int posy;
public:
	Tiles(void);
	~Tiles(void);
	void setTile(int num_tile, int largura, int altura);
	void setWalk(bool bw);
	void setInfo(int inf);
	int getInfo();
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

