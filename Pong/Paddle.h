#pragma once

#include <SFML/Graphics.hpp>

class Paddle
{
public:
	sf::RectangleShape paddle;
	Paddle(int xPos, int yPos, int width, int height, bool AIEnabled, sf::Keyboard::Key upKey = sf::Keyboard::W, sf::Keyboard::Key downKey = sf::Keyboard::S);
	void update(float deltaTime, int winHeight);
	int score = 0;
	~Paddle();
private:
	void m_move(int direction, float deltaTime);
	int m_speed = 500;
	bool m_AIEnabled = false;
	sf::Keyboard::Key m_upKey;
	sf::Keyboard::Key m_downKey;
};

