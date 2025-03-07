#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Actor.h"
#include "Sun.h"

using namespace sf;
using namespace std;

class Character : public Actor
{
	public:
		Character(Vector2f position, Texture& texture);
		void makingSolarEnergy(Sun& sun, RenderWindow& window);
		bool isMaxResourceNotReach(int resource);
		int getSolarResource();
		int getLifespan();

	private:
		int solarResource;
		int lifespan;
		int food;
		int water;
};

