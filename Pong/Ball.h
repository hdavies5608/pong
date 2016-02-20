#pragma once

#include "Paddle.h"

#include <SFML/Graphics.hpp>

class Ball
{
public:
	sf::CircleShape ball;
	Ball(float xPos, float yPos, float radius, sf::Vector2f direction);
	void update(float deltaTime, int winWidth, int winHeight, Paddle &paddleOne, Paddle &paddleTwo);
	void setPosition(sf::Vector2f position) { ball.setPosition(position); };
	~Ball();
private:
	sf::Vector2f m_direction;
	int m_speed = 500;
	void m_move(float deltaTime);

	bool m_hasCollidedPaddle = false;
	bool m_hasCollidedWall = false;
};

