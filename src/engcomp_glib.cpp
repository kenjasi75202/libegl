#include "engcomp_glib.h"
#include <algorithm>
#include <cctype>

Uint32 rmask, gmask, bmask, amask;

bool egl_init=false;
SDL_Surface* tela=NULL;

SDL_Event eventos;
bool key[323] = {false};

int mouse_x;
int mouse_y;
int mouse_b;

int res_x; 
int res_y;
Uint32 clear_color;
bool egl_debug=false;
string msg_erro;



#include "fonte.h"

bool egl_inicializar(int w, int h, bool janela)
{
	 // SDL interprets each pixel as a 32-bit number, so our masks must depend
     //  on the endianness (byte order) of the machine 
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif

	SDL_Init( SDL_INIT_VIDEO );
	if(!janela)
	{
		tela = SDL_SetVideoMode( w, h, 0, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
	}
	else
	{
		tela = SDL_SetVideoMode( w, h, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
		SDL_WM_SetCaption( "libEGL3", 0 );
	}
	
	res_x = w; res_y = h;

	clear_color = SDL_MapRGB(tela->format, 0, 0, 0);
	SDL_FillRect(tela, NULL, clear_color);

	TTF_Init();

	egl_init = true;
	
	return true;
}

void egl_finalizar()
{
	if(tela) SDL_FreeSurface(tela);
	TTF_Quit();
	SDL_Quit();
}

void  egl_processa_eventos()
{
	if (SDL_PollEvent(&eventos))
	{
		if (eventos.type == SDL_MOUSEMOTION)
		{
			mouse_x = eventos.motion.x;
			mouse_y = eventos.motion.y;
		}

		if (eventos.type == SDL_KEYDOWN)
		{
			key[eventos.key.keysym.sym] = true;
		} 
		if (eventos.type == SDL_KEYUP)
		{
			key[eventos.key.keysym.sym] = false;
		}
	}
}

void egl_desenha_frame(bool limpa, bool sync)
{
	if(!egl_init) return;
    if(egl_debug) egl_texto(msg_erro.c_str(),0,0);

	egl_processa_eventos();

	//if(sync) vsync();
	SDL_Flip(tela);
	if(limpa) 
      SDL_FillRect(tela, NULL, clear_color);
}

void egl_pixel(int x,int y, int vermelho, int verde, int azul)
{
	if(!egl_init) return;

	pixelRGBA(tela,x,y,vermelho,verde,azul,255);
}

void egl_linha(int x1,int y1, int x2,int y2, int vermelho, int verde, int azul)
{
	if(!egl_init) return;

	lineRGBA(tela,x1,y1,x2,y2,vermelho, verde, azul,255);
}

void egl_retangulo(int x1,int y1, int x2,int y2, int vermelho, int verde, int azul)
{
	if(!egl_init) return;

	rectangleRGBA(tela,x1,y1,x2,y2,vermelho, verde, azul,255);
}

void egl_sleep(int milisec)
{
	SDL_Delay(milisec);
}

void egl_erro(string mensagem)
{
	msg_erro += (" " + mensagem);
}

void egl_texto(string txt, int x, int y, int cR, int cG, int cB)
{
	if(!egl_init) return;

	stringRGBA(tela,x,y,txt.c_str(),cR,cG,cB,255);
}


/*

// Adaptada de um exemplo de: Kronoman - Taking a string from keyboard
// BUG: não aceita acentos (perde a sincronia do cursor)
// BUG: no limite maximo do texto ele adiciona 2 chars simultaneos???
// SUGESTÃO: adicionar a possibilidade de passar uma cor como parametro
void read_string(char *str_to, int size, int x, int y)
{
	int cur_pos = 0; // position of caret
	int the_key = 0;
	int i;

	for (i = 0; i < size; i++)
		str_to[i] = '\0'; // 'clean' the string

	// usa o atual frame do jogo como fundo para a edicao de texto
	// desenha linhas de referencia para o texto
	BITMAP* telat;
	telat = create_bitmap(res_x,res_y);
	egl_linha(x,y+8,x+((size-1)*8),y+8,255,255,255);
	egl_linha(x+(cur_pos*8),y+7,x+(cur_pos*8)+8,y+7,255,255,255);
	blit(tela, screen, 0, 0, 0, 0, res_x, res_y);
	
	// limpa o buffer do teclado
	while(keypressed()) readkey();

	while (the_key>>8 != KEY_ENTER)
	{
		the_key = readkey();

		if ((the_key & 0xff) >= ' ') // get only valid chars
		{
			str_to[cur_pos] = the_key & 0xff;
			cur_pos++;
			if (cur_pos > size-2) cur_pos = size-2;

		}

		if (the_key >> 8 == KEY_BACKSPACE)
		{
			cur_pos --;
			if (cur_pos < 0) cur_pos = 0;
			str_to[cur_pos] = '\0'; // chop the string
		}
		
		// desenha no frame atual usando buffer duplo
		// + linha de referencia para o cursor
		blit(tela, telat, 0, 0, 0, 0, res_x, res_y);
		line(telat, x+(cur_pos*8),y+7,x+(cur_pos*8)+8,y+7,makecol(255, 255, 255));
		textout(telat,font, str_to, x,y, makecol(255,255,255));
		blit(telat, screen, 0, 0, 0, 0, res_x, res_y);
	}
	if(telat) destroy_bitmap(telat);
}

// IMPORTANTE: essa função é síncrona !!!!
void egl_ler_string_teclado(string &buffer, int tamanho_buffer, int x, int y)
{
	if(!egl_init) return;

	char *ptr = new char[tamanho_buffer];
	read_string(ptr, tamanho_buffer - 1, x, y);
	buffer = string(ptr);
	delete[] ptr;
}

void egl_cursor(int tipo_cursor)
{
	enable_hardware_cursor();
	select_mouse_cursor(tipo_cursor);
	show_mouse(screen);
}


void egl_cursor(string caminho)
{
	BITMAP *bmp;

	string ext = caminho.substr(caminho.size()-4,caminho.size()-1);
	std::transform(ext.begin(), ext.end(), ext.begin(),static_cast < int(*)(int) > (tolower));
	
	if (ext == ".png")
	{
		bmp = load_png(caminho.c_str(),NULL);
	} else {
		bmp = load_bitmap(caminho.c_str(),NULL);
	}

	set_mouse_sprite(bmp);
	egl_cursor(CURSOR_EGL);
}

*/