#include "Cloud.h"
#include <SFML/Graphics.hpp>
#include <iostream>

void Cloud::draw(RenderWindow& window)
{
	window.draw(sprite);
}

void Cloud::update(float deltaTime)
{
}
