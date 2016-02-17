#include "Ball.h"

#include <math.h>
#include <cmath> 
Ball::Ball(float xPos, float yPos, float radius, sf::Vector2f direction)
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


	if (paddleOne.paddle.getGlobalBounds().intersects(ball.getGlobalBounds()) || paddleTwo.paddle.getGlobalBounds().intersects(ball.getGlobalBounds()) && !m_hasCollidedPaddle)
	{
		m_direction.x = -m_direction.x;
		m_hasCollidedPaddle = true;
	}
	else 
	{
		m_hasCollidedPaddle = false;
	}


	if (ball.getPosition().y - ball.getRadius() <= 0 || ball.getPosition().y + ball.getRadius() >= winHeight && !m_hasCollidedWall)
	{
		m_direction.y = -m_direction.y;
		m_hasCollidedWall = true;
	}
	else
	{
		m_hasCollidedWall = false;
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