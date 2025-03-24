#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Shark.h"
#include "Actor.h"

using namespace sf;
using namespace std;

class Shark : public Actor
{
	private:
		float speed;
		bool isActive;
		float spriteRespawnTime;
		float respawnTimer;

	public:
		Shark(Vector2f position, Texture& texture, float speed);
		void makeSharkDisappear(float currentTime);

		void makeSharkAppear(float currentTime);
		void update(RenderWindow& window, float deltaTime);
		bool getIsActive();
};

