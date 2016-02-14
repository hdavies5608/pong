#include "Ball.h"



Ball::Ball(int xPos, int yPos, int radius, sf::Vector2f direction)
{
	ball.setFillColor(sf::Color::White);
	ball.setPosition(xPos, yPos);
	ball.setRadius(radius);
	ball.setOrigin(radius / 2, radius / 2);
	m_direction = direction;
}


Ball::~Ball()
{
}
