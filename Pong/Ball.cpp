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

void Ball::update(float deltaTime, int winWidth, int winHeight, Paddle &paddleOne, Paddle &paddleTwo)
{
	float magnitude = std::sqrt(std::pow(m_direction.x, 2) + std::pow(m_direction.y, 2));
	m_direction = m_direction / magnitude;


	if (paddleOne.paddle.getGlobalBounds().intersects(ball.getGlobalBounds()) || paddleTwo.paddle.getGlobalBounds().intersects(ball.getGlobalBounds()))
	{
		m_direction.x = -m_direction.x;
	}


	if (ball.getPosition().y - ball.getRadius() <= 0 || ball.getPosition().y + ball.getRadius() >= winHeight)
	{
		m_direction.y = -m_direction.y;
	}

	if (ball.getPosition().x <= 0)
	{
		paddleTwo.score += 1;
		m_direction.x = -m_direction.x;
	}
	if (ball.getPosition().x + ball.getRadius() >= winWidth)
	{
		paddleOne.score += 1;
		m_direction.x = -m_direction.x;
	}

	m_move(deltaTime);
}


Ball::~Ball()
{
}

void Ball::m_move(float deltaTime)
{
	ball.move(m_direction * (deltaTime * m_speed));
}