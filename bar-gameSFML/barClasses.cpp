#include <iostream>
#include "barClasses.h"


Drawable::Drawable(sf::Vector2<int> pos) {
	sprite.setPosition(pos.x, pos.y);
}

void Drawable::draw(sf::RenderWindow &window) {

	window.draw(sprite);
}


Person::Person(sf::Vector2<int> pos, std::map<std::string, int> _order) : Drawable(pos) {
	image.loadFromFile("resources/sprites/guy1.png");
	sprite.setTexture(image);
	//TODO: change this to use rvalues and move
	order = _order;
	promptString = getOrder();
	
	if (!font.loadFromFile("C:/Users/mattr/Desktop/bar-gameSFML/bar-gameSFML/resources/fonts/GoudyOldStyleRegular.ttf"))
	{
		std::cout << "font error dickhead" << std::endl;
	}
	

	
	prompt.setFont(font); // font is a sf::Font

	
	prompt.setString(promptString);

	
	prompt.setCharacterSize(24); // in pixels, not points!

	
	prompt.setFillColor(sf::Color(100, 149, 237));
	prompt.setPosition(pos.x, pos.y - 50);
	
	
}
void Person::draw(sf::RenderWindow& window) {
	window.draw(sprite);
	window.draw(prompt);
}


bool Person::isColliding(int x, int y) {

	if (sprite.getGlobalBounds().contains(x, y)) {
		return true;
	}
	else {
		return false;
	}

}
bool Person::orderChecker(std::map<std::string, int> drink) {
	
	if (drink.empty()) {
		std::cout << "Nothing here dickhead" << std::endl;
		return false;
	}
	
	for(auto const& x : drink) {
		if (order.count(x.first) == 0) {
			std::cout << "wrong Order dickhead" << std::endl;
			return false;
		}

	}
	
	return true;
}

std::string Person::getOrder() {
	std::string returnString;
	for (auto const& x : order) {
		returnString.append(x.first);
		returnString.append(":");
		returnString.append(std::to_string(x.second));
		returnString.append(", ");
	}
	return returnString;
}
