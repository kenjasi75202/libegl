
#include "engcomp_glib.h"

 bool egl_init=false;
 BITMAP *tela=NULL;

 int res_x; 
 int res_y;
 bool egl_debug=false;
 string msg_erro;

bool egl_inicializar(int w, int h, bool janela)
{
	allegro_init();

	install_keyboard();
	install_mouse();
	install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);

	set_color_depth(32);
	
	set_gfx_mode(janela ? GFX_DIRECTX_WIN : GFX_AUTODETECT ,w,h,0,0);
	res_x = w; res_y = h;

	tela = create_bitmap(res_x,res_y);
	clear(tela);

	egl_init = true;
	return true;
}

void egl_finalizar()
{
	if(tela) destroy_bitmap(tela);
}

void egl_desenha_frame(bool limpa, bool sync)
{
	if(!egl_init) return;
    if(egl_debug) textout_ex(tela,font,msg_erro.c_str(),0,0,makecol(255,255,255),-1);

	if(sync) vsync();
	blit(tela, screen, 0, 0, 0, 0, res_x, res_y);
	if(limpa) 
      clear(tela);
}

void egl_texto(string txt, int x, int y, int cR, int cG, int cB)
{
	if(!egl_init) return;
 	textout_ex(tela,font,txt.c_str(),x,y,makecol(cR,cG,cB),-1);
}

void egl_sleep(int milisec)
{
	rest(milisec);
}

void egl_pixel(int x,int y, int vermelho, int verde, int azul)
{
	if(!egl_init) return;
	putpixel(tela,x,y,makecol(vermelho, verde, azul));
}

void egl_linha(int x1,int y1, int x2,int y2, int vermelho, int verde, int azul)
{
	if(!egl_init) return;
	line(tela, x1,y1,x2,y2,makecol(vermelho, verde, azul));
}

void egl_retangulo(int x1,int y1, int x2,int y2, int vermelho, int verde, int azul)
{
	if(!egl_init) return;

	int cor = makecol(vermelho, verde, azul);
	line(tela, x1,y1,x2,y1,cor);
	line(tela, x2,y1,x2,y2,cor);
	line(tela, x2,y2,x1,y2,cor);
	line(tela, x1,y2,x1,y1,cor);
}

void egl_erro(string mensagem)
{
	msg_erro += (" " + mensagem);
}

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

	

