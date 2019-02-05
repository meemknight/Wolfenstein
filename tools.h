//////////////////////////////////////////////
/// define FORCE_LOG
///to controll the behavour of the log or just 
///change from debug to releasee
///Copyright (c) 2019 Luta Vlad
//////////////////////////////////////////////
#pragma once
#include <iostream>
#include <Windows.h>

#ifdef _DEBUG
#define FORCE_LOG
#endif

#ifdef FORCE_LOG
inline void llog()
{
	std::cout << "\n";
}

template<class F, class ...T>
inline void llog(F f, T ...args)
{
	std::cout << f << " ";
	llog(args...);
}
#else
template<class F, class ...T>
inline void llog(F f, T ...args)
{

}

inline void llog()
{
}
#endif

inline void pause();

#ifdef FORCE_LOG

#define MAIN  main()
inline void pause() { std::cin.get(); }

#else

#define MAIN WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
inline void pause() { }


#endif // FORCE_LOG


