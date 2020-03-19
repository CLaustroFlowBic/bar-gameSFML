#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "barClasses.h"


//Base class for Item Objects
class Item : public Drawable {
	std::string name;
public:
	Item() {};
	Item(sf::Vector2<int> pos, std::string _name, std::string spritePath);
	//virtual Item* clone(sf::Vector2<int> pos) = 0;
	void update(sf::Vector2<int> pos);
	sf::Vector2<int> getPos();
	std::string getName() { return name; };

};

////Spirit Item Object
//class Spirit : public Item {
//	std::string name = "spirit";
//public:
//	Spirit() {};
//	Spirit(sf::Vector2<int> pos);
//	Item* clone(sf::Vector2<int> pos) { return new Spirit(pos); }
//	std::string getName() { return name; };
//};
//
////Soda Item Objects
//class Soda : public Item {
//	std::string name = "soda";
//public:
//	Soda() {};
//	Soda(sf::Vector2<int> pos);
//	Item* clone(sf::Vector2<int> pos) { return new Soda(pos); }
//	std::string getName() { return name; };
//
//};


class ItemSpawner : public Drawable {
private:
	
	int choice;
	std::string spritePath;
	std::string name;
public:
	ItemSpawner(sf::Vector2<int> pos, std::string _spritePath, std::string _name) : Drawable(pos) {
		spritePath = _spritePath;
		name = _name;
		image.loadFromFile(spritePath);
		sprite.setTexture(image);
		//choice = _choice;
	}
	bool mouseCollision(sf::Vector2<int> pos) {
		if (sprite.getGlobalBounds().contains(pos.x, pos.y)) {
			return true;

		}
		else
			return false;
	}
	Item* spawn(sf::Vector2<int> pos) {

		return new Item(pos, name, spritePath);
	};
};

#endif