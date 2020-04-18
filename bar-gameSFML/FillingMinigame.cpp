#include "FillingMinigame.h"
#include <iostream>
#include <cmath>


sf::RectangleShape makeLine(sf::RectangleShape border, int height) {

	sf::RectangleShape level;

	level = sf::RectangleShape(sf::Vector2f(border.getGlobalBounds().width - 10, 5));
	
	level.setFillColor(sf::Color(50, 0, 255));

	level.setPosition(border.getPosition().x, height);
	
	return level;

}


FillingMiniGame::FillingMiniGame(sf::Vector2<int> pos, float _speed) {

	border = sf::RectangleShape(sf::Vector2f(100,260));
	cursor = sf::RectangleShape(sf::Vector2f(border.getGlobalBounds().width, 5));
	border.setFillColor(sf::Color(0, 0, 0));
	border.setOutlineThickness(5);
	border.setOutlineColor(sf::Color(250, 150, 100));

	cursor.setFillColor(sf::Color(255, 0, 0));

	border.setPosition(pos.x - 275, pos.y - 400);
	position = border.getPosition().y + border.getGlobalBounds().height - cursor.getGlobalBounds().height;
	cursor.setPosition(border.getPosition().x, position);


	int spacing = 55;
	int height = position - spacing;
	for (int i = 0; i < 4; ++i) {
		
		levels[i] = makeLine(border, height);
		height -= spacing;
		
	}
	
	activated = true;
	speed = _speed;
}

void FillingMiniGame::draw(sf::RenderWindow &window) {
	window.draw(border);
	window.draw(cursor);

	for (auto x : levels) {
		window.draw(x);
	}

	window.draw(levels[0]);
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

bool FillingMiniGame::update(float dt) {
	position = position - log2(speed * dt);
	std::cout << "Position" << " " <<  log2(speed * dt) << std::endl;
	speed += 10;
	//std::cout << "speed = " << speed << std::endl;
	//std::cout << "dt = " << dt << std::endl;
	//
	//std::cout << "log2: " <<  log10(speed * dt) << std::endl;
	cursor.setPosition(cursor.getPosition().x, position ) ;
	//- log10(speed)
	//speed += 0.10f;
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