#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Boat.h"
#include "Cloud.h"

using namespace std;
using namespace sf;


vector<Sprite> manageCloud(RenderWindow& window, Texture& cloudTexture) {

    vector<Sprite> clouds;
    if (!cloudTexture.loadFromFile("../assets/texture/cloud.png")) {
        throw runtime_error("Texture not working");
    }

    float cloudX = 400.f;
    float cloudY = window.getSize().y * 0.1f;

    Vector2f cloudPosition(cloudX, cloudY);
    Sprite cloud(cloudTexture);
    cloud.setPosition(cloudPosition);

    clouds.push_back(cloud);
    return clouds;
}

int main()
{
    VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int screenWidth = desktopMode.size.x;
    unsigned int screenHeight = desktopMode.size.y;

    RenderWindow window(desktopMode, "Plein écran");

    RectangleShape background(sf::Vector2f(window.getSize()));
    Vector2f backgroundPosition(0.f, 0.f);
    background.setPosition(backgroundPosition);

    sf::Texture bg, cloudTexture;
    if (!bg.loadFromFile("../assets/texture/bg.jpg") ||
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
    
    Vector2f positionBoat(400, 400);
  
    float cloudX = 400.f;
    float cloudY = window.getSize().y * 0.1f;

    Vector2f cloudPosition(cloudX, cloudY);
 /*   Boat boat1;
    Actor(positionBoat, "../assets/texture/boat.png");*/
    Color color = sf::Color::Blue;
    Clock clock;
    

    while(window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }


        float time = clock.getElapsedTime().asSeconds();
      
        shader.setUniform("time", time);
        shader.setUniform("resolution", sf::Vector2f(window.getSize()));
        shader.setUniform("backgroundTex", bg);

        Texture cloudTexture;
        vector<Sprite> clouds;
        clouds = manageCloud(window, cloudTexture);
        
        

        window.clear();
        window.draw(background, &shader);
        Cloud cloud = Cloud(window);
        window.draw(cloud.getSprite());


     /*   boat1.draw(window);*/


       /* for (int i = 0; i < clouds.size(); i++)
        {
            window.draw(clouds[i]);
        }*/

        window.display();
    }
    return 0; 
}