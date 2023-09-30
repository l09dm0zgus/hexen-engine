//
// Created by cx9ps3 on 22.12.22.
//
#ifndef __ANDROID__
	#define main main
#else
	#define main SDL_main
#endif

#include "application/Application.hpp"

extern "C" __attribute__((visibility("default"))) int main(int argc, char **argv)
{
	hexen::client::Application application;
	application.run();
	return (0);
}