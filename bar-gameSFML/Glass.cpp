#include "Glass.h"
#include <iostream>


Glass::Glass(sf::Vector2<int> pos, int _id) {
	sprite.setPosition(pos.x - sprite.getGlobalBounds().width / 2, pos.y - sprite.getGlobalBounds().height / 2);
	id = _id;
}

void Glass::update(sf::Vector2<int> pos) {

	sprite.setPosition(pos.x - sprite.getGlobalBounds().width / 2, pos.y - sprite.getGlobalBounds().height / 2);

}

sf::Vector2f Glass::getPos() {
	return sprite.getPosition();
	
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

	std::cout << "glass id: " << id << " " << "contents: ";
	for (auto elem : contains)
	{
		 std::cout << elem.first << " " << elem.second << " ";
	}
	std::cout << std::endl;
}

//GLASS OBJECT fUNCTIONS
OldFashioned::OldFashioned(sf::Vector2<int> pos, int _id) : Glass(pos, _id) {
	std::cout << "OldFashioned Created" << std::endl;
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