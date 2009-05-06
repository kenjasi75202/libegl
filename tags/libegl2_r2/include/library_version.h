#pragma once
// libegl2: Cabecalho para configuracao automatica das bibliotecas no Visual Studio
#if _MSC_VER >= 1500
   // this is Visual C++ 2008
	#include "..//allegro-msvc80-4.2.2//include//allegro.h"	
	#ifndef _DEBUG
		#pragma message("RELEASE: added libs:alleg,libegl (VS2008+)")
		#pragma comment(lib, "..//egl//allegro-msvc80-4.2.2//lib//alleg.lib")
		#pragma comment(lib, "..//egl//lib//NET2008//libegl.lib")
	#else
		#pragma message("DEBUG: added libs:alleg,libegl_d (VS2008+)")
		#pragma comment(lib, "..//egl//allegro-msvc80-4.2.2//lib//alleg.lib")
		#pragma comment(lib, "..//egl//lib//NET2008//libegl_d.lib")
	#endif	
#elif _MSC_VER >= 1400
   // this is Visual C++ 2005
	#include "..//allegro-msvc80-4.2.2//include//allegro.h"	
	#ifndef _DEBUG
		#pragma message("RELEASE: added libs:alleg,libegl (VS2005)")		
		#pragma comment(lib, "..//egl//allegro-msvc80-4.2.2//lib//alleg.lib")
		#pragma comment(lib, "..//egl//lib//NET2005SP1//libegl.lib")
	#else
		#pragma message("DEBUG: added libs:alleg,libegl_d (VS2005)")
		#pragma comment(lib, "..//egl//allegro-msvc80-4.2.2//lib//alleg.lib")
		#pragma comment(lib, "..//egl//lib//NET2005SP1//libegl_d.lib")
	#endif
#elif _MSC_VER >= 1310
   // this is Visual c++ .NET 2003 com Service Pack 1
	#include "..//allegro-msvc71-4.2.2//include//allegro.h"	
	#ifndef _DEBUG
		#pragma message("RELEASE: added libs:alleg,libegl (VS2003 SP1)")
		#pragma comment(lib, "..//egl//allegro-msvc71-4.2.2//lib//alleg.lib")
		#pragma comment(lib, "..//egl//lib//NET2003SP1//libegl.lib")
	#else
		#pragma message("DEBUG: added libs:alleg,libegl_d (VS2003 SP1)")
		#pragma comment(lib, "..//egl//allegro-msvc71-4.2.2//lib//alleg.lib")
		#pragma comment(lib, "..//egl//lib//NET2003SP1//libegl_d.lib")
	#endif
#else
   // this is Visual C++ .NET 2003 sem Service Pack 1
	#include "..//allegro-msvc70-4.2.2//include//allegro.h"
	#ifndef _DEBUG
		#pragma message("RELEASE: added libs:alleg,libegl (VS2003-)")
		#pragma comment(lib, "..//egl//allegro-msvc70-4.2.2//lib//alleg.lib")
		#pragma comment(lib, "..//egl//lib//NET2003//libegl.lib")
	#else
		#pragma message("DEBUG: added libs:alleg,libegl (VS2003-)")
		#pragma comment(lib, "..//egl//allegro-msvc70-4.2.2//lib//alleg.lib")
		#pragma comment(lib, "..//egl//lib//NET2003//libegl_d.lib")
	#endif

#endif 
