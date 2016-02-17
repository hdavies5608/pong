#pragma once

#include <SFML/Graphics.hpp>

class Paddle
{
public:
	sf::RectangleShape paddle;
	Paddle(float xPos, float yPos, float width, float height, bool AIEnabled, sf::Keyboard::Key upKey = sf::Keyboard::W, sf::Keyboard::Key downKey = sf::Keyboard::S);
	void update(float deltaTime, int winHeight, float ballYPos = 0);
	int score = 0;
	~Paddle();
private:
	void m_move(int direction, float deltaTime);
	int m_speed = 500;
	bool m_AIEnabled = false;
	sf::Keyboard::Key m_upKey;
	sf::Keyboard::Key m_downKey;
};

