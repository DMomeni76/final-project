void show(SDL_Surface* screen)
{
	SDL_Surface* mybase =NULL;
	SDL_Surface* emptybase =NULL;
	SDL_Surface* foebase =NULL;
	for (int i=0;i<11;i++)
	{
		if (base[i].type=="m")
		{	
			
			mybase= IMG_Load ("mybase.png");
			SDL_Rect base_cords;
			base_cords.x=base[i].x;
			base_cords.y=base[i].y;
			SDL_BlitSurface( mybase, NULL, screen, &base_cords);
		}
		if (base[i].type=="f")
		{	
			
			foebase= IMG_Load ("foebase.png");
			SDL_Rect base_cords;
			base_cords.x=base[i].x;
			base_cords.y=base[i].y;
			SDL_BlitSurface( mybase, NULL, screen, &base_cords);
		}
		/*if (base[i].type=="e")
		{	
			emptybase= IMG_Load ("emptybase.png");
			SDL_Rect base_cords;
			base_cords.x=base[i].x;
			base_cords.y=base[i].y;
			SDL_BlitSurface( mybase, NULL, screen, &base_cords);
		}*/
		SDL_Flip(screen);
	}
}