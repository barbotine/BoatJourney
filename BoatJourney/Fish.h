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
	bool isActive;
	float spriteRespawnTime;
	float respawnTimer;

public:
	Fish(Vector2f position, Texture& texture, float speed, MovementDirection direction);
	void update(RenderWindow& window, float currentTime, float deltaTime);
	Sprite& getSprite();
	bool& getWasClicked();
	void makeFishDisappear(float currentTime);
	void makeFishAppear();
	bool GetIsActive();
};

