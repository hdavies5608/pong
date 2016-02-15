#pragma once

#include <SFML/Graphics.hpp>

class Paddle
{
public:
	sf::RectangleShape paddle;
	Paddle(int xPos, int yPos, int width, int height, bool AIEnabled);
	void update(float deltaTime);
	int score = 0;
	~Paddle();
private:
	void m_move(int direction, float deltaTime);
	int m_speed = 500;
	bool m_AIEnabled = false;
};

