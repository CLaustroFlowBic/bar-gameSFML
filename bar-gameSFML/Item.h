#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "barClasses.h"

const int numberOfItems = 3;

//Base class for Item Objects
class Item : public Drawable {
	std::string name;
public:
	Item() {};
	Item(sf::Vector2<int> pos);
	virtual Item* clone(sf::Vector2<int> pos) = 0;
	void update(sf::Vector2<int> pos);
	sf::Vector2<int> getPos();
	virtual std::string getName() = 0;

};

//Spirit Item Object
class Spirit : public Item {
	std::string name = "spirit";
public:
	Spirit() {};
	Spirit(sf::Vector2<int> pos);
	Item* clone(sf::Vector2<int> pos) { return new Spirit(pos); }
	std::string getName() { return name; };
};

//Soda Item Objects
class Soda : public Item {
	std::string name = "soda";
public:
	Soda() {};
	Soda(sf::Vector2<int> pos);
	Item* clone(sf::Vector2<int> pos) { return new Soda(pos); }
	std::string getName() { return name; };

};


class ItemSpawner : public Drawable {
private:
	static Item* i_prototypes[numberOfItems];
	int choice;

public:
	ItemSpawner(sf::Vector2<int> pos, std::string spritePath, int _choice) : Drawable(pos) {
		image.loadFromFile(spritePath);
		sprite.setTexture(image);
		choice = _choice;
	}
	bool mouseCollision(sf::Vector2<int> pos) {
		if (sprite.getGlobalBounds().contains(pos.x, pos.y)) {
			return true;

		}
		else
			return false;
	}
	Item* spawn(sf::Vector2<int> pos) {

		return i_prototypes[choice]->clone(pos);
	};
};

#endif