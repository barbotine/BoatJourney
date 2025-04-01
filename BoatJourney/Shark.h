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

		bool SharkBoatCollisionDetected;
		int sharkClicks;
		int sharkMaxClicks;
		bool isSharkAlive;
		bool wasSharkPressed;

	public:
		Shark(Vector2f position, Texture& texture, float speed);
		void makeSharkDisappear(float currentTime);

		void makeSharkAppear(float currentTime);
		void update(RenderWindow& window, float deltaTime, Actor& actor);
		bool getIsActive();
		void rushingOnActor(Actor& actor, float deltaTime);
		void collidesWith(Actor& actor);

		bool getSharkBoatCollisionDetected();

		void setSharkBoatCollisionDetected(bool value);

		int getSharkClicks();

		void setSharkClicks(int value);

		void incrementeClick();

		int getSharkMaxClicks();

		bool getIsSharkAlive();

		void setIsSharkAlive(bool value);

		bool& getWasSharkPressed();

		void setWasSharkPressed(bool value);

};

