#pragma once

#include <SFML/Graphics.hpp>

class Paddle
{
public:
	sf::RectangleShape paddle;
	Paddle(int xPos, int yPos, int width, int height);
	int score = 0;
	~Paddle();
};

