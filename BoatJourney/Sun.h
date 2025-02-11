#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Actor.h"

using namespace sf;
using namespace std;

class Sun : public Actor
{
private:
	float speed;
	Vector2f position;

public:
	using Actor::Actor;
	Sun(Vector2f position, string actorTex, Texture& texture, float speed);
	Sun(Vector2f position, Texture& texture, float speed);
	void update(RenderWindow& window);
	bool sunIsVisible(RenderWindow& window);
};

