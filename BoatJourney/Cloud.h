#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Actor.h"

using namespace sf;
using namespace std;

class Cloud : public Actor
{
	private :
		float speed;

	public:
		using Actor::Actor;
		Cloud(Vector2f position, string actorTex, Texture& texture, float speed);
		Cloud(Vector2f position, Texture& texture, float speed);
		void update(RenderWindow& window, float deltaTime);
};