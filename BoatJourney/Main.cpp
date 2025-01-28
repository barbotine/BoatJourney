#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Cloud.h"
#include "Boat.h"

using namespace std;
using namespace sf;


int main()
{
    VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    unsigned int screenWidth = desktopMode.size.x;
    unsigned int screenHeight = desktopMode.size.y;

    RenderWindow window(desktopMode, "Plein écran");

    RectangleShape background(sf::Vector2f(window.getSize()));
    Vector2f backgroundPosition(0.f, 0.f);
    background.setPosition(backgroundPosition);

    sf::Texture bg, cloudTex1, cloudTex2;
    if (!bg.loadFromFile("../assets/texture/bg.jpg") ||
        !cloudTex1.loadFromFile("../assets/texture/cloud.png") ||
        !cloudTex2.loadFromFile("../assets/texture/cloud3.png")) {
        return -1;
    }
    vector<Cloud> clouds;
    Cloud cloud = Cloud(Vector2f(500.f, 200.f), cloudTex1, 50);
    Cloud cloud2 = Cloud(Vector2f(0.f, 0.f), cloudTex2, 50);
    Cloud cloud3 = Cloud(Vector2f(500.f, 0.f), cloudTex1, 50);
    Cloud cloud4 = Cloud(Vector2f(1000.f, 0.f), cloudTex2, 50);

    clouds.push_back(cloud);
    clouds.push_back(cloud2);
    clouds.push_back(cloud3);
    clouds.push_back(cloud4);

   
    sf::Shader shader;
    if (!shader.loadFromFile("../assets/shaders/water_shader.frag", sf::Shader::Type::Fragment)) {
        std::cerr << "Erreur lors du chargement du shader !" << std::endl;
        return -1;
    }
    
    Color color = sf::Color::Blue;
    Clock clock;


    float time = clock.getElapsedTime().asSeconds();
    
    while(window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        time = clock.getElapsedTime().asSeconds();
      
        shader.setUniform("time", time);
        shader.setUniform("resolution", sf::Vector2f(window.getSize()));
        shader.setUniform("backgroundTex", bg);
        
        window.clear();
        window.draw(background, &shader);
  
        Boat boat = Boat(Vector2f(400.f, 400.f), "../assets/texture/boat.png");
       
        boat.draw(window);
       
        for (Cloud& cloud : clouds)
        {
            cloud.update(window);
            cloud.draw(window);
        }

        window.display();
    }  
    return 0; 
}