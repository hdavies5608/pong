#include "Paddle.h"

Paddle::Paddle(int xPos, int yPos, int width, int height)
{
	paddle.setFillColor(sf::Color::White);
	paddle.setPosition(xPos, yPos);
	paddle.setSize(sf::Vector2f(width, height));
	paddle.setOrigin(width / 2, height / 2);
	score = 0;
}

Paddle::~Paddle()
{
}
