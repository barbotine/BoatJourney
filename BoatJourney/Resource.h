#pragma once
#include "Actor.h"
#include <iostream>

using namespace sf;
using namespace std;

class Resource : public Actor
{

private :
	Font font;
	Text resourceValue;

public : 
	Resource(Vector2f position, Texture& texture);
	void update(RenderWindow& window);
	void createText(int value);
	void draw(sf::RenderWindow& window);
};

