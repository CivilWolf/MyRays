#include "enemy.h"
Enemy::Enemy(SDL_Renderer*renderer, string filePath, string audioPath, float x, float y)
{
	active = false;
		boom = Mix_LoadWAV((audioPath+"fire.wav").c_str());
		string basePath = filePath + "Efollow.png";
		eTex = IMG_LoadTexture(renderer, basePath.c_str());
		posRect.x = x;
		posRect.y = y;

		int w, h;
		SDL_QueryTexture(eTex, NULL, NULL, &w, &h);
		posRect.w = w;
		posRect.h = h;

		pos_X = posRect.x;
		pos_Y = posRect.y;

		speed = 100;

		center.x = 32;
		center.y = 32;

		health = 10;

}


void Enemy::Reset()
{
	e
}
void Enemy::Update(float deltaTime, SDL_Rect playerRect)
{

	double distancex = (posRect.x - playerRect.x)*(posRect.x - playerRect.x);
		double distancey = (posRect.y - playerRect.y) * (posRect.y - playerRect.y);
		double calcdistance = sqrt(distancex + distancey);

		if (calcdistance <= 250)
		{
			active = true;
		}
		else
		{
			active = false;
		}

		if (active)
		{
			x = (playerRect.x + (playerRect.w / 2)) - (posRect.x + (posRect.w / 2));
			y = (playerRect.y + (playerRect.h / 2)) - (posRect.y + (posRect.h / 2));
			angle = atan2(y, x) * 180 / 3.14;

			float radians = (angle * 3.14) / 180;

			float move_x = speed * cos(radians);
			float move_y = speed * sin(radians);

			pos_X += (move_x)* deltaTime;
			pos_Y += (move_y)* deltaTime;

			posRect.x = (int)(pos_X + 0.5f);
			posRect.y = (int)(pos_Y + 0.5f);

		}



	if (direction == 0)
	{
		pos_Y -= (speed*yDir)*deltaTime;
		posRect.y = (int)(pos_Y - 0.5f);
		if (posRect.y < 0)
		{
			direction = rand() % 4;
			Reset();
		}
		angle += 0.1;
	}

	else if (direction == 1)
	{
		pos_X += (speed*yDir)*deltaTime;
		posRect.x = (int)(pos_X + 0.5f);
		if (posRect.x < 0)
		{
			direction = rand() % 4;
			Reset();
		}
		angle += 0.1;
	}


	else if (direction == 2)
	{
		pos_Y += (speed*yDir)*deltaTime;
		posRect.y = (int)(pos_Y + 0.5f);
		if (posRect.y > 900)
		{
			direction = rand() % 4;
			Reset();
		}
		angle += 0.1;
	}

	else if (direction == 3)
	{
		pos_X -= (speed*yDir)*deltaTime;
		posRect.x = (int)(pos_X + 0.5f);
		if (posRect.x < 0)
		{
			direction = rand() % 4;
			Reset();
		}
		angle += 0.1;
	}


}



void Enemy::Draw(SDL_Renderer*renderer)
{
	SDL_RenderCopyEx(renderer,texture,NULL,&posRect,angle,&center,SDL_FLIP_NONE);
}

Enemy::~Enemy()
{
	//SDL_DestroyTexture(texture)
}
