#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <cstdlib>
#include <ctime>
#include "sstream"
#include <cmath>
#include <fstream>
using namespace std;
int main (int argc, char * args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_surface* map = NULL;
	SDL_surface* screen= NULL;
	screen = SDL_SetvideoMode (640, 480, 32, SDL_SWSURFACE);
	map = SDL_IMGLoad ("plane-wars.jpg");
	
}