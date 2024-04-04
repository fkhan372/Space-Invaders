#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <stdlib.h>
#include <SFML/Audio.hpp>
#include "playerShip.h"
#include "enemy.h"
#include "powerUp.h"

enum class GameUI
{
    mainMenu,
    gameActive,
    gameOver
};

int main()
{
    //Set the window size
    sf::RenderWindow window(sf::VideoMode(600, 800), "Space Invaders");
    
    //Initialize clocks
    sf::Clock clock;
    sf::Clock timeSinceStart;
    float timeAlive = 0;

    //Load menu on game start
    GameUI ui = GameUI::mainMenu;

    //Creating a list of enemies and powerups
    std::vector<enemy> enemies;
    std::vector<powerUp> powerUps;

    //Setting textures
    sf::Texture playerTexture;
    playerTexture.loadFromFile("Batman.png");
    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("Joker.png");
    sf::Texture powerUpTexture;
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("Background.png");
    sf::Sprite backgroundSprite(backgroundTexture);
    sf::Texture backgroundMTexture;
    backgroundMTexture.loadFromFile("BackgroundM.png");
    sf::Sprite backgroundMSprite(backgroundMTexture);

    //Setting music
    sf::Music music;
    music.openFromFile("action_music.mp3");
    music.play();

    //Setting initial spawn values as well as rand to randomize the spawn location
    float spawnPoints[12] = { 0.0f, 50.0f, 100.0f, 150.0f, 200.0f, 250.0f, 300.0f, 350.0f, 400.0f, 450.0f, 500.0f, 550.0f};
    int randInt;
    float spawnPoint;

    //Seeding random number to generate different results
    srand(time(NULL));

    //Initializing initial enemy values (health, speed, max amount)
    int maxEnemies = 3;
    float enemySpeed = 10.0f;
    int enemyHealth = 1;
    int waveCount = 0;

    //Initializing player health
    int playerHealth = 5;

    //CURRENT POWERUPS IMPLEMENTED: FireUp, HealthUp, KillAll, SpeedDown
    const char* powerUpType[4] = { "FireUp", "HealthUp", "KillAll", "SpeedDown" };

    //Initializing player into the game
    playerShip p1(sf::Vector2f(50.0f, 25.0f), sf::Vector2f(275.0f, 775.0f), playerTexture, sf::Color::Yellow, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Space);

    //enemy::enemy(sf::Vector2f size, sf::Vector2f initialPosition, sf::Texture& texture, sf::Color color, float health, float speed)
    //enemy e1(sf::Vector2f(50.0f, 50.0f), sf::Vector2f(275.0f, 0.0f), texture2, sf::Color::Yellow, 3, 10.0f);
    //Pushing in e1 into the list of enemies
    //enemies.push_back(e1);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (ui == GameUI::mainMenu && event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Key::Space)
                {
                    ui = GameUI::gameActive;
                }
            }
            else if (ui == GameUI::gameOver && event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Key::Space)
                {
                    ui = GameUI::mainMenu;
                    playerHealth = 5;
                }
            }
        }

        if (ui == GameUI::mainMenu)
        {
            //Set window color/background
            window.clear(sf::Color::White);
            window.draw(backgroundMSprite);

            float centre = window.getSize().x / 2.0f;
            float textSize;

            sf::Font font;
            font.loadFromFile("arial.ttf");

            sf::Text title("Space Invaders", font, 50); // Text, font, size
            title.setFillColor(sf::Color::White);
            title.setStyle(sf::Text::Bold);
            title.setStyle(sf::Text::Underlined);
            textSize = title.getLocalBounds().width;
            title.setPosition((centre - textSize / 2.0f), 100);

            sf::Text instruction("Press Spacebar to Start", font, 30);
            instruction.setFillColor(sf::Color::White);
            textSize = instruction.getLocalBounds().width;
            instruction.setPosition((centre - textSize / 2.0f), 200);

            sf::Text author("By: Faisal Khan", font, 20);
            author.setFillColor(sf::Color::White);
            textSize = author.getLocalBounds().width;
            author.setPosition((centre - textSize / 2.0f), 700);

            window.draw(title);
            window.draw(instruction);
            window.draw(author);

            window.display();
        }
        else if (ui == GameUI::gameActive)
        {
            //Start the delta time clock and the time since start clocks
            float deltaTime = clock.restart().asSeconds();
            float totalTime = timeSinceStart.getElapsedTime().asSeconds();
            
            //Display total time the player is alive
            timeAlive += deltaTime;

            sf::Font font;
            font.loadFromFile("arial.ttf");

            sf::Text timeLived("Time Alive: " + std::to_string(timeAlive), font, 20);
            timeLived.setFillColor(sf::Color::White);
            timeLived.setPosition(200, 700);

            sf::Text livesLeft("Lives Left: " + std::to_string(playerHealth), font, 20);
            livesLeft.setFillColor(sf::Color::White);
            livesLeft.setPosition(230, 725);

            //Updating player actions
            p1.Update(deltaTime);

            //Set window color/background
            window.clear(sf::Color::White);
            window.draw(backgroundSprite);

            //Draw player shape
            window.draw(p1.getShape());

            //Condition to spawn wave of enemies every 5 seconds
            if (totalTime >= 5.0f)
            {
                //Randomizes a value between 1 and max enemies (default 3)
                std::cout << "REACHED 5 SECONDS" << std::endl;
                int i = rand() % maxEnemies + 1;
                std::cout << "Number of enemies: " << i << std::endl;
                //Using a for loop to save the enemy objects generated into a list of enemies to be drawn later
                for (i; i > 0; i--)
                {
                    //Randomizes a spawn location from the spawnPoints list between 0 and 11
                    randInt = rand() % 12;
                    spawnPoint = spawnPoints[randInt];
                    std::cout << "Spawn point: " << spawnPoint << std::endl;
                    enemy e1(sf::Vector2f(50.0f, 50.0f), sf::Vector2f(spawnPoint, 0.0f), enemyTexture, sf::Color::Yellow, enemyHealth, enemySpeed);
                    //Pushing in e1 into the list of enemies
                    enemies.push_back(e1);
                }
                std::cout << "~~~~~~~~~~~~~~~~~~~~" << std::endl;
                //This is to count to 30 in increments of 5 since we are restarting the clock every 5 seconds
                waveCount += 1;
                timeSinceStart.restart();
            }

            //Once the timer (wavecount 6) reaches 30, give a powerup to the enemies and player
            if (waveCount == 2)
            {
                std::cout << "REACHED 30 SECONDS" << std::endl;
                //Enemy power ups
                enemySpeed += 25.0f;
                enemyHealth += 1;

                //Player powerups
                randInt = rand() % 12;
                std::cout << randInt << std::endl;
                spawnPoint = spawnPoints[randInt];
                randInt = rand() % 4;
                std::cout << randInt << std::endl;
                //powerType = powerUpType[randInt];
                powerUpTexture.loadFromFile(std::string(powerUpType[randInt]) + ".png");

                powerUp pow(sf::Vector2f(50.0f, 50.0f), sf::Vector2f(spawnPoint, 0.0f), powerUpTexture, powerUpType[randInt]);
                powerUps.push_back(pow);

                //Reset wave count
                waveCount = 0;
            }

            //Check the collection of projectiles and spawn if theres any
            for (const auto& projectile : p1.getProjectiles())
            {
                window.draw(projectile);
            }

            //Update and draw enemies from the list of enemies
            for (auto& enemy : enemies)
            {
                enemy.Update(deltaTime);
                window.draw(enemy.getShape());

                //Check enemy collision with projectile
                for (auto x = p1.getProjectiles().begin(); x != p1.getProjectiles().end();)
                {
                    //If theres been a collision with a projectile, it will reduce the health of the enemy by 1
                    if (enemy.checkCollision(*x))
                    {
                        std::cout << "Collision is detected" << std::endl;
                        std::cout << enemy.getHealth();
                        //If the enemies health is 0, use the killEnemy function to erase the enemy 
                        if (enemy.getHealth() <= 0)
                        {
                            enemy.killEnemy(enemies);
                        }
                        //Remove the projectile from the collection upon collision
                        x = p1.getProjectiles().erase(x);
                    }
                    //Go to the next projectile
                    else
                    {
                        ++x;
                    }
                }

                //Check collision with bottom of the screen
                for (auto y = enemies.begin(); y != enemies.end();)
                {
                    //Check if the enemy reached the bottom
                    if (y->getShape().getPosition().y > 750)
                    {
                        //Reduce players health by 1 for each enemy reaching the bottom until 0
                        std::cout << "You lost a life!" << std::endl;
                        playerHealth -= 1;
                        //If players health is 0, close the game window
                        if (playerHealth <= 0)
                        {
                            std::cout << "Game over!" << std::endl;
                            ui = GameUI::gameOver;
                        }
                        //Erase the enemy once it reaches the bottom
                        y = enemies.erase(y);
                    }
                    //Go to the next enemy
                    else
                    {
                        ++y;
                    }
                }
            }

            for (auto z = powerUps.begin(); z != powerUps.end();)
            {
                auto& powerUp = *z;

                powerUp.Update(deltaTime);
                window.draw(powerUp.getShape());

                //Check if player collided with the power up
                if (powerUp.checkCollision(p1.getShape()))
                {
                    std::cout << "Player collected powerup!" << std::endl;

                    //Accordingly add the power up that was collected
                    if (powerUp.getType() == "FireUp")
                    {
                        std::cout << "Fire rate increased!" << std::endl;
                        p1.IncreaseFireRate();
                    }
                    else if (powerUp.getType() == "HealthUp")
                    {
                        std::cout << "Health increased!" << std::endl;
                        playerHealth += 1;
                    }
                    else if (powerUp.getType() == "SpeedDown")
                    {
                        std::cout << "Enemy speed decreased!" << std::endl;
                        if (!enemySpeed <= 10.0f)
                            enemySpeed -= 25.0f;
                    }
                    else if (powerUp.getType() == "KillAll")
                    {
                        std::cout << "All enemies eliminated!" << std::endl;
                        enemies.clear();
                    }

                    z = powerUps.erase(z);
                }
                //Erase the power up if it touches the floor
                else if (powerUp.getShape().getPosition().y > 800)
                {
                    std::cout << "PowerUp expired!" << std::endl;
                    z = powerUps.erase(z);
                }
                //Go to the next power up
                else {
                    ++z;
                }
            }

            window.draw(timeLived);
            window.draw(livesLeft);

            window.display();
        }
        else if (ui == GameUI::gameOver)
        {
            window.clear();

            float centre = window.getSize().x / 2.0f;
            float textSize;

            sf::Font font;
            font.loadFromFile("arial.ttf");

            sf::Text title("Game Over!", font, 50);
            title.setFillColor(sf::Color::White);
            title.setStyle(sf::Text::Bold);
            title.setStyle(sf::Text::Underlined);
            textSize = title.getLocalBounds().width;
            title.setPosition((centre - textSize / 2.0f), 100);

            sf::Text exit("Press Spacebar to return to menu", font, 30);
            exit.setFillColor(sf::Color::White);
            textSize = exit.getLocalBounds().width;
            exit.setPosition((centre - textSize / 2.0f), 300);

            sf::Text score("Total Time: " + std::to_string(timeAlive), font, 20);
            score.setFillColor(sf::Color::White);
            textSize = score.getLocalBounds().width;
            score.setPosition((centre - textSize / 2.0f), 600);

            window.draw(title);
            window.draw(exit);
            window.draw(score);

            window.display();
        }
    }

    return 0;
}
