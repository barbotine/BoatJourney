#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Actor
{

	protected:
		Vector2f position;
		Sprite sprite;
		Texture texture;

	public:
		Actor(Vector2f position, string& actorTex);
		Actor(Vector2f position, Texture& actorTex);
		virtual void update(float deltaTime);
		void draw(RenderWindow& window);
		Vector2f getPosition();
		void setPosition(Vector2f position);
		void centerSpriteOrigin();
		virtual ~Actor() = default;
};

