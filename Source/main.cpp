#include <iostream>


#include <SDL2/SDL.h>
#include <time.h>
#include <SDL2_Image/SDL_image.h>
#include <cmath>
#include <stdio.h>
#include <string>

#define wWidth 1024
#define wHeight 800

using namespace std;

bool quit = false,happy = true;
float playerx = 300, playery = 300, pspeed = .5;


class Player
{
public:
	float x;
	float y;


};

class Mouse
{
private:
	float x;
	float y;

};

Player player;



int main(int argc, char* args[]) {

	// initialize SDL
	SDL_Init(SDL_INIT_VIDEO);

	// create a window
	SDL_Window* window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, wWidth, wHeight, SDL_WINDOW_SHOWN);


	//create a renderer
	SDL_Renderer * r1 = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	
	//**************** S1 - Start ****************//

	//**************** S1 - End ****************//

	SDL_Surface*surf1;
	
	SDL_Texture*surfTex;
	

	surf1 = SDL_LoadBMP("Player.bmp");
	surfTex = SDL_CreateTextureFromSurface(r1, surf1);
	SDL_FreeSurface(surf1);


	SDL_Surface*s;
	s = SDL_CreateRGBSurface(0, 700, 700, 32, 0, 0, 0, 0);
	SDL_Event keyboardevent;    //The SDL event that we will poll to get events.
	//const Uint8 *keys = SDL_GetKeyboardState(NULL);

	while (!quit)
	{
		while (SDL_PollEvent(&keyboardevent)){
			switch (keyboardevent.type){
			case SDL_KEYDOWN:
				switch (keyboardevent.key.keysym.sym) {
				
				case SDLK_UP:

					//s1.up = true;

					player.y-= 10;


					break;
				case SDLK_DOWN:

					//s1.down = true;
					player.y+= 10;

					break;
				case SDLK_LEFT:
					//s1.left = true;
					player.x-= 10;

					break;
				case SDLK_RIGHT:
					//s1.right = true;
					player.x+= 10;

					break;
				case SDLK_ESCAPE:
					quit = true;
					break;
				}

				default:
					break;
				}
			}
		
		

		//cout << "angle: " << s1.angle  << "\nPlayer Pos: (" << s1.pos.x << "," << s1.pos.y << ")";






		SDL_SetRenderDrawColor(r1, 0, 0, 0, 0);
		SDL_RenderClear(r1);
		

		//s1.update(delay,wall,obj);

		



		SDL_RenderDrawLine(r1,player.x,player.y,wWidth/2,wHeight/2);
		//s1.Draw(r1, delay);
		//s1.box.Draw(r1);

	
			/*obj0->Draw(r1);
			obj1->Draw(r1);
			obj2->Draw(r1);
			obj3->Draw(r1);
			obj4->Draw(r1);*/

		//show the screen
		SDL_RenderPresent(r1);
	}


	//Destroy window

	SDL_DestroyWindow(window);


	//Quit SDL subsystems

	SDL_Quit();


	return 0;
}