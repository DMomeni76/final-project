#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <SDL/SDL_mixer.h>
#include <cstdlib>
#include <ctime>
#include "sstream"
#include <cmath>
#include <fstream>
#include <string>
using namespace std;
int main(int argc, char * args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Surface* screen= NULL;
	screen = SDL_SetVideoMode (1280, 720, 32, SDL_SWSURFACE);
	SDL_Surface* menu[3];
	menu[0]=IMG_Load ("menu1.png");
	menu[1]=IMG_Load ("menu2.png");
	menu[2]=IMG_Load ("menu3.png");
	Mix_Music* menu_music=NULL;
	Mix_Chunk* selection_sound=NULL;
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
	menu_music=Mix_LoadMUS ("menu_music.mp3");
	selection_sound=Mix_LoadWAV ("selection_sound.wav");
	Mix_PlayMusic (menu_music,-1);
	bool menu_run =true;
	SDL_Surface* quit_no=NULL;
	SDL_Surface* quit_yes= NULL;
	quit_no=IMG_Load ("game_images/quitno.png");
	quit_yes=IMG_Load ("game_images/quityes.png");
	while (menu_run)
	{
		SDL_Event event;
		if(SDL_PollEvent(&event))
		{
			if (event.type==SDL_QUIT)
			{
				SDL_FreeSurface(screen);
				menu_run=false;
			}
			if (event.type==SDL_MOUSEMOTION)
			{
				if (event.button.x>250 && event.button.x<1000 && event.button.y>210 && event.button.y<408)
				{

                    SDL_BlitSurface (quit_no,NULL, screen, NULL);
				}
				if (event.button.x>250 && event.button.x<1000 && event.button.y>408 && event.button.y<610)
				{
                    SDL_BlitSurface (quit_yes,NULL, screen, NULL);
				}
			}
			/*if (event.type==SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button==SDL_BUTTON_LEFT)
                {

                }
            }*/
		}
	SDL_Flip (screen);
	SDL_Delay (1);
	}
	Mix_FreeChunk (selection_sound);
	Mix_FreeMusic (menu_music);
	Mix_CloseAudio();
	SDL_Quit();
	return 0;
}
