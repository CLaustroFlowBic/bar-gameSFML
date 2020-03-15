#include "Glass.h"
#include <iostream>


Glass::Glass(sf::Vector2<int> pos, int _id) {
	sprite.setPosition(pos.x - sprite.getGlobalBounds().width / 2, pos.y - sprite.getGlobalBounds().height / 2);
	id = _id;
}

void Glass::update(sf::Vector2<int> pos) {

	sprite.setPosition(pos.x - sprite.getGlobalBounds().width / 2, pos.y - sprite.getGlobalBounds().height / 2);

}

bool Glass::mouseCollision(sf::Vector2<int> pos) {
	if (sprite.getGlobalBounds().contains(pos.x, pos.y)) {
		return true;

	}
	else
		return false;
}
void Glass::add(int amount, Item* item) {
	currentCapacity += amount;
	
	std::map<std::string, int>::iterator it = contains.find(item->getName());
	if (it == contains.end()) {
		contains.insert(std::make_pair(item->getName(), amount));
	}
	else {
		it->second += amount;
	}
	for (auto elem : contains)
	{
		std::cout << id << " " << elem.first << " " << elem.second << "\n";
	}
}

//GLASS OBJECT fUNCTIONS
OldFashioned::OldFashioned(sf::Vector2<int> pos, int _id) : Glass(pos, _id) {
	std::cout << "hello:" << std::endl;
	image.loadFromFile("resources/sprites/glass1.jpg");
	sprite.setTexture(image);
	sprite.setPosition(pos.x - sprite.getGlobalBounds().width / 2, pos.y - sprite.getGlobalBounds().height / 2);
}

//GLASSSPAWNER FUNCTIONS

GlassSpawner::GlassSpawner(sf::Vector2<int> pos, std::string spritePath, int _choice) : Drawable(pos) {
	image.loadFromFile(spritePath);
	sprite.setTexture(image);
	choice = _choice;

}

bool GlassSpawner::mouseCollision(sf::Vector2<int> pos) {
	if (sprite.getGlobalBounds().contains(pos.x, pos.y)) {
		return true;

	}
	else
		return false;
}

Glass* GlassSpawner::g_prototypes[] = { new OldFashioned };