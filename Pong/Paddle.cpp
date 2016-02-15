#include "Paddle.h"

Paddle::Paddle(int xPos, int yPos, int width, int height, bool AIEnabled)
{
	paddle.setFillColor(sf::Color::White);
	paddle.setPosition(xPos, yPos);
	paddle.setSize(sf::Vector2f(width, height));
	paddle.setOrigin(width / 2, height / 2);
	m_AIEnabled = AIEnabled;
}

void Paddle::update(float deltaTime)
{
	if (!m_AIEnabled)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			m_move(-1, deltaTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			m_move(1, deltaTime);
		}
	}
	else
	{
		// TODO: AI
	}
}

void Paddle::m_move(int direction, float deltaTime)
{
	paddle.move(0, direction * deltaTime * m_speed);
}

Paddle::~Paddle()
{
}
