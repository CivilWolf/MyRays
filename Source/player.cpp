#include "player.h"

//analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;

Player::Player(SDL_Renderer*renderer,string filePath,string audioPath,float x,float y)
{
	playerHealth = 100.0f;
	maxHealth = 100.0f;

	elevation = 0;


	active = true;
	speed = 500.0f;

	arrow = Mix_LoadWAV((audioPath+"laser.wav").c_str());


	oldScore = 0;
	playerScore = 0;
	oldLives = 0;
	playerLives = 6;
	playerPath = filePath + "Ship0.png";
	surface = IMG_Load(playerPath.c_str());
	texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_FreeSurface(surface);
	posRect.x = x;
	posRect.y = y;
	int w,h;
	SDL_QueryTexture(texture,NULL,NULL,&w,&h);
	posRect.w = w;
	posRect.h = h;
	pos_X = x;
	pos_Y = y;

	xDir = 0;
	yDir = 0;


	xDirOld = 1;
	yDirOld = 0;

	center.x = posRect.w / 2;
	center.y = posRect.h / 2;

	string bulletPath;
	bulletPath = filePath + "bullet.png";
	
	for (int i = 0; i < 10; i++)
	{
		Bullet tmpBullet(renderer, bulletPath, -1000, -1000,0,0);
		bulletList.push_back(tmpBullet);

	}

}

void Player::Reset()
{

		posRect.x = 250.0;
		posRect.y = 500.0;
	

	pos_X = posRect.x;
	pos_Y = posRect.y;
	playerLives = 6;
	playerHealth = 100.0f;
	playerScore = 0;
	xDir = 0;
	yDir = 0;
	active = true;
}


void Player::Update(float deltaTime,SDL_Renderer *renderer, string filePath)
{
	pos_X +=(speed * xDir)*deltaTime;
	pos_Y +=(speed * yDir) *deltaTime;
	posRect.x = (int)(pos_X+0.5f);
	posRect.y = (int)(pos_Y+0.5f);





	if (xDir != 0 || yDir != 0)
	{
		x = posRect.x - xDir;
		y = posRect.y - yDir;
		playerangle = atan2(xDir, -yDir) * 180 / 3.14;
		oldAngle = playerangle;
		xDirOld = xDir;
		yDirOld = yDir;
	}
	else
	{
		playerangle = oldAngle;
	}


	if(posRect.x < 0)
	{
		posRect.x = 0;
		pos_X = posRect.x;
	}

	if(posRect.x >1024 - posRect.w)
	{
		posRect.x = 1024 - posRect.w;
		pos_X=posRect.x;
	}
	if(posRect.y < 0)
	{
		posRect.y = 0;
		pos_Y = posRect.y;
	}
	if(posRect.y >1024 - posRect.h)
	{
		posRect.y = 1024 -posRect.h;
		pos_Y = posRect.y;
	}
}



void Player::enemyHit()
{
	playerHealth -= 10.0f;
	cout << endl << playerHealth << endl;
}



void Player::Draw(SDL_Renderer*renderer)
{
	SDL_RenderCopyEx(renderer,texture,NULL,&posRect, playerangle, &center, SDL_FLIP_NONE);
	for (int i = 0; i < bulletList.size(); i++)
	{
		if (bulletList[i].active)
		{
			bulletList[i].Draw(renderer);
		}
	}
}

void Player::OnControllerButton(const SDL_ControllerButtonEvent event)
{

}


void Player::OnControllerAxis(const SDL_ControllerAxisEvent event)
{
	if(event.which == 0)
	{
		if(event.axis == 0)
		{
			if(event.value <-JOYSTICK_DEAD_ZONE)
			{
				xDir=-1.0f;
			}
			else if(event.value > JOYSTICK_DEAD_ZONE)
			{
				xDir = 1.0f;
			}
			else
			{
				xDir = 0.0f;
			}
		}
		if(event.axis == 1)
		{
			if(event.value <-JOYSTICK_DEAD_ZONE)
			{
				yDir = -1.0f;
			}
			else if(event.value > JOYSTICK_DEAD_ZONE)
			{
				yDir = 1.0f;
			}
			else
			{
				yDir = 0.0f;
			}
		}
	}
}

void Player::OnKeyboardPress(const SDL_KeyboardEvent event)
{
	if(event.type == SDL_KEYDOWN)
	{
		if (event.keysym.sym == SDLK_w)
		{
			yDir = -1.0f;
		}
		if (event.keysym.sym == SDLK_s)
		{
			yDir = 1.0f;
		}
		else
		{
			xDir = 0.0f;
			yDir = 0.0f;
		}
	}
}
Player::~Player()
{
	SDL_DestroyTexture(texture);
}




