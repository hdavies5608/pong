#include <SFML/Graphics.hpp>
#include <vector>
#include <assert.h> 

#include "Paddle.h"
#include "Ball.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pong!");

	Paddle playerOne(50, WINDOW_HEIGHT / 2, 20, 100, false);
	Paddle playerTwo(WINDOW_WIDTH - 50, WINDOW_HEIGHT / 2, 20, 100, true);
	Ball ball(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 15, sf::Vector2f(1, 0));

	sf::Font font;
	assert (font.loadFromFile("RobotoMono.ttf"));

	std::vector<sf::Text> scores;
	for (int i = 0; i < 2; i++)
	{
		scores.push_back(sf::Text());
		scores[i].setFont(font);
		scores[i].setCharacterSize(64);
		scores[i].setColor(sf::Color::White);
		if (i == 0)
			scores[i].setPosition((WINDOW_WIDTH / 2) - (WINDOW_WIDTH / 4), 100);
		else
			scores[i].setPosition((WINDOW_WIDTH / 2) + (WINDOW_WIDTH / 4), 100);
	}

	sf::Clock deltaTimeClock;
	float deltaTime = 0;
	while (window.isOpen())
	{
		//Update scores
		scores[0].setString(std::to_string(playerOne.score));
		scores[1].setString(std::to_string(playerTwo.score));

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		playerOne.update(deltaTime);
		playerTwo.update(deltaTime);
		ball.update(deltaTime);

		window.clear();
		window.draw(scores[0]);
		window.draw(scores[1]);
		window.draw(playerOne.paddle);
		window.draw(playerTwo.paddle);
		window.draw(ball.ball);
		window.display();

		deltaTime = deltaTimeClock.restart().asSeconds();
	}

	return 0;
}