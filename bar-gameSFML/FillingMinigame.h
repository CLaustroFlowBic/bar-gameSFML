#include "barClasses.h"


class FillingMiniGame  {

	sf::RectangleShape border;
	sf::RectangleShape cursor;

	sf::RectangleShape levels[4];

	

	bool activated;
	float speed;

	int position;
public:
	FillingMiniGame(sf::Vector2<int> pos, float _speed);
	void draw(sf::RenderWindow &window);
	int getAmountFilled();
	bool update(float dt);
	void pressed();
};