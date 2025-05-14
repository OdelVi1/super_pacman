#pragma once
#include "Board.h"
#include "Player.h"
#include "Demon.h"
#include "GameStatus.h"
#include <fstream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <chrono>
#include <thread>

const int LIFE = 3;
const int BOARD_VIEW_SIZE = 600;
const float BOARD_X_POSITION = 50;
const float BOARD_Y_POSITION = 50;
const float LEVEL_TIME = 60;
const int SHOW_GAME_STATUS_TIME = 3000;

class Level
{
public:
	Level();
	~Level() = default;
	bool loadLevel();
	bool run(); //the main loop
private:
	void handleStaticCollisions();
	void handlePlayerDemonCollision();
	void draw();
	bool isCountDownLevel();
	void drawGameOver();
	void setBfsTree(sf::Vector2i start);
	void setNeighborPaths(sf::Vector2i start, sf::Vector2i current, std::queue<sf::Vector2i>& queue);
	bool CellOutOfBoard(sf::Vector2f place);
	void drawMovingObject(Moving* object);
	void gameReset();
	bool isGameOver();
	void winSound();
	void movePlayer();
	void moveDemons();
	void setDemonsCollision();

	std::vector<std::unique_ptr<Demon>> m_demonVector;
	std::unique_ptr<Player> m_player; 
	Board m_board;
	bool m_pacmanMoving;
	sf::Vector2f m_Position;
	int m_cookies;
	std::vector<std::vector<sf::Vector3i>> m_bfsTree;
	sf::Sound m_sound;
	int m_score;
	int m_life;
	int m_level;
	GameStatus m_gameStatus;
};
