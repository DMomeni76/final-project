#include <iostream>
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#include "SDL/SDL_image.h"
#include <SDL/SDL_mixer.h>
#include "SDL/SDL_ttf.h"
#include <cstdlib>
#include <ctime>
#include "sstream"
#include <cmath>
#include <fstream>
#include <string>
using namespace std;

void initialization (int row[],int column[], int &basecount);
void show(SDL_Surface* screen,int &timer_show_plane ,int cloud_speed, int basecount, int &target_base_number);
void event_handel (SDL_Surface* screen, int basecount, int &target_base_number);
void base_handel (int &timer, int basecount);
void myplane_handel (SDL_Surface* screen,int selected_bases_count, int basecount);
void menu( SDL_Surface* screen);
bool quit(SDL_Surface* screen);
struct base_struct
{
	char type;
	bool select;
	int x;
	int y;
	int w;
	int h;
	int plane_count;
	int production_speed;
	int plane_count_temp;
	int plane_xspeed;
	int plane_yspeed;
	float shib;
	float tetha;
	bool target;
}base[11];
struct plane_struct
{
	char type;
	bool show;
	int x;
	int y;
	int w;
	int h;
	float tetha;
	float shib;
	int xspeed;
	int yspeed;
}myplane[120],foeplane[120];
int myplane_speed =1;
struct cloud_struct
{
	int x;
	int y;
}cloud[3];
int myplane_number=0;
int show_count=3;
//images
	SDL_Surface* background = NULL;
	SDL_Surface* mybase =NULL;
	SDL_Surface* emptybase =NULL;
	SDL_Surface* foebase =NULL;
	SDL_Surface* baseshadow =NULL;
	SDL_Surface* Cloud=NULL;
	SDL_Surface* cloudshadow =NULL;
	SDL_Surface* mybase_select=NULL;
	SDL_Surface* foebase_select=NULL;
	SDL_Surface* emptybase_select=NULL;
	SDL_Surface* Myplane=NULL;
	SDL_Surface* Foeplane=NULL;
	SDL_Surface* boom =NULL;
	SDL_Surface* planeshadow=NULL;
	SDL_Surface* emptybase_plane_count[10];
	SDL_Surface* mybase_plane_count[20];
	SDL_Surface* menupic[3];
	SDL_Surface* quit_no=NULL;
	SDL_Surface* quit_yes= NULL;
	Mix_Chunk* selection_sound=NULL;
