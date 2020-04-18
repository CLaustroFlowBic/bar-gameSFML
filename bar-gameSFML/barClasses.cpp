#include <iostream>
#include "barClasses.h"


Drawable::Drawable(sf::Vector2<int> pos) {
	sprite.setPosition(pos.x, pos.y);
}

void Drawable::draw(sf::RenderWindow &window) {

	window.draw(sprite);
}
std::string genPersonPNG(int selection) {

	switch (selection) {
	case 0:
		return "guy1.png";
	case 1:
		
		return "guy2.png";
	case 2:
		
		return "guy3.png";
	case 3:
		return "guy4.png";
	}
	return "";
}

Person::Person(sf::Vector2<int> pos, std::map<std::string, int> _order) : Drawable(pos) {

	std::string personPNG = genPersonPNG(rand() % 4);

	image.loadFromFile("resources/sprites/" + personPNG);
	sprite.setTexture(image);
	//TODO: change this to use rvalues and movesdf
	order = _order;
	promptString = getOrder();
	
	if (!font.loadFromFile("C:/Users/mattr/Desktop/bar-gameSFML/bar-gameSFML/resources/fonts/VCR_OSD_MONO_1.001.ttf"))
	{
		std::cout << "font error dickhead" << std::endl;
	}

	textbox = sf::RectangleShape(sf::Vector2f(300, 100));
	textbox.setPosition(pos.x + 150, pos.y );
	textbox.setFillColor(sf::Color(0, 0, 0));
	textbox.setOutlineThickness(5);
	textbox.setOutlineColor(sf::Color(100, 0, 200));

	
	prompt.setFont(font); // font is a sf::Font
	
	prompt.setString("");
	
	prompt.setCharacterSize(28); // in pixels, not points!
	
	
	int textPosx = textbox.getPosition().x + textbox.getGlobalBounds().width / 2;
	int textPosy = textbox.getPosition().y + textbox.getGlobalBounds().height / 2;
	prompt.setFillColor(sf::Color(255, 255, 255));
	prompt.setPosition(textbox.getPosition().x, textbox.getPosition().y);
	
	
}
void Person::draw(sf::RenderWindow& window) {
	window.draw(sprite);
	window.draw(textbox);

	if (prompt.getString() != promptString) {
		if (textSpeed >= 100) {
			textPosition++;
			prompt.setString(promptString.substr(0, textPosition));
			textSpeed = 0;
		}

		textSpeed = textSpeed + 25;
	}

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
		returnString.append(": ");
		//dont add a , on the last item
		returnString.append(std::to_string(x.second));
		if (x != *order.rbegin()) {
			returnString.append("\n");
		}

		
	}
	return returnString;
}
