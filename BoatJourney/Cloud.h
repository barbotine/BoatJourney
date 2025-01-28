#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Actor.h"

using namespace sf;
using namespace std;

class Cloud : public Actor
{
	private :
		int speed;

	public:
		using Actor::Actor;
		Cloud(Vector2f position, string actorTex, Texture& texture, int speed);
		Cloud(Vector2f position, Texture& texture, int speed);
		void update();
};