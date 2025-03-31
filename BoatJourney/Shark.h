#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Shark.h"
#include "Actor.h"
#include "Utils.h"

using namespace sf;
using namespace std;

class Shark : public Actor
{
	private:
		float speed;
		bool isActive;
		float spriteRespawnTime;
		float respawnTimer;
		bool isRushing;
		float elaspsedTime;

	public:
		Shark(Vector2f position, Texture& texture, float speed);
		void makeSharkDisappear(float currentTime);
		void makeSharkAppear(float currentTime);
		void update(RenderWindow& window, float deltaTime, Actor& actor);
		bool getIsActive();
		void rushingOnActor(Actor& actor, float deltaTime);
		void collidesWith(Actor& actor);
};

