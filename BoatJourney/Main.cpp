#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Cloud.h"
#include "Boat.h"
#include "Sun.h"
#include "CloudManager.h"
#include "SeaManager.h"
#include "Button.h"
#include "Character.h"
#include "Resource.h"
#include "Shark.h"
#include "Fish.h"
#include "Utils.h"
#include "FishManager.h"
#include "ProgressBar.h"
#include "HungerBar.h"
#include "Game.h"
#include "SharkManager.h"

using namespace std;
using namespace sf;

const unsigned int FIXED_WIDTH = 1920;
const unsigned int FIXED_HEIGHT = 1080;

bool initializeShader(sf::Shader& shader, const string& shaderFilePath, const sf::Vector2f& resolution, sf::Texture& bgTexture) {
    if (!shader.loadFromFile(shaderFilePath, sf::Shader::Type::Fragment)) {
        throw "Can't load shader";
    }
    shader.setUniform("resolution", resolution);
    shader.setUniform("backgroundTex", bgTexture);
    return true;
}

void updateShaderUniforms(sf::Shader& shader, float time) {
    shader.setUniform("time", time);
}

void addTextOnGameOverScreen()
{
}

int main()
{
    VideoMode desktopMode = VideoMode::getDesktopMode();
    unsigned int screenWidth = desktopMode.size.x;
    unsigned int screenHeight = desktopMode.size.y;

    RenderWindow window(VideoMode({ FIXED_WIDTH, FIXED_HEIGHT }), "Boat Journey", sf::Style::Titlebar | sf::Style::Close);
   
    window.setVerticalSyncEnabled(true);
    Vector2u windowSize = window.getSize();
    Vector2f resolution(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));

    RectangleShape background(resolution);

    SeaManager seaService = SeaManager();

    const sf::Vector2f originalResolution(screenWidth, screenHeight);

    Texture bg, cloudText1, cloudText2, sunText, boatTexture, characterTexture, sharkTexture2, solarEnergyTexture, heartTexture, sharkTexture, fishTexture1, foodSupplyTexture;
    if (!bg.loadFromFile("../assets/texture/bg.jpg") ||
        !cloudText1.loadFromFile("../assets/texture/cloud1.png") ||
        !cloudText2.loadFromFile("../assets/texture/cloud2.png") ||
        !sunText.loadFromFile("../assets/texture/sun.png") ||
        !boatTexture.loadFromFile("../assets/texture/boat.png") ||
        !characterTexture.loadFromFile("../assets/texture/sailor.png") ||
        !solarEnergyTexture.loadFromFile("../assets/texture/solarEnergy.png") ||
        !heartTexture.loadFromFile("../assets/texture/heart.png") ||
        !sharkTexture.loadFromFile("../assets/texture/shark.png") ||
        !sharkTexture2.loadFromFile("../assets/texture/pirhana.png") ||
        !fishTexture1.loadFromFile("../assets/texture/fish.png") ||
        !foodSupplyTexture.loadFromFile("../assets/texture/foodSupply.png")
        ) {
        throw "Can't load";
    }

    sf::Font font;
    if (!font.openFromFile("../assets/font/Roboto-Italic.ttf"))
    {
        std::cerr << "Erreur: Impossible de charger la police 'assets/arial.ttf'\n";
        std::cerr << "Verifie que le fichier existe et que le chemin est correct.\n";
        return -1;
    }

    Texture fishTexture2, fishTexture3, fishTexture4, fishTexture5, fishTexture6;
    if (!fishTexture2.loadFromFile("../assets/texture/nemo.png") ||
        !fishTexture3.loadFromFile("../assets/texture/dory.png") ||
        !fishTexture4.loadFromFile("../assets/texture/horse-lion.png") ||
        !fishTexture5.loadFromFile("../assets/texture/fish2.png") ||
        !fishTexture6.loadFromFile("../assets/texture/fish4.png") 
        )
    {
        throw "Can't load";
    }





    RectangleShape gameOverOverlay;
    gameOverOverlay.setSize(resolution);
    gameOverOverlay.setFillColor(sf::Color(0, 0, 0, 180)); // Semi-transparent black

    Text gameOverText(font);
    gameOverText.setCharacterSize(80);
    gameOverText.setString("GAME OVER");
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);

    // Center text
    FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(Vector2f(textRect.position.x + textRect.size.x / 2.0f, textRect.position.y + textRect.size.y/ 2.0f));
    gameOverText.setPosition(Vector2f(resolution.x / 2.0f, resolution.y / 2.0f - 50.f));

    float button_x = resolution.x / 2.0f - 100.f;
    float button_y = resolution.y / 2.0f + 50.f;
    Button replayButton = Button(button_x, button_y, 200.f, 60.f, sf::Color::Green, "Replay");

        sf::Shader shader;
        if (!initializeShader(shader, "../assets/shaders/water_shader.frag", sf::Vector2f(window.getSize()), bg)) {
            throw "Can't load shader texture";
        }

        Clock clock;
        float currentTime = 0.0f;
        float previousTime = 0.0f;
        float deltaTime = 0.0f;

        Game game = Game();

        Color buttonFillColor(205, 133, 63);
        Color buttonOutlineColor(139, 69, 19);

        Button solarActivityButton = Button(1000, 950, 200, 50, buttonFillColor, "Solar recharge");
        solarActivityButton.setOutlineColor(buttonOutlineColor);
        solarActivityButton.setOutlineThickness(3);

        Button eatingActivityButton = Button(750, 950, 200, 50, buttonFillColor, "Eating");
        eatingActivityButton.setOutlineColor(buttonOutlineColor);
        eatingActivityButton.setOutlineThickness(3);

        CloudManager cloudService = CloudManager();
        vector<Cloud> clouds = cloudService.createClouds(cloudText1, cloudText2);

        FishManager fishService = FishManager();
        vector<Fish> fishes = fishService.createFishes(fishTexture1, fishTexture2, fishTexture3, fishTexture4, fishTexture5, fishTexture6);

        Character character = Character(Vector2f(1800.f, 780.f), characterTexture);

        Vector2f boatInitialPos(resolution.x / 2.f, resolution.y * 0.5f);
        Boat boat = Boat(boatInitialPos, boatTexture);
        boat.setOriginToBottomCenter();

        Sun sun = Sun(Vector2f(100, 500.f), sunText, 250.f);
        Resource solarEnergy = Resource(Vector2f(1750.f, 780.f), solarEnergyTexture, Vector2f(1750.f, 780.f), character.getSolarResource());
        Resource lifespan = Resource(Vector2f(1750.f, 850.f), heartTexture, Vector2f(1750.f, 850.f), character.getLifespan());
        Resource foodSupply = Resource(Vector2f(1750.f, 900.f), foodSupplyTexture, Vector2f(1750.f, 950.f), character.getFoodSupply());
        Shark shark = Shark(Vector2f(1900.f, 1000.f), sharkTexture, 300.f);

        SharkManager sharkService = SharkManager();
        vector<Shark> sharks = sharkService.createSharks(sharkTexture, sharkTexture2, sharkTexture2);

        HungerBar hungerBar(50, 50);

        bool isSomeSharkColliding = false;
        
        while (window.isOpen())
        {
            previousTime = currentTime;
            currentTime = clock.getElapsedTime().asSeconds();
            deltaTime = currentTime - previousTime;

            while (const std::optional<sf::Event> event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();

                if (event->is<sf::Event::Resized>())
                {
                    //if (window.getSize() != previousSize)
                    //{
                    //    //auto const size = window.getSize();
                    //    //ratio = (float)size.x / (float)size.y;
                    //    //// Log the change
                    //    //std::cout << "Window resized to " << previousSize.x << "x" << previousSize.y << std::endl;
                    //}
                }
            }


            switch (game.getCurrentState())
            {
                case GameState::INGAME:
                {
                    if (solarActivityButton.isClicked(window))
                    {
                        character.makingSolarEnergy(sun, window);
                        solarEnergy.setText(character.getSolarResource());
                    }

                    if (eatingActivityButton.isClicked(window))
                    {
                        character.Eat();
                        foodSupply.setText(character.getFoodSupply());
                        if (character.getFoodSupply() > 0)
                        {
                            hungerBar.FillTheBar();
                        }
                    }
                    isSomeSharkColliding = false;
                    for (Shark& shark : sharks)
                    {
                        if (shark.getSprite().getGlobalBounds().findIntersection(boat.getSprite().getGlobalBounds()))
                        {
                            
                            
                            if (!shark.getSharkBoatCollisionDetected())
                            {
                                isSomeSharkColliding = true;
                                character.losingLifeSpan(game);
                                lifespan.setText(character.getLifespan());
                                shark.setSharkBoatCollisionDetected(true); 
                                std::cout << "Collision détectée !" << std::endl;
                            }
                        }
                        else
                        {
                            shark.setSharkBoatCollisionDetected(false);
                        }
                    }
                    for (Shark& shark : sharks)
                    {
                        if (shark.getIsActive() && Utils::isClicked(shark.getSprite(), window, shark.getWasSharkPressed())) {
                            shark.incrementeClick();
                            if (shark.getSharkClicks() >= shark.getSharkMaxClicks()) {
                                shark.makeSharkDisappear(currentTime);
                                shark.setSharkClicks(0);

                            }
                        }
                    }

                    if (isSomeSharkColliding)
                    {
                        boat.getSprite().setColor(Color::Red);
                    }
                    else {
                        boat.getSprite().setColor(Color::White);
                    }
                   

                    for (Fish& fish : fishes)
                    {
                        if (Utils::isClicked(fish.getSprite(), window, fish.getWasClicked()))
                        {
                            character.gettingFish();
                            foodSupply.setText(character.getFoodSupply());
                            fish.makeFishDisappear(currentTime);
                        }
                    }

                    if (hungerBar.GetCurrentHunger() == 0)
                    {
                        game.setCurrentState(GameState::GAMEOVER);
                    }

                    hungerBar.EmptyTheBar(deltaTime);

                    for (Shark& shark : sharks)
                    {
                        shark.makeSharkAppear(currentTime);
                    }

                    updateShaderUniforms(shader, currentTime);

                    float boatX = boat.getPosition().x / resolution.x;

                    float waveHeight = seaService.calculateWaveHeight(boat.getSprite().getPosition().x, currentTime, Vector2f(window.getSize().x, window.getSize().y));

                    float x = boat.getSprite().getPosition().x;
                    float y = (waveHeight + 0.52) * resolution.y;

                    boat.setPosition(Vector2f(x, y), window.getSize(), originalResolution);

                    window.clear();
                    window.draw(background, &shader);

                    boat.draw(window);



                    for (Shark& shark : sharks)
                    {
                        if (shark.getIsActive()) {
                            
                            shark.update(window, deltaTime, boat);
                            shark.draw(window);
                        }
                    }
                  
                    sun.update(window, deltaTime);
                    sun.draw(window);

                    for (Cloud& cloud : clouds)
                    {
                        cloud.update(window, deltaTime);
                        cloud.draw(window);
                    }

                    for (Fish& fish : fishes)
                    {
                        fish.update(window, currentTime, deltaTime);
                        fish.draw(window);
                    }
                    hungerBar.update(hungerBar.GetCurrentHunger(), hungerBar.GetMaxHunger());
                    hungerBar.draw(window);
                    character.draw(window);
                    solarEnergy.draw(window);
                    lifespan.draw(window);
                    foodSupply.draw(window);
                    solarActivityButton.draw(window);
                    eatingActivityButton.draw(window);
                    break;
                }
                case GameState::GAMEOVER:
                {
                    window.draw(gameOverOverlay);
                    window.draw(gameOverText);
                    replayButton.draw(window);

                    break;
                }

            }
            
            window.display();
        }
        return 0;
    }