#pragma once
#include "Actor.h"
#include <iostream>

using namespace sf;
using namespace std;

class Resource
{
	private :
		Font font;
		Text resourceValue;
		Sprite sprite;
		Texture texture;

	public : 
		Resource(Vector2f spritePosition, Texture& texture, Vector2f textPosition, int value);
		void update(RenderWindow& window, int value);
		void setText(int value);
		void draw(sf::RenderWindow& window);
};