int main (int argc, char * args[])
{
	srand(time(0));
	SDL_Init(SDL_INIT_EVERYTHING);
	int column[5]={88,344,600,856,1112};
	int row[3]={100,340,580};
	SDL_Surface* screen= NULL;
	screen = SDL_SetVideoMode (1280, 720, 32, SDL_SWSURFACE);
	Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
	SDL_WM_SetCaption ("Plane Wars (D&H)", NULL);
	int basecount =0;
	int target_base_number;
	int timer=time(0);
	int timer_show_plane=time(0);
	int cloud_speed=1;
	initialization (row,column, basecount);
	bool game_run=true;
	menu (screen);
	while (game_run)
	{
		event_handel (screen, basecount, target_base_number);
		show (screen,timer_show_plane,cloud_speed, basecount, target_base_number);
		base_handel (timer, basecount);
		SDL_Flip(screen);
		SDL_Delay (2);
	}
	return 0;
}
void initialization (int row[],int column[], int &basecount)
{
	//basecount=rand()%4 + 1;
	basecount=4;
	int emptybase_count;
	if (basecount<=2)
	{
		emptybase_count=2;
	}
	else
	{
		emptybase_count=3;
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
	while(counter<2*basecount+emptybase_count)
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
		if (counter<emptybase_count)
		{
			base[counter].type='e';
			base[counter].x=column[jbase];
			base[counter].y=row[ibase];
			base[counter].w=73;
			base[counter].h=82;
			base[counter].select=false;
			base[counter].plane_count=10;
		    base[counter].production_speed=1;	
		}
		else
		{
			if (counter<basecount+emptybase_count)
			{
				base[counter].type='m';
				base[counter].x=column[jbase];
				base[counter].y=row[ibase];
				base[counter].w=85;
                base[counter].h=89;
                base[counter].select=false;
                base[counter].plane_count=5;
                base[counter].production_speed=1;
			}
			else
			{
				base[counter].type='f';
				base[counter].x=column[jbase];
				base[counter].y=row[ibase];
				base[counter].w=76;
                base[counter].h=85;
                base[counter].select=false;
                base[counter].plane_count=5;
                base[counter].production_speed=1;      
			}
		}
		counter++;
	}
	//image load
		basecount=2*basecount+emptybase_count;
		background=SDL_LoadBMP ("game_images/map1.bmp");
		foebase= IMG_Load ("game_images/foebase.png");
		mybase= IMG_Load ("game_images/mybase.png");
		emptybase= IMG_Load ("game_images/emptybase.png");
		mybase_select=IMG_Load ("game_images/mybase select.png");
		foebase_select=IMG_Load ("game_images/foebase select.png");
		emptybase_select=IMG_Load ("game_images/emptybase select.png");
		baseshadow=IMG_Load ("game_images/baseshadow.png");
		Cloud=IMG_Load ("game_images/cloud.png");
		cloudshadow=IMG_Load("game_images/cloudshadow.png");
		Myplane=IMG_Load("game_images/myplane.png");
		Foeplane=IMG_Load("game_images/foeplane.png");
		planeshadow=IMG_Load("game_images/planeshadow.png");
		menupic[0]=IMG_Load ("game_images/menu1.png");
		menupic[1]=IMG_Load ("game_images/menu2.png");
		menupic[2]=IMG_Load ("game_images/menu3.png");
		quit_no=IMG_Load ("game_images/quitno.png");
		quit_yes=IMG_Load ("game_images/quityes.png");
		mybase_plane_count[0]= IMG_Load ("game_images/numbers/1.png");
		mybase_plane_count[1]= IMG_Load ("game_images/numbers/2.png");
		mybase_plane_count[2]= IMG_Load ("game_images/numbers/3.png");
		mybase_plane_count[3]= IMG_Load ("game_images/numbers/4.png");
		mybase_plane_count[4]= IMG_Load ("game_images/numbers/5.png");
		mybase_plane_count[5]= IMG_Load ("game_images/numbers/6.png");
		mybase_plane_count[6]= IMG_Load ("game_images/numbers/7.png");
		mybase_plane_count[7]= IMG_Load ("game_images/numbers/8.png");
		mybase_plane_count[8]= IMG_Load ("game_images/numbers/9.png");
		mybase_plane_count[9]= IMG_Load ("game_images/numbers/10.png");
		mybase_plane_count[10]= IMG_Load ("game_images/numbers/11.png");
		mybase_plane_count[11]= IMG_Load ("game_images/numbers/12.png");
		mybase_plane_count[12]= IMG_Load ("game_images/numbers/13.png");
		mybase_plane_count[13]= IMG_Load ("game_images/numbers/14.png");
		mybase_plane_count[14]= IMG_Load ("game_images/numbers/15.png");
		mybase_plane_count[15]= IMG_Load ("game_images/numbers/16.png");
		mybase_plane_count[16]= IMG_Load ("game_images/numbers/17.png");
		mybase_plane_count[17]= IMG_Load ("game_images/numbers/18.png");
		mybase_plane_count[18]= IMG_Load ("game_images/numbers/19.png");
		mybase_plane_count[19]= IMG_Load ("game_images/numbers/20.png");
		emptybase_plane_count[0]=IMG_Load ("game_images/emptybasenumbers/1.png");
		emptybase_plane_count[1]=IMG_Load ("game_images/emptybasenumbers/2.png");
		emptybase_plane_count[2]=IMG_Load ("game_images/emptybasenumbers/3.png");
		emptybase_plane_count[3]=IMG_Load ("game_images/emptybasenumbers/4.png");
		emptybase_plane_count[4]=IMG_Load ("game_images/emptybasenumbers/5.png");
		emptybase_plane_count[5]=IMG_Load ("game_images/emptybasenumbers/6.png");
		emptybase_plane_count[6]=IMG_Load ("game_images/emptybasenumbers/7.png");
		emptybase_plane_count[7]=IMG_Load ("game_images/emptybasenumbers/8.png");
		emptybase_plane_count[8]=IMG_Load ("game_images/emptybasenumbers/9.png");
		emptybase_plane_count[9]=IMG_Load ("game_images/emptybasenumbers/10.png");
		selection_sound=Mix_LoadWAV ("game_sounds/selection_sound.wav");
		cloud[0].x=500;
		cloud[1].x=40;
		cloud[2].x=1000;
		cloud[0].y=50;
		cloud[1].y=220;
		cloud[2].y=450;
}
void show(SDL_Surface* screen,int &timer_show_plane ,int cloud_speed, int basecount, int &target_base_number)
{
	
	SDL_Rect emptybase_plane_count_cords;
	SDL_Rect mybase_plane_count_cords;
	SDL_Rect mybase_cords;
	SDL_Rect foebase_cords;
	SDL_Rect emptybase_cords;
	SDL_Rect baseshadow_cords;
	SDL_Rect cloud_cords;
	SDL_Rect cloudshadow_cords;
	SDL_Rect myplane_cords;
	SDL_Rect foeplane_cords;
	SDL_Rect planeshadow_cords;
	SDL_BlitSurface(background, NULL, screen, NULL );

	for (int i=0;i<basecount;i++)
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
			mybase_plane_count_cords.x=base[i].x+22;
			mybase_plane_count_cords.y=base[i].y-25;
			SDL_BlitSurface (mybase_plane_count[base[i].plane_count-1], NULL, screen, &mybase_plane_count_cords);

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
			emptybase_plane_count_cords.x=base[i].x+22;
			emptybase_plane_count_cords.y=base[i].y-25;
			SDL_BlitSurface (emptybase_plane_count[base[i].plane_count-1], NULL, screen, &emptybase_plane_count_cords);
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
	/*for (int i=0;i<myplane_number;i++)
	{
		if (myplane[i].x>base[target_base_number].x && myplane[i].x<base[target_base_number].x+base[target_base_number].w)
		{
			if (myplane[i].y>base[target_base_number].y && myplane[i].y<base[target_base_number].y+base[target_base_number].h)
			{
				myplane[i].show=false;
				if (base[target_base_number].type='m' && base[target_base_number].plane_count<20) base[target_base_number].plane_count++;
				if (base[target_base_number].type!='m' && base[target_base_number].plane_count>0) base[target_base_number].plane_count--;
				if (base[target_base_number].type!='m' && base[target_base_number].plane_count<=0) base[target_base_number].type='m';
			}
		}*/
	int current_time=time(0);
	if (current_time - timer_show_plane>.00001)
	{
					show_count+=3;
					timer_show_plane=time(0);
					for (;show_count>myplane_number;show_count--);
	}			
			for (int i=0;i<show_count;i++)
			{

				if (myplane[i].show)
				{
					//myplane[i].x+=myplane_speed*cos(myplane[i].tetha);
					//myplane[i].y+=myplane_speed*sin(myplane[i].tetha);
					myplane[i].x+=myplane[i].xspeed;
					myplane[i].y+=myplane[i].shib*myplane[i].xspeed+myplane[i].yspeed;
					myplane_cords.x=myplane[i].x;
					myplane_cords.y=myplane[i].y;
					SDL_BlitSurface (Myplane, NULL, screen, &myplane_cords);
				}
			}

	
}
void event_handel (SDL_Surface* screen, int basecount, int &target_base_number)
{	
	float delta_x;
	int selected_bases_count=0;
	float delta_y;
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		if (event.type==SDL_QUIT)
		{	
			quit(screen);
		}
		if (event.type==SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button==SDL_BUTTON_LEFT)
			{
                for (int i=0;i<basecount;i++)
                {
                    if (event.button.x>base[i].x && event.button.x<base[i].x+base[i].w)
                    {
                        if (event.button.y>base[i].y && event.button.y<base[i].y+base[i].h)
                        {
                            if (base[i].type=='m')
                            {
                            	if (base[i].select) base[i].select=false;
                               	else
                               	{ 
                               		Mix_PlayChannel (-1,selection_sound,0);
                               		base[i].select=true;
                               	}
                           	}
                        }
                    }
                }
			}
			if (event.button.button==SDL_BUTTON_RIGHT)
			{

				for (int i=0;i<basecount;i++)
                {
                    if (event.button.x>base[i].x && event.button.x<base[i].x+base[i].w)
                    {
                        if (event.button.y>base[i].y && event.button.y<base[i].y+base[i].h)
                        {
                           	base[i].target=true;
                           	target_base_number=i;
                          	for (int j=0;j<basecount;j++)
                            {	
                             	if (base[j].type=='m' && base[j].select==true && i!=j)
                             	{
                             		base[j].plane_count_temp=base[j].plane_count;
                             		delta_x=(base[i].x+(base[i].w/2)-base[j].x+(base[j].w/2));
                             		delta_y=(base[i].y+(base[i].h/2))-(base[j].y+(base[j].h/2));
                           			base[j].tetha=atan(delta_y/delta_x);
                           			if (base[j].x!=base[i].x)
                           			{
                           				if (base[j].y!=base[i].y)
                           				{
                           					base[j].shib=delta_y/delta_x;
                           					if (base[j].x<base[i].x) base[j].plane_xspeed=1;
                           					else base[j].plane_xspeed=-1;
                           					base[j].plane_yspeed=0;
                           				}
                           				else
                           				{
                           					base[j].shib=0;
                           					if (base[j].x<base[i].x) base[j].plane_xspeed=1;
                           					else base[j].plane_xspeed=-1;
                           					base[j].plane_yspeed=0;
                           				}
                           			}
                           			else
                           			{
                           				base[j].plane_xspeed=0;
                           				base[j].shib=0;
                           				if (base[j].y<base[i].y) base[j].plane_yspeed=1;
                           				else base[j].plane_yspeed=-1;
                           			}
                           			base[j].select=false;
                           			selected_bases_count++;
                             	}
                             	if (base[j].type=='m' && base[j].select==true && i==j)
                             	{
                             		base[j].plane_count_temp=0;
                             		base[j].select=false;
                             	}
                            }
                            myplane_handel (screen,selected_bases_count, basecount);
                        }
                        
                    }
                }
			}
		}
		if (event.type==SDL_MOUSEMOTION)
		{
    	    for (int i=0;i<basecount;i++)
   		    {
   	      		if (event.button.x>base[i].x && event.button.x<base[i].x+base[i].w)
            	{
               		if (event.button.y>base[i].y && event.button.y<base[i].y+base[i].h)
                	{
                		if (base[i].type!='m')
                		{
                			for (int j=0;j<basecount;j++)
                			{
                				if (base[j].select==true)
                				{
                    				base[i].select=true;
                    				break;
                				}
                				if (base[j].type=='f') break;
                			}
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
}
void base_handel (int &timer, int basecount)
{
	int current_time=time(0);
	if (current_time - timer>=2)
	{
		for (int i=0;i<basecount;i++)
		{
			if (base[i].type!='e' && base[i].plane_count<20)
			{
				base[i].plane_count+=base[i].production_speed;
			}
		}
		timer=time(0);
	}
}
void myplane_handel (SDL_Surface* screen,int selected_bases_count, int basecount)
{
	int collocation=0;
	int collocation_check=0;
	int counter=0;
	if (selected_bases_count==1) selected_bases_count+=2;
	if (selected_bases_count==2) selected_bases_count+=1;
	while (counter<21)
	{
		
		for (int i=0;i<basecount;i++)
		{
			if (base[i].type=='m' && base[i].plane_count_temp>0)
			{
				base[i].plane_count_temp--;
				base[i].plane_count--;
				if (collocation%selected_bases_count==0)
				{
					myplane[myplane_number].x=base[i].x+(base[i].w/2);
					myplane[myplane_number].y=base[i].y + 17;
					myplane[myplane_number].tetha=base[i].tetha;
					myplane[myplane_number].shib=base[i].shib;
					myplane[myplane_number].xspeed=base[i].plane_xspeed;
					myplane[myplane_number].yspeed=base[i].plane_yspeed;
					myplane[myplane_number].show=true;
					myplane_number++;
					collocation_check++;
	
				}
				if (collocation_check==selected_bases_count)
				{ 
					collocation_check=0;
					collocation++;
				}
				if (collocation==3) collocation=0;			
				if (collocation%selected_bases_count==1)
				{
					myplane[myplane_number].x=base[i].x+(base[i].w/2);
					myplane[myplane_number].y=base[i].y+(base[i].h/2);
					myplane[myplane_number].tetha=base[i].tetha;
					myplane[myplane_number].shib=base[i].shib;
					myplane[myplane_number].xspeed=base[i].plane_xspeed;
					myplane[myplane_number].yspeed=base[i].plane_yspeed;
					myplane[myplane_number].show=true;
					myplane_number++;
					collocation_check++;
		
				}
				if (collocation_check==selected_bases_count)
				{ 
					collocation_check=0;
					collocation++;
				}
				if (collocation==3) collocation=0;
				if (collocation%selected_bases_count==2)
				{
					myplane[myplane_number].x=base[i].x+(base[i].w/2);
					myplane[myplane_number].y=base[i].y+base[i].h-17;
					myplane[myplane_number].tetha=base[i].tetha;
					myplane[myplane_number].shib=base[i].shib;
					myplane[myplane_number].xspeed=base[i].plane_xspeed;
					myplane[myplane_number].yspeed=base[i].plane_yspeed;
					myplane[myplane_number].show=true;
					myplane_number++;
					collocation_check++;
				
				}
				if (collocation_check==selected_bases_count)
				{ 
					collocation_check=0;
					collocation++;
				}
				if (collocation==3) collocation=0;
			}
			
		}
		
		counter++;
	}
}
void menu( SDL_Surface* screen)
{	
	Mix_Music* menu_music=NULL;
	menu_music=Mix_LoadMUS ("game_sounds/menu_music.mp3");
	Mix_PlayMusic (menu_music,-1);
	bool menu_run=true;
	SDL_BlitSurface (menupic[0],NULL, screen, NULL);
	while (menu_run)
	{
		SDL_Event event;
		if(SDL_PollEvent(&event))
		{
			if (event.type==SDL_QUIT)
			{
				quit (screen);
				menu_run=false;
			}
			if (event.type==SDL_MOUSEMOTION)
			{
				if (event.button.x>250 && event.button.x<1000 && event.button.y>150 && event.button.y<335)
				{

                    SDL_BlitSurface (menupic[0],NULL, screen, NULL);
				}
				if (event.button.x>250 && event.button.x<1000 && event.button.y>335 && event.button.y<385)
				{
                    SDL_BlitSurface (menupic[1],NULL, screen, NULL);
				}
				if (event.button.x>250 && event.button.x<1000 && event.button.y>385 && event.button.y<550)
				{
                    SDL_BlitSurface (menupic[2],NULL, screen, NULL);
				}
			}
			if (event.type==SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button==SDL_BUTTON_LEFT)
                {
                	if (event.button.x>250 && event.button.x<1000 && event.button.y>250 && event.button.y<335)
					{
						Mix_PlayChannel (-1,selection_sound,0);
                	    menu_run=false;
					}
					if (event.button.x>250 && event.button.x<1000 && event.button.y>335 && event.button.y<385)
					{
						Mix_PlayChannel (-1,selection_sound,0);
					}
					if (event.button.x>250 && event.button.x<1000 && event.button.y>385 && event.button.y<450)
					{
						Mix_PlayChannel (-1,selection_sound,0);
						//quit(screen);
						if (quit(screen)==false)  SDL_BlitSurface (menupic[2],NULL, screen, NULL);
					}
                }
            }    
		}
	SDL_Flip (screen);
	SDL_Delay (1);
	}
	Mix_FreeMusic (menu_music);
}
bool quit(SDL_Surface* screen)
{
	SDL_BlitSurface (quit_no,NULL, screen, NULL);
	while (true)
	{
		SDL_Event event;
		if(SDL_PollEvent(&event))
		{
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
			if (event.type==SDL_MOUSEBUTTONDOWN)
            {
                if (event.button.button==SDL_BUTTON_LEFT)
                {
                	if (event.button.x>250 && event.button.x<1000 && event.button.y>340 && event.button.y<408)
					{	
						Mix_PlayChannel (-1,selection_sound,0);
						return false;
					}
					if (event.button.x>250 && event.button.x<1000 && event.button.y>408 && event.button.y<500)
					{
						Mix_PlayChannel (-1,selection_sound,0);
                    	SDL_FreeSurface (background);
						SDL_FreeSurface (mybase); 
 						SDL_FreeSurface (foebase); 
 						SDL_FreeSurface (baseshadow); 
						SDL_FreeSurface (emptybase); 
  						SDL_FreeSurface (Cloud); 
  						SDL_FreeSurface (cloudshadow); 
 						SDL_FreeSurface (mybase_select); 
  						SDL_FreeSurface (foebase_select); 
 						SDL_FreeSurface (emptybase_select); 
						for (int i=0;i<20;i++) 
  						{ 
   							SDL_FreeSurface (mybase_plane_count[i]); 
  						}
						SDL_FreeSurface(screen);
						Mix_CloseAudio();
						SDL_Quit();
					}
                }
            }
		}
	SDL_Flip (screen);
	SDL_Delay (1);
	}
}