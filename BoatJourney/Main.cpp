#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Cloud.h"
#include "Boat.h"

using namespace std;
using namespace sf;


void manageCloud(RenderWindow& window) {
    vector<Cloud> clouds;
    Cloud cloud = Cloud(window, Vector2f(500.f, 200.f), "../assets/texture/cloud.png");
    Cloud cloud2 = Cloud(window, Vector2f(0.f, 0.f), "../assets/texture/cloud2.png");

    clouds.push_back(cloud);
    clouds.push_back(cloud2);

    for (Cloud& cloud : clouds)
    {
        cloud.draw(window);
    }
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
    if (!bg.loadFromFile("../assets/texture/bg.jpg")){
        return -1;
    }
   
    sf::Shader shader;

    if (!shader.loadFromFile("../assets/shaders/water_shader.frag", sf::Shader::Type::Fragment)) {
        std::cerr << "Erreur lors du chargement du shader !" << std::endl;
        return -1;
    }
    
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
        
        window.clear();
        window.draw(background, &shader);
        Boat boat = Boat(window, Vector2f(400.f, 400.f), "../assets/texture/boat.png");
        boat.draw(window);

        //manageCloud(window);

        vector<Cloud> clouds;
        Cloud cloud = Cloud(window, Vector2f(500.f, 200.f), "../assets/texture/cloud.png");
        Cloud cloud2 = Cloud(window, Vector2f(0.f, 0.f), "../assets/texture/cloud3.png");
        Cloud cloud3 = Cloud(window, Vector2f(500.f, 0.f), "../assets/texture/cloud.png");
        Cloud cloud4 = Cloud(window, Vector2f(1000.f, 0.f), "../assets/texture/cloud3.png");

        clouds.push_back(cloud);
        clouds.push_back(cloud2);
        clouds.push_back(cloud3);
        clouds.push_back(cloud4);

        for (Cloud& cloud : clouds)
        {
            cloud.draw(window);
        }

        window.display();
    }  
    return 0; 
}