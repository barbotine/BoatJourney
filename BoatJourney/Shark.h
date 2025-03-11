#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Shark.h"
#include "Actor.h"

using namespace sf;
using namespace std;

class Shark : public Actor
{
	public:
		using Actor::Actor;
		void update(float deltaTime);
};

