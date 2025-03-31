#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Actor.h"

using namespace sf;
using namespace std;

class Character;

class Sun : public Actor
{
	private:
		float speed;
		Vector2f position;
		Clock timer;
		bool timerStarted = false;
		bool isVisible;

	public:
		using Actor::Actor;
		Sun(Vector2f position, string actorTex, Texture& texture, float speed);
		Sun(Vector2f position, Texture& texture, float speed);
		void update(RenderWindow& window, float deltaTime);
		void makeSunInvisible(RenderWindow& window);
		void makeSunVisible(RenderWindow& window, float sunAppearingTime);
		float generateRandomTime();
		bool getIsVisible();
};

