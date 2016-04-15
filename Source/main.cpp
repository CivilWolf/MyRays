#include <iostream>
#include <fstream>

#include <SDL2/SDL.h>
#include <time.h>
#include <SDL2_Image/SDL_image.h>
#include <cmath>
#include <stdio.h>
#include <string>
#include "tiles.h"
#include "player.h"

#include "enemy.h"


using namespace std;

#define wWidth 1024
#define wHeight 800

#define RPNUM 50

using namespace std;

//code for frame rate independence
float deltaTime = 0.0;
int thisTime = 0;
int lastTime = 0;

bool quit = false, happy = true;
float playerx = 300, playery = 300, pspeed = .5;

int bSpeed = 100;

SDL_Rect bkgd1Pos, bkgd2Pos;

//set temp variables to hold movement
float BG1pos_X = 0, BG1pos_Y = 0;

//set temp variables to hold movement
float BG2pos_X = 0, BG2pos_Y = -1024;

void UpdateBackground(float deltaTime) {
	//Update
	//Update Background 1
	BG1pos_Y += (bSpeed * 1) * deltaTime;
	//Set the new bkgd1 position
	bkgd1Pos.y = (int) (BG1pos_Y + 0.5f);

	//reset when off the bottom of the screen
	if (bkgd1Pos.y >= 1024) {
		bkgd1Pos.y = -1024;
		BG1pos_Y = bkgd1Pos.y;
	}

	//Update Background 2
	BG2pos_Y += (bSpeed * 1) * deltaTime;
	//Set the new bkgd1 position
	bkgd2Pos.y = (int) (BG2pos_Y + 0.5f);

	//reset when off the bottom of the screen
	if (bkgd2Pos.y >= 1024) {
		bkgd2Pos.y = -1024;
		BG2pos_Y = bkgd2Pos.y;
	}
}

class Point {
public:
	int x;
	int y;
	float targetLength;
	float length;
	float angle;
	Point();
};

Point::Point() {
	x = 0;
	y = 0;
	targetLength = 0;
	length = 0;
	angle = 0;
}

/*
 class Mouse
 {
 private:
 float x;
 float y;

 };
 */

