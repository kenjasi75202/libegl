#pragma once
#if _MSC_VER >= 1500
   // this is Visual C++ 2008
	#pragma message("added libs:alleg,libegl (VS2008+)")
	#pragma comment(lib, "..//egl//allegro-msvc80-4.2.2//lib//alleg.lib")
	#pragma comment(lib, "..//egl//lib//libegl.lib")
	#include "allegro-msvc80-4.2.2//include//allegro.h"
#elif _MSC_VER >= 1400
   // this is Visual C++ 2005
	#pragma message("added libs:alleg,libegl (VS2005)")
	#pragma comment(lib, "..//egl//allegro-msvc80-4.2.2//lib//alleg.lib")
	#pragma comment(lib, "..//egl//lib//libegl.lib")
	#include "allegro-msvc80-4.2.2//include//allegro.h"
#elif _MSC_VER >= 1310
   // this is Visual c++ .NET 2003 com Service Pack 1
	#pragma message("added libs:alleg,libegl (VS2003 SP1)")
	#pragma comment(lib, "..//egl//allegro-msvc71-4.2.2//lib//alleg.lib")
	#pragma comment(lib, "..//egl//lib//libegl.lib")
	#include "allegro-msvc71-4.2.2//include//allegro.h"
#else
   // this is Visual C++ .NET 2003 sem Service Pack 1
	#pragma message("added libs:alleg,libegl (VS2003-)")
	#pragma comment(lib, "..//egl//allegro-msvc70-4.2.2//lib//alleg.lib")
	#pragma comment(lib, "..//egl//lib//libegl.lib")
	#include "allegro-msvc70-4.2.2//include//allegro.h"
#endif 
