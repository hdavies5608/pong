#include <SFML/Graphics.hpp>
#include <vector>
#include <assert.h> 
#include <random>
#include <chrono>
#include <iostream>
#include "Paddle.h"
#include "Ball.h"

#define WINDOW_WIDTH 1029
#define WINDOW_HEIGHT 720

enum class GameState {
	MENU,
	PLAY,
	PAUSE
};

int main()
{
	GameState gameState = GameState::MENU;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pong!");
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);

	typedef std::chrono::high_resolution_clock seedClock;
	seedClock::time_point begin = seedClock::now();
	std::mt19937_64 generator;
	seedClock::duration d = seedClock::now() - begin;
	generator.seed(d.count());
	std::uniform_int_distribution<int> dist(-1, 1);

	int x = dist(generator);
	if (x == 0) { x = 1; }
	int y = dist(generator);
	if (y == 0) { y = 1; }
	Paddle playerOne(50, WINDOW_HEIGHT / 2, 20, 100, false);
	Paddle playerTwo(WINDOW_WIDTH - 50, WINDOW_HEIGHT / 2, 20, 100, true);
	Ball ball((float)(WINDOW_WIDTH / 2.f), ((float)WINDOW_HEIGHT / 2.f), 15.f, sf::Vector2f(x, y));

	sf::Font font;
	bool loadedFont = font.loadFromFile("RobotoMono.ttf");
	assert(loadedFont);

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
	std::string pauseItems[] = { "Paused", "Resume", "Main Menu" };
	std::vector<sf::Text> pauseText;
	for (auto i = 0; i < (sizeof(pauseItems) / sizeof(*pauseItems)); i++)
	{
		pauseText.push_back(sf::Text());
		pauseText.back().setFont(font);
		pauseText.back().setCharacterSize(64);
		pauseText.back().setColor(sf::Color::White);
		pauseText.back().setString(pauseItems[i]);

		sf::FloatRect textRect = pauseText.back().getLocalBounds();

		pauseText.back().setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		pauseText.back().setPosition(sf::Vector2f((WINDOW_WIDTH - 10) - textRect.width / 2, 10 + textRect.height / 2.f + (i * 100)));
	}

	std::string menuItems[] = { "One Player", "Two Player", "Exit" };
	std::vector<sf::Text> menuText;
	for (auto i = 0; i < (sizeof(menuItems) / sizeof(*menuItems)); i++)
	{
		menuText.push_back(sf::Text());
		menuText.back().setFont(font);
		menuText.back().setCharacterSize(64);
		menuText.back().setColor(sf::Color::White);
		menuText.back().setString(menuItems[i]);
		menuText.back().setPosition(0.f, i * 100.f);
	}
	sf::Clock deltaTimeClock;
	float deltaTime = 0;
	bool clicked = false;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
				clicked = true;
			else
				clicked = false;
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape && gameState == GameState::PLAY)
				{
					gameState = GameState::PAUSE;
				}
				else if (event.key.code == sf::Keyboard::Escape && gameState == GameState::PAUSE)
				{
					gameState = GameState::PLAY;
				}

			}
		}
		switch (gameState)
		{
		case GameState::MENU:
			playerOne.setPosition(sf::Vector2f(50, WINDOW_HEIGHT / 2));
			playerTwo.setPosition(sf::Vector2f(WINDOW_WIDTH - 50, WINDOW_HEIGHT / 2));
			ball.setPosition(sf::Vector2f((float)(WINDOW_WIDTH / 2.f), ((float)WINDOW_HEIGHT / 2.f)));
			for (unsigned short i = 0; i < menuText.size(); i++)
			{
				if (menuText[i].getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window)))
				{
					menuText[i].setColor(sf::Color::Red);
					if (clicked)
					{
						switch (i)
						{
						case 0:
							gameState = GameState::PLAY;
							break;
						case 1:
							playerTwo.setAIEnabled(false);
							playerTwo.setControls(sf::Keyboard::Up, sf::Keyboard::Down);
							gameState = GameState::PLAY;
							break;
						case 2:
							window.close();
							break;
						default:
							break;
						}
					}
				}
				else
				{
					menuText[i].setColor(sf::Color::White);
				}
			}

			window.clear();
			for (unsigned short i = 0; i < menuText.size(); i++)
			{
				window.draw(menuText[i]);
			}
			window.display();
			break;
		case GameState::PLAY:
			//Update scores
			scores[0].setString(std::to_string(playerOne.score));
			scores[1].setString(std::to_string(playerTwo.score));

			playerOne.update(deltaTime, WINDOW_HEIGHT);
			playerTwo.update(deltaTime, WINDOW_HEIGHT, ball.ball.getPosition().y);
			ball.update(deltaTime, WINDOW_WIDTH, WINDOW_HEIGHT, playerOne, playerTwo);

			window.clear();
			window.draw(scores[0]);
			window.draw(scores[1]);
			window.draw(playerOne.paddle);
			window.draw(playerTwo.paddle);
			window.draw(ball.ball);
			window.display();
			break;
		case GameState::PAUSE:
			for (unsigned short i = 1; i < pauseText.size(); i++)
			{
				if (pauseText[i].getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(window)))
				{
					pauseText[i].setColor(sf::Color::Red);
					if (clicked)
					{
						switch (i)
						{
						case 1:
							gameState = GameState::PLAY;
							break;
						case 2:
							gameState = GameState::MENU;
							break;
						default:
							break;
						}
					}
				}
				else
				{
					pauseText[i].setColor(sf::Color::White);
				}
			}

			window.clear();
			for (unsigned short i = 0; i < pauseText.size(); i++)
			{
				window.draw(pauseText[i]);
			}
			window.display();
			break;
		default:
			break;
		}


		deltaTime = deltaTimeClock.restart().asSeconds();
	}

	return 0;
}