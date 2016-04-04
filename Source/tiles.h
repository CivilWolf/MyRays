#include <iostream>
#include <SDL2/SDL.h>
#include <time.h>
#include <SDL2_Image/SDL_image.h>
using namespace std;

class Tile
{
public:

	SDL_Texture* texture;
	SDL_Rect sR,dR;
	double angle;
	SDL_Point center;



	Tile();

	//Tile(float x,float y);

	void Draw(SDL_Renderer*renderer);

};