int main(int argc, char* argv[]) {

	srand(time(NULL));

	SDL_Window *window;                    // Declare a pointer

	SDL_Init(SDL_INIT_EVERYTHING);              // Initialize SDL2

	// Create an application window with the following settings:
	window = SDL_CreateWindow("An SDL2 window",                  // window title
			SDL_WINDOWPOS_UNDEFINED,           // initial x position
			SDL_WINDOWPOS_UNDEFINED,           // initial y position
			1024,                               // width, in pixels
			1024,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
	);

#if defined(__APPLE__)
	{
		cout << "Running on Apple" << endl;
		//get the current working directory
		string currentWorkingDirectory(getcwd(NULL, 0));

		//create a string linking to the mac's images folder
		string images_dir = currentWorkingDirectory + "/MyRays/Images/";
	}
#endif

#if defined(__linux__)
	{
		cout << "Running on Linux" << endl;
		//get the current working directory
		string currentWorkingDirectory(getcwd(NULL, 0));

		//create a string linking to the mac's images folder
		string images_dir = currentWorkingDirectory + "/MyRays/Images/";
		string audio_dir = currentWorkingDirectory + "/MyRays/Audio/";
	}
#endif

#if defined(_WIN32) || (_WIN64)
	{
		cout << "Running on Windows" << endl;
		//get the current working directory
		string currentWorkingDirectory(getcwd(NULL, 0));

		//create a string linking to the mac's images folder
		string images_dir = currentWorkingDirectory + "\\MyRays\\Images\\";
		string audio_dir = currentWorkingDirectory + "\\MyRays\\Audio\\";
	}
#endif

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		//quit = true;
		return 1;
	}

	SDL_Renderer*renderer = NULL;

	//create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	string currentWorkingDirectory(getcwd(NULL, 0));
	string images_dir = currentWorkingDirectory + "/MyRays/Images/";
	string audio_dir = currentWorkingDirectory + "/MyRays/Audio/";
	//CreateBackground
	string BKGDpath = images_dir + "Back.png";

	//create a SDL surface to hold the background images
	SDL_Surface *surface = IMG_Load((BKGDpath).c_str());

	//create SDL_Texture
	SDL_Texture*bkgd1;
	//place surface info into the texture bkgd1;
	bkgd1 = SDL_CreateTextureFromSurface(renderer, surface);

	//create SDL_Texture
	SDL_Texture*bkgd2;
	//place surface info into the texture bkgd1;
	bkgd2 = SDL_CreateTextureFromSurface(renderer, surface);

	//free SDL surface
	SDL_FreeSurface(surface);

	//Create the SDL_Rectangle for the texture's position and size -x,y,w,h

	//set the X,T,W, and H for the Rectangle
	bkgd1Pos.x = 0;
	bkgd1Pos.y = 0;
	bkgd1Pos.w = 1024;
	bkgd1Pos.h = 1024;

	//Create the SDL_Rectangle for the texture's position and size -x,y,w,h

	//set the X,T,W, and H for the Rectangle
	bkgd2Pos.x = 0;
	bkgd2Pos.y = -768;
	bkgd2Pos.w = 1024;
	bkgd2Pos.h = 1024;

	//**************************************Create Background -End*************************************

	//create a renderer
	SDL_Renderer * r1 = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED);

	//**************** S1 - Start ****************//

	SDL_GameControllerEventState(SDL_ENABLE);
	//Setup a Game Controller Variable
	SDL_GameController* gGameController0 = NULL;

	//Open Game Controller
	gGameController0 = SDL_GameControllerOpen(0);

	SDL_GameController* gGameController1 = NULL;

	//Open Game Controller
	gGameController1 = SDL_GameControllerOpen(0);
	//Turn on Game Controller Events

	//SDL Event to handle input
	SDL_Event event;

	//setup variables for the game states
	enum GameState {
		MENU, INSTRUCTIONS, PLAYERS1, PLAYERS2, WIN, LOSE
	};

	//setup the initial state
	GameState gameState = PLAYERS1;

	//boolean values to control movement though the states
	bool menu = false, instructions = false, players1 = false, players2 = false,
			win = false, lose = false, quit = false;

	//////////////////////////////////////////////

	//Open Audio Channel
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Music *bgm = Mix_LoadMUS((audio_dir + "ambience.wav").c_str());
	if (!Mix_PlayingMusic()) {
		Mix_PlayMusic(bgm, -1);
	}

	Mix_Chunk *explosionSound = Mix_LoadWAV((audio_dir + "Slop.wav").c_str());

	bool alreadyOver = false;

	//create players
	Player player1 = Player(renderer, images_dir.c_str(), audio_dir.c_str(),
			250.0, 500.0);

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


	Enemy enemy1 = Enemy(renderer, images_dir.c_str(),audio_dir.c_str(),200.0f,100.0f);





	while (!quit) {
		switch (gameState) {

		case PLAYERS1: {

			//reset the player
			player1.Reset();

			players1 = true;
			cout << "The Game State is Players 1" << endl;
			cout << endl;
			while (players1) {

				//set up framerate for the section, or CASE
				thisTime = SDL_GetTicks();
				deltaTime = (float) (thisTime - lastTime) / 1000;
				lastTime = thisTime;

				//check for input events
				if (SDL_PollEvent(&event)) {
					//check to see if the SDL Window is closed - player clicks X in the window
					if (event.type == SDL_QUIT) {
						quit = true;
						players1 = false;
						break;
					}
					switch (event.type) {
					case SDL_CONTROLLERBUTTONDOWN:
						if (event.cdevice.which == 0) {
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_X) {
								players1 = false;
								gameState = WIN;

							}
							if (event.cbutton.button
									== SDL_CONTROLLER_BUTTON_Y) {
								players1 = false;
								gameState = LOSE;

							}
							//send button press info to player 1
							if (player1.active) {
								player1.OnControllerButton(event.cbutton);
							}
						}
						break;
					case SDL_CONTROLLERAXISMOTION:
						player1.OnControllerAxis(event.caxis);
						break;
					case SDL_KEYDOWN:
						player1.OnKeyboardPress(event.key);
						break;
					}
				}

				//UpdateBackground(deltaTime);
				if (player1.active) {
					player1.Update(deltaTime, renderer, images_dir.c_str());
				}

				////move background
				//if ((player1.posRect.x >= 1024 - player1.posRect.w))// &&(player1.Xvalue > 8000))
				//{
				//	X_pos -= (tank1.speed) * deltaTime;

				//	if((bkgdRect.x > -1024))
				//	{
				//		bkgdRect.x =
				//	}
				//}

				//LightUpdate
				cout << player1.center.x << endl << player1.center.y << endl;


				enemy1.Update(deltaTime, player1.posRect);

				if (SDL_HasIntersection(&player1.posRect, &enemy1.posRect))
				{
					player1.enemyHit();
				}


				//Start Drawing
				//Clear SDL Renderer
				SDL_RenderClear(renderer);

				//Draw the b image
				SDL_RenderCopy(renderer, bkgd1, NULL, &bkgd1Pos);
				//Draw the b image
				SDL_RenderCopy(renderer, bkgd2, NULL, &bkgd2Pos);

				//Draw the menu image
				//SDL_RenderCopy(renderer, oneN, NULL, &onePos);

				player1.Draw(renderer);


				enemy1.Draw(renderer);
				//SDL Render present
				SDL_RenderPresent(renderer);

			}
		}
		break;	//end players1 case
		}
	}

	//Destroy window

	SDL_DestroyWindow(window);

	//Quit SDL subsystems

	SDL_Quit();

	return 0;
}
