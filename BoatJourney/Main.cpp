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

    sf::RectangleShape background(sf::Vector2f(window.getSize()));
    sf::Vector2f backgroundPosition(0.f, 0.f);
    background.setPosition(backgroundPosition);

    sf::Texture boatTexture, bg, cloudTexture;
    if (!boatTexture.loadFromFile("../assets/texture/boat.png") || 
        !bg.loadFromFile("../assets/texture/bg.jpg") ||
        !cloudTexture.loadFromFile("../assets/texture/cloud.png")
        ){
        return -1;
    }
 
    // Charger le shader
    sf::Shader shader;

    if (!shader.loadFromFile("../assets/shaders/water_shader.frag", sf::Shader::Type::Fragment)) {
        std::cerr << "Erreur lors du chargement du shader !" << std::endl;
        return -1;
    }
    sf::Sprite boat(boatTexture);
    sf::Sprite cloud(cloudTexture);

    float positionBoatX = 400.f;
    float positionBoatY = window.getSize().y * 0.7f;

    sf::Vector2f position(positionBoatX, positionBoatY);
    boat.setPosition(position);

    float cloudX = 400.f;
    float cloudY = window.getSize().y * 0.1f;

    sf::Vector2f cloudPosition(cloudX, cloudY);
    boat.setPosition(cloudPosition);

    sf::Color color = sf::Color::Blue;

    sf::Clock clock;

    sf::Angle rotationAngle = sf::degrees(2);

    float boatWidth = boat.getLocalBounds().size.x / 2;
    float boatHeight = boat.getLocalBounds().size.y / 2;

    sf::Vector2f boatOrigin(boatWidth, boatHeight);

    boat.setOrigin(boat.getLocalBounds().size / 2.0f);

    while(window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float time = clock.getElapsedTime().asSeconds();
      

        // Passer le temps au shader
        shader.setUniform("time", time);
        shader.setUniform("resolution", sf::Vector2f(window.getSize()));
        shader.setUniform("backgroundTex", bg);

        window.clear();
        window.draw(background, &shader);
        window.draw(boat);
        window.draw(cloud);
        window.display();
    }
    return 0; 
}