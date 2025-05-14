#pragma once
#include <iostream>
#include "Graphics.h"
#include <string>
#include <SFML/Graphics.hpp>
#include "TimeClock.h"
#include "Title.h"

const int STATUS_SPACE = 30;
const float STATUS_WIDTH = 500;

class GameStatus
{
public:
	GameStatus(int& life, int& score, int& level);
	~GameStatus() = default;
	void draw();
	void startGame() { m_gameStarted = true;};
	void setGameOver();
	void setGameWon();
private:
	void drawGameStatus();
	void setText();
	bool m_gameOver;
	bool m_gameStarted;

	Title m_title;
	sf::Sprite m_winOrLoseSprite;
	int& m_level;
	int& m_score;
	int& m_life;

	sf::Font m_font;
	sf::RectangleShape m_menuRectangle;
	sf::Sprite m_lifeSprite;

	sf::Text m_levelText;
	sf::Text m_lifeText;
	sf::Text m_scoreText;
	sf::Text m_timeText;
};
