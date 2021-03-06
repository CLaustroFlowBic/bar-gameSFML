#pragma once
#ifndef GLASS_H
#define GLASS_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <map>
#include "barClasses.h"
#include "Item.h"

int const numberOfGlasses = 1;

class Glass : public Drawable{
	int maxCapacity;
	int currentCapacity;
	std::map<std::string, int> contains;

public:
	Glass() {};
	Glass(sf::Vector2<int> pos);
	int getMaxCapacity() { return maxCapacity; }
	int getCurrentCapacity() { return currentCapacity; }
	bool mouseCollision(sf::Vector2<int> pos);
	void add(int amount, Item* item);
	void update(sf::Vector2<int> pos);
	virtual Glass* clone(sf::Vector2<int> pos) = 0;



};


class OldFashioned :public Glass{
public:
	OldFashioned() {};
	OldFashioned(sf::Vector2<int> pos);
	Glass* clone(sf::Vector2<int> pos) { return new OldFashioned(pos); }
};



class GlassSpawner : public Drawable {
private:
	static Glass* g_prototypes[numberOfGlasses];
	int choice;

public:
	GlassSpawner(sf::Vector2<int> pos, std::string spritePath, int _choice);
	bool mouseCollision(sf::Vector2<int> pos);
	Glass* spawn(sf::Vector2<int> pos) {
		return g_prototypes[choice]->clone(pos);
	};
};

#endif