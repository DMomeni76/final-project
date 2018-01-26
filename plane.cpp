#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include <cstdlib>
#include <ctime>
#include "sstream"
#include <cmath>
#include <fstream>
#include <string>
using namespace std;
int main (int argc, char * args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* screen= NULL;
	screen = SDL_SetVideoMode (1280, 720, 32, SDL_SWSURFACE);
	SDL_Surface* background = NULL;
	SDL_Surface* myplane =NULL;
	SDL_Surface* mybase =NULL;
	SDL_Rect  myplane_cords;
	myplane_cords.x=700;
	myplane_cords.y=50;
	background =IMG_Load ("map1.png");
	myplane= IMG_Load ("myplane.png");
	mybase= IMG_Load ("mybase.png");
	SDL_BlitSurface( background, NULL, screen, NULL );
	SDL_BlitSurface( mybase, NULL, screen, NULL );
	SDL_BlitSurface (myplane, NULL, screen, &myplane_cords);
	SDL_Flip(screen);
	SDL_Delay(8000);
	SDL_FreeSurface (background);
	SDL_Quit();
	return 0;
}