#pragma once

#include <SFML/Graphics.hpp>

class Ball
{
public:
	sf::CircleShape ball;
	Ball(int xPos, int yPos, int radius, sf::Vector2f direction);
	~Ball();
private:
	sf::Vector2f m_direction;
};

