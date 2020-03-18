#include "FillingMinigame.h"
#include <iostream>
#include <cmath>

FillingMiniGame::FillingMiniGame(sf::Vector2<int> pos, float _speed) {

	border = sf::RectangleShape(sf::Vector2f(100,200));
	cursor = sf::RectangleShape(sf::Vector2f(border.getGlobalBounds().width, 5));
	border.setFillColor(sf::Color(0, 0, 0));
	border.setOutlineThickness(2);
	border.setOutlineColor(sf::Color(250, 150, 100));

	cursor.setFillColor(sf::Color(255, 0, 0));

	border.setPosition(pos.x - 275, pos.y - 400);

	cursor.setPosition(border.getPosition().x, 
					   border.getPosition().y + border.getGlobalBounds().height - cursor.getGlobalBounds().height);
	activated = true;
	speed = _speed;
}

void FillingMiniGame::draw(sf::RenderWindow &window) {
	window.draw(border);
	window.draw(cursor);
}

void FillingMiniGame::pressed() {
	activated = false;
	
}

int FillingMiniGame::getAmountFilled() {
	//(cursor.getPosition().y < (border.getPosition().y + border.getGlobalBounds().height)
	float calc = cursor.getPosition().y - (border.getPosition().y + border.getGlobalBounds().height);
	calc = calc /  border.getGlobalBounds().height;
	std::cout << calc << std::endl;
	calc = calc * 100.0f;
	
	return abs(calc);
}

bool FillingMiniGame::update() {
	cursor.setPosition(cursor.getPosition().x, cursor.getPosition().y - log10(speed)) ;
	speed += 0.10f;
	//std::cout << log(speed) << std::endl;
	if (cursor.getPosition().y <= border.getPosition().y) {
		
		return true;
	}
	else if(activated == false) {
		
		return true;
		
	}
	else {
		
		return false;
	}
}