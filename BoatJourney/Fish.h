#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Actor.h"

using namespace sf;
using namespace std;

enum class MovementDirection {
	LEFT,
	RIGHT
};

class Fish : public Actor
{
private:
	float speed;
	MovementDirection direction;
	bool wasClicked;

public:
	Fish(Vector2f position, Texture& texture, float speed, MovementDirection direction);
	void update(RenderWindow& window);
	Sprite& getSprite();
	bool& getWasClicked();
};

