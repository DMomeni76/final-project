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
void initialization (int row[],int column[]);
void show(SDL_Surface* screen, int cloud_speed);
void event_handel (SDL_Surface* screen);
struct base_struct
{
	char type;
	int x;
	int y;
	int w;
	int h;
	bool select;
}base[11];
struct cloud_struct
{
	int x;
	int y;
}cloud[3];
int main (int argc, char * args[])
{
	srand(time(0));
	SDL_Init(SDL_INIT_EVERYTHING);
	int column[5]={88,344,600,856,1112};
	int row[3]={100,340,580};
	SDL_Surface* screen= NULL;
	screen = SDL_SetVideoMode (1280, 720, 32, SDL_SWSURFACE);
	SDL_Surface* background = NULL;
	SDL_Surface* myplane =NULL;
	SDL_Surface* foeplane =NULL;
	SDL_Surface* boom =NULL;
	SDL_Surface* planeshadow=NULL;
	background=SDL_LoadBMP ("map1.bmp");
	cloud[0].x=500;
	cloud[1].x=40;
	cloud[2].x=1000;
	cloud[0].y=50;
	cloud[1].y=220;
	cloud[2].y=450;
	int cloud_speed=1;
	initialization (row,column);
	while (true)
	{
		SDL_BlitSurface(background, NULL, screen, NULL );
		event_handel (screen);
		show (screen,cloud_speed);
		
		SDL_Flip(screen);
		SDL_Delay (2);
	}
	return 0;
}
void initialization (int row[],int column[])
{
	int basecount;
	basecount=rand()%4 + 1;
	int emptybase;
	if (basecount<=2)
	{
		emptybase=2;
	}
	else
	{
		emptybase=3;
	}
	int counter=0;
	int ibase;
	int jbase;
	int basechack[3][5];
	for (int i=0;i<3;i++)
	{
		for (int j=0;j<5;j++)
		{
			basechack[i][j]=0;
		}
	}
	while(counter<2*basecount+emptybase)
	{
		while(true)
		{
			ibase=rand()%3;
			jbase=rand()%5;
			if (basechack[ibase][jbase]==0)
			{
				basechack[ibase][jbase]=1;
				break;
			}
		}
		if (counter<emptybase)
		{
			base[counter].type='e';
			base[counter].x=column[jbase];
			base[counter].y=row[ibase];
			base[counter].w=73;
			base[counter].h=82;
			base[counter].select=false;
		}
		else
		{
			if (counter<basecount+emptybase)
			{
				base[counter].type='m';
				base[counter].x=column[jbase];
				base[counter].y=row[ibase];
				base[counter].w=85;
                base[counter].h=89;
                base[counter].select=false;
			}
			else
			{
				base[counter].type='f';
				base[counter].x=column[jbase];
				base[counter].y=row[ibase];
				base[counter].w=76;
                base[counter].h=85;
                base[counter].select=false;
			}
		}
		counter++;
	}

}
void show(SDL_Surface* screen, int cloud_speed)
{
	SDL_Surface* mybase =NULL;
	SDL_Surface* emptybase =NULL;
	SDL_Surface* foebase =NULL;
	SDL_Surface* baseshadow =NULL;
	SDL_Surface* Cloud=NULL;
	SDL_Surface* cloudshadow =NULL;
	SDL_Surface* mybase_select=NULL;
	SDL_Surface* foebase_select=NULL;
	SDL_Surface* emptybase_select=NULL;
	mybase= IMG_Load ("mybase.png");
	foebase= IMG_Load ("foebase.png");
	emptybase= IMG_Load ("emptybase.png");
	mybase_select=IMG_Load ("mybase select.png");
	foebase_select=IMG_Load ("foebase select.png");
	emptybase_select=IMG_Load ("emptybase select.png");
	baseshadow=IMG_Load ("baseshadow.png");
	Cloud=IMG_Load ("cloud.png");
	cloudshadow=IMG_Load("cloudshadow.png");
	SDL_Rect mybase_cords;
	SDL_Rect foebase_cords;
	SDL_Rect emptybase_cords;
	SDL_Rect baseshadow_cords;
	SDL_Rect cloud_cords;
	SDL_Rect cloudshadow_cords;
	for (int i=0;i<11;i++)
	{
		if (base[i].type=='m')
		{
			mybase_cords.x=base[i].x;
			mybase_cords.y=base[i].y;
			baseshadow_cords.x=base[i].x-30;
			baseshadow_cords.y=base[i].y+40;
			SDL_BlitSurface (baseshadow, NULL, screen, &baseshadow_cords);
			if (base[i].select)
			{
			SDL_BlitSurface( mybase_select, NULL, screen, &mybase_cords);	
			}
			else 
			{
				SDL_BlitSurface( mybase, NULL, screen, &mybase_cords);
			}	
		}
		if (base[i].type=='f')
		{
			foebase_cords.x=base[i].x;
			foebase_cords.y=base[i].y;
			baseshadow_cords.x=base[i].x-30;
			baseshadow_cords.y=base[i].y+40;
			SDL_BlitSurface (baseshadow, NULL, screen, &baseshadow_cords);
			if (base[i].select)
			{
			SDL_BlitSurface( foebase_select, NULL, screen, &foebase_cords);	
			}
			else 
			{
				SDL_BlitSurface( foebase, NULL, screen, &foebase_cords);
			}	
		}
		if (base[i].type=='e')
		{
			emptybase_cords.x=base[i].x;
			emptybase_cords.y=base[i].y;
			baseshadow_cords.x=base[i].x-30;
			baseshadow_cords.y=base[i].y+40;
			SDL_BlitSurface (baseshadow, NULL, screen, &baseshadow_cords);
			if (base[i].select)
			{
				SDL_BlitSurface( emptybase_select, NULL, screen, &emptybase_cords);
			}
			else 
			{
				SDL_BlitSurface( emptybase, NULL, screen, &emptybase_cords);
			}	
		}
	}
	for (int i=0;i<3;i++)
	{
		cloud[i].x+=cloud_speed;
		if (cloud[i].x>=1380)
		{
			cloud[i].x=-100;
		}
		cloud_cords.x=cloud[i].x;
		cloud_cords.y=cloud[i].y;
		cloudshadow_cords.x=cloud[i].x-30;
		cloudshadow_cords.y=cloud[i].y+40;
		SDL_BlitSurface (Cloud, NULL, screen, &cloud_cords);
		SDL_BlitSurface (cloudshadow, NULL, screen, &cloudshadow_cords);
	}
}
void event_handel (SDL_Surface* screen)
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
		{
			if (event.type==SDL_QUIT)
			{
				SDL_FreeSurface(screen);
				SDL_Quit();
			}
			if (event.type==SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button==SDL_BUTTON_LEFT)
				{
                    for (int i=0;i<11;i++)
                    {
                        if (event.button.x>base[i].x && event.button.x<base[i].x+base[i].w)
                        {
                            if (event.button.y>base[i].y && event.button.y<base[i].y+base[i].h)
                            {
                                if (base[i].type=='m')
                                {
                                	if (base[i].select) base[i].select=false;
                                	else base[i].select=true;
                            	}
                            }
                        }
                    }
				}
			}
		}
	if (event.type==SDL_MOUSEMOTION)
	{
        for (int i=0;i<11;i++)
       {
            if (event.button.x>base[i].x && event.button.x<base[i].x+base[i].w)
            {
                if (event.button.y>base[i].y && event.button.y<base[i].y+base[i].h)
                {
                	if (base[i].type!='m')
                	{
                    	base[i].select=true;
                    }	
                }
                else if (base[i].type!='m')
            	{	
            		base[i].select=false;
            	}
            }
            else if (base[i].type!='m')
            {	
            	base[i].select=false;
            }
        }
	}
}
