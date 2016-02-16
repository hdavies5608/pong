#include "Paddle.h"

Paddle::Paddle(int xPos, int yPos, int width, int height, bool AIEnabled, sf::Keyboard::Key upKey, sf::Keyboard::Key downKey)
{
	paddle.setFillColor(sf::Color::White);
	paddle.setPosition(xPos, yPos);
	paddle.setSize(sf::Vector2f(width, height));
	paddle.setOrigin(width / 2, height / 2);

	m_AIEnabled = AIEnabled;
	m_upKey     = upKey;
	m_downKey   = downKey;
}

void Paddle::update(float deltaTime, int winHeight)
{
	if (!m_AIEnabled)
	{
		if (sf::Keyboard::isKeyPressed(m_upKey) && paddle.getPosition().y >= (10 + paddle.getGlobalBounds().height / 2) )
		{
			m_move(-1, deltaTime);
		}
		if (sf::Keyboard::isKeyPressed(m_downKey) && paddle.getPosition().y <= ((winHeight - 10) - paddle.getGlobalBounds().height / 2))
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
