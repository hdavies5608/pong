#include "Ball.h"

#include <math.h>
#include <cmath> 
Ball::Ball(int xPos, int yPos, int radius, sf::Vector2f direction)
{
	ball.setFillColor(sf::Color::White);
	ball.setPosition(xPos, yPos);
	ball.setRadius(radius);
	ball.setOrigin(radius / 2, radius / 2);
	m_direction = direction;
}

void Ball::update(float deltaTime)
{
	m_direction.x = 1;
	m_direction.y = 1;
	float magnitude = std::sqrt(std::pow(m_direction.x, 2) + std::pow(m_direction.y, 2));
	m_direction = m_direction / magnitude;
	m_move(deltaTime);
}


Ball::~Ball()
{
}

void Ball::m_move(float deltaTime)
{
	ball.move(m_direction * (deltaTime * m_speed));
}
