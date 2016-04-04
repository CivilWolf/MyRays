#include "tiles.h"


Tile::Tile()
{
	center.x = 0;
	center.y = 0;
	angle = 0;
	texture = NULL;
	sR.h = 0;
	sR.w = 0;
	sR.x = 0;
	sR.y = 0;
	dR.h = 0;
	dR.w = 0;
	dR.x = 0;
	dR.y = 0;
}

void Tile::Draw(SDL_Renderer*renderer)
{
	SDL_RenderCopyEx(renderer,texture,&sR,&dR,angle,&center,SDL_FLIP_NONE);
}
