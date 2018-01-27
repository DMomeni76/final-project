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
void show(SDL_Surface* screen);
struct base_struct
{
	char type;
	int x;
	int y;
}base[11];

int main (int argc, char * args[])
{
	srand(time(0));
	SDL_Init(SDL_INIT_EVERYTHING);

	int column[5]={88,344,600,856,1112};
	int row[3]={50,290,530};
	SDL_Surface* screen= NULL;
	SDL_Surface* background = NULL;
	screen = SDL_SetVideoMode (1280, 720, 32, SDL_SWSURFACE);
	background=IMG_Load ("map1.png");
	SDL_BlitSurface(background, NULL, screen, NULL );
	SDL_Surface* myplane =NULL;
	SDL_Surface* foeplane =NULL;
	SDL_Surface* boom =NULL;
	SDL_Surface* cloud=NULL;
	SDL_Surface* planeshadow=NULL;
	SDL_Surface* baseshadow =NULL;
	SDL_Surface* cloudshadow =NULL;
	initialization (row,column);

	
	show (screen);
	SDL_Flip(screen);
	SDL_Delay(2000);
	
	SDL_Quit();
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
			cout<<"\ny="<<jbase<<"  "<<"x="<<ibase;
			base[counter].type='e';
			base[counter].x=row[ibase];
			base[counter].y=column[jbase];
		}
		else
		{
			if (counter<basecount+emptybase)
			{
				cout<<"\ny="<<jbase<<"  "<<"x="<<ibase;
				base[counter].type='m';
				base[counter].x=row[ibase];
				base[counter].y=column[jbase];
			}
			else
			{
				cout<<" \ny="<<jbase<<"  "<<"x="<<ibase;
				base[counter].type='f';
				base[counter].x=row[ibase];
				base[counter].y=column[jbase];
			}
		}
		counter++;
	}	

}
void show(SDL_Surface* screen)
{
	
	SDL_Surface* mybase =NULL;
	SDL_Surface* emptybase =NULL;
	SDL_Surface* foebase =NULL;
	for (int i=0;i<11;i++)
	{
		
		if (base[i].type=='m')
		{	
			cout<<"Msh\n";
			mybase= IMG_Load ("mybase.png");
			SDL_Rect mybase_cords;
			mybase_cords.x=base[i].x;
			mybase_cords.y=base[i].y;
			SDL_BlitSurface( mybase, NULL, screen, &mybase_cords);

			
		}
		if (base[i].type=='f')
		{	
			cout<<"Fsh\n"<<base[i].x<<"\n"<<base[i].y;;

			foebase= IMG_Load ("foebase.png");
			SDL_Rect foebase_cords;
			foebase_cords.x=base[i].x;
			foebase_cords.y=base[i].y;
			SDL_BlitSurface( foebase, NULL, screen, &foebase_cords);
		}
		/*if (base[i].type=='e')
		{	
			emptybase= IMG_Load ("emptybase.png");
			SDL_Rect base_cords;
			base_cords.x=base[i].x;
			base_cords.y=base[i].y;
			SDL_BlitSurface( mybase, NULL, screen, &base_cords);
			SDL_Flip(screen);
		}*/
		SDL_Flip(screen);
	}
	
}