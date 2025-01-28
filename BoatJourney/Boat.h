#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Actor.h"

using namespace sf;
using namespace std;

class Boat : public Actor
{
	public:
		using Actor::Actor;
		void update(float deltaTime);
};

