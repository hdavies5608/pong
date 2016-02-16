#pragma once

#include "Paddle.h"

#include <SFML/Graphics.hpp>

class Ball
{
public:
	sf::CircleShape ball;
	Ball(int xPos, int yPos, int radius, sf::Vector2f direction);
	void update(float deltaTime, int winWidth, int winHeight, Paddle &paddleOne, Paddle &paddleTwo);
	~Ball();
private:
	sf::Vector2f m_direction;
	int m_speed = 500;
	void m_move(float deltaTime);
};

