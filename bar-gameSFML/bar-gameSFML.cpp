#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <time.h>

#include "barClasses.h"
#include "Item.h"
#include "Glass.h"
#include "FillingMinigame.h"


//main file for this project

typedef struct {
    bool focusedCollision;
    bool unfocusedCollision;
} GlassCollisionState;

std::string genOrder(int selection, int& amount) {

    switch (selection) {
    case 0:
        amount = 50;
        return "vodka";
    case 1:
        amount = 50;
        return "gin";
    case 2:
        amount = 50;
        return "darkrum";
    case 3:
        amount = 50;
        return "soda";
    }
    return "";
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Bar-Game");

    std::string spritePath = "resources/sprites/";
    
    ItemSpawner spiritSpawner(sf::Vector2<int>(200, 300), spritePath + "vodka.png", "vodka");
    ItemSpawner SodaSpawner(sf::Vector2<int>(300, 300), spritePath + "soda.jpg", "soda");
    ItemSpawner darkRum(sf::Vector2<int>(400, 300), spritePath + "darkrum.png", "darkrum");
    ItemSpawner gin(sf::Vector2<int>(500, 300), spritePath + "gin.png", "gin");
    std::vector<ItemSpawner> itemSpawnerCollisions{ spiritSpawner, SodaSpawner, darkRum, gin };

    
    GlassSpawner oldFashionedSpawner(sf::Vector2<int>(600, 385), spritePath + "rocks_empty.png", 0);
    std::vector<GlassSpawner> GlassSpawnerCollisions{ oldFashionedSpawner };


    srand(time(NULL));
    std::list<Person> personStack;
    for (int i = 0; i < 20; ++i) {
        int amount1 = 0;
        std::string drink1 = genOrder(rand() % 4, amount1);
        int amount2 = 0;
        std::string drink2 = genOrder(rand() % 4, amount2);
        std::map<std::string, int> temp;

        temp.insert(std::pair<std::string, int>(drink1, amount1));
        temp.insert(std::pair<std::string, int>(drink2, amount2));

        Person *person = new Person(sf::Vector2<int>(590, 100),  temp);
        personStack.push_back((*person));
        temp.clear();
        std::cout << person << std::endl;
        //std::cout << &personStack.front() << std::endl;
    }
    
    
    std::vector<Drawable> drawList{ spiritSpawner, SodaSpawner, oldFashionedSpawner, darkRum, gin };
    
 
    Item* itemSelected = NULL;
    Glass* glassSelected = NULL;
    Glass* glassFill = NULL;
    Item* itemFill = NULL;
    FillingMiniGame* minigameActivated = NULL;
    std::list<Glass*> glasses;
    
    int glassid = 0;
    GlassCollisionState glassCollisionState;
    glassCollisionState.focusedCollision = false;
    glassCollisionState.unfocusedCollision = false;


    sf::Event event;
    while (window.isOpen()) {
        
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (!minigameActivated) {

                    
                        for (ItemSpawner x : itemSpawnerCollisions) {
                            if (x.mouseCollision(sf::Mouse::getPosition(window))) {
                                itemSelected = x.spawn(sf::Mouse::getPosition(window));
                            }
                        }

                        //might be able to get rid of this
                        for (GlassSpawner x : GlassSpawnerCollisions) {
                            if (x.mouseCollision(sf::Mouse::getPosition(window))) {
                                glassSelected = x.spawn(sf::Mouse::getPosition(window), glassid);
                                glasses.insert(glasses.begin(), glassSelected);
                                glassid++;

                            }
                        }

                        if (!glasses.empty()) {
                            //collison layering logic for glasses
                            //TODO: refactoring
                            std::list<Glass*>::iterator y = glasses.begin();
                            for (auto x{ glasses.begin() }; x != glasses.end(); ++x) {
                                if ((*x)->mouseCollision(sf::Mouse::getPosition(window))) {
                                    if (x != glasses.begin()) {
                                        y = x;
                                        glassCollisionState.unfocusedCollision = true;
                                    }
                                    else {
                                        glassCollisionState.focusedCollision = true;
                                    }
                                }
                            }
                            if (glassCollisionState.unfocusedCollision) {
                                Glass* temp = *y;
                                glasses.erase(y);
                                glasses.push_front(temp);
                                glassSelected = *(glasses.begin());
                                glassCollisionState.unfocusedCollision = false;
                            }
                            if (glassCollisionState.focusedCollision) {
                                glassSelected = *(glasses.begin());
                                glassCollisionState.focusedCollision = false;
                            }
                        }
                        
                    }
                    else {
                        minigameActivated->pressed();

                    }
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (itemSelected) {
                        for (Glass* x : glasses) {
                            
                            if (x->mouseCollision(itemSelected->getPos())) {
                                
                                minigameActivated = new FillingMiniGame(sf::Mouse::getPosition(), 0.1f);
                                glassFill = x;
                                itemFill = itemSelected;
                                //free(itemSelected);
                                //itemSelected = NULL;
                            }
                                                   
                        }
                        itemSelected = NULL;
                        
                    }
                    if (glassSelected) {
                        if (personStack.front().isColliding(glassSelected->getPos().x, glassSelected->getPos().y)) {
                            std::cout << "removed Glass" << std::endl;
                            std::cout << personStack.front().getOrder() << std::endl;
                            glasses.remove(glassSelected);
                            if (personStack.front().orderChecker(glassSelected->getContents())) {
                                personStack.pop_front();
                            }
                            
                        }
                        glassSelected = NULL;
                    }
                }
                
            }

            if (event.type == sf::Event::MouseMoved){
                if (itemSelected) {
                    itemSelected->update(sf::Mouse::getPosition(window));
                }
                if (glassSelected) {
                    glassSelected->update(sf::Mouse::getPosition(window));
                }

            }
        }


        window.clear();
        personStack.front().draw(window);
        for (Drawable x : drawList) {
            x.draw(window);
        }
        
        for (auto p{ glasses.rbegin() }; p != glasses.rend(); ++p) {
            //std::cout << (*p)->id << ",";
            (*p)->draw(window);
        }
        
        


        if (itemSelected) {
            itemSelected->draw(window);
        }

        //todo: implement actually working minigame dickhead
        if (minigameActivated) {
            window.setMouseCursorVisible(false);

            minigameActivated->draw(window);
            
            if (minigameActivated->update()) {
                window.setMouseCursorVisible(true); \
                glassFill->add(minigameActivated->getAmountFilled(), itemFill);
                
                minigameActivated = NULL;
            }
        }
        
        window.display();
    }
}

