#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <vector>
#include "barClasses.h"
#include <typeinfo>

int main()
{
    
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");

    std::string spritePath = "resources/sprites/";
    
    Spawner spiritSpawner(sf::Vector2<int>(200, 200), spritePath + "vodka.png", 0);
    Spawner SodaSpawner(sf::Vector2<int>(300, 300), spritePath + "soda.jpg", 1);
    Spawner oldFashionedSpawner(sf::Vector2<int>(400, 400), spritePath + "glass1.jpg", 2);
    std::vector<Spawner> spawnerCollisions{ spiritSpawner, SodaSpawner, oldFashionedSpawner };
    Person person(sf::Vector2<int>(100,100));
    
    std::vector<Drawable> drawList{ spiritSpawner, SodaSpawner, oldFashionedSpawner, person};
    
 
    Item* selected = NULL;
    //std::vector<OldFashioned> glasses;
    
    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    
                    for (Spawner x : spawnerCollisions) {
                        if (x.mouseCollision(sf::Mouse::getPosition(window))) {
                            std::cout << "yipee" << std::endl;
                            selected = x.spawn(sf::Mouse::getPosition(window));
                            
                        }

                    }
                    

                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (selected) {
                        selected = NULL;
                        
                    }
                }

            }
            if (event.type == sf::Event::MouseMoved){
                if (selected) {
                    selected->update(sf::Mouse::getPosition(window));
                    //std::cout << sf::Mouse::getPosition(window).x << std::endl;
                }

            }
        }
        window.clear();

        
        for (Drawable x : drawList) 
             x.draw(window);
        
        if (selected) {
            selected->draw(window);
        }
        window.display();
    }
}

