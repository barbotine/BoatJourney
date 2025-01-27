#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Cloud
{
	private :
		Vector2f position;
		Sprite sprite;
		Texture texture;

	public : 
		Cloud(RenderWindow& window);

};

