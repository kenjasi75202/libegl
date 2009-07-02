#pragma once
// libegl3: Cabecalho para configuracao automatica das bibliotecas no Visual Studio
#if _MSC_VER >= 1500
   // this is Visual C++ 2008
	#include "SDL.h"
	#include "SDL_image.h"
	#include "SDL_ttf.h"
	#include "SDL_draw.h"
	#ifndef _DEBUG
		#pragma message("RELEASE: added libs: sdl.lib sdlmain.lib sdl_image.lib (VS2008+)")
		#pragma comment(lib, "..//egl3//SDL//lib//sdl.lib")
		#pragma comment(lib, "..//egl3//SDL//lib//sdlmain.lib")
		#pragma comment(lib, "..//egl3//SDL//lib//sdl_image.lib")
		#pragma comment(lib, "..//egl3//SDL//lib//sdl_ttf.lib")
		#pragma comment(lib, "..//egl3//SDL//lib//sdl_draw.lib")
		#pragma comment(lib, "..//egl3//lib//NET2008//libegl.lib")
	#else
		#pragma message("DEBUG: added libs: sdl.lib sdlmain.lib sdl_image.lib (VS2008+)")
		#pragma comment(lib, "..//egl3//SDL//lib//sdl.lib")
		#pragma comment(lib, "..//egl3//SDL//lib//sdlmain.lib")
		#pragma comment(lib, "..//egl3//SDL//lib//sdl_image.lib")
		#pragma comment(lib, "..//egl3//SDL//lib//sdl_ttf.lib")
		#pragma comment(lib, "..//egl3//SDL//lib//sdl_draw.lib")
		#pragma comment(lib, "..//egl3//lib//NET2008//libegl_d.lib")
	#endif	
#else
	#pragma message("ERRO: Versão do Visual Studio sem suporte automático! ")
#endif 
