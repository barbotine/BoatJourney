#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;


int main()
{
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int screenWidth = desktopMode.size.x;
    unsigned int screenHeight = desktopMode.size.y;

    sf::RenderWindow window(desktopMode, "Plein écran");

    sf::Texture texture;
    if (!texture.loadFromFile("C:/Main/BoatJourney/assets/texture/boat.png")){
        return -1;
    }
 
    sf::Sprite boat(texture);

    float positionBoatX = 400.f;
    float positionBoatY = window.getSize().y * 0.5f;

    sf::Vector2f position(positionBoatX, positionBoatY);
    boat.setPosition(position);

    while(window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear();
        window.draw(boat);
        window.display();
    }
    return 0; 
}