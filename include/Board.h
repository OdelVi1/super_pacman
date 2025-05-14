#pragma once
#include "Player.h"
#include "Demon.h"
#include "Cookie.h"
#include "Wall.h"
#include "Cookie.h"
#include "Present.h"
#include "Door.h"
#include "Key.h"
#include "AddLife.h"
#include "FreezeDemons.h"
#include "ExtendTime.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include "SmartDemon.h"
#include "RandomDemon.h"
#include "Graphics.h"
#include "Utils.h"
#include <SFML/Audio.hpp>

using std::ifstream;
using std::string;
using std::vector;
const int RANDOM_PRESENT = 4;
const int FREQUENCY_DEMON = 2;

class Board
{
public:
	Board();
	sf::Vector2f getBoardSize();
	bool createBoard(int levelNumber, bool isCountDownLevel, Player& player, vector<std::unique_ptr<Demon>>& demons, int &cookies);
	void draw();
	Static& getBoardItem(int row, int col);
	sf::Vector2i getBoardIndexSize() { return sf::Vector2i(int(m_boardStaticItems[0].size()), int(m_boardStaticItems.size())); };

private:
	bool openFile(ifstream& input, int levelNumber);
	void setBoardSize(int rows, int cols);
	void setRandomPresent(const int row, const int col, bool isCountDownLevel);
	void setDemon(vector<std::unique_ptr<Demon>>& demons, const int row, const int col);
	void createKey(int row, int col, int& doorIndex, int& keyIndex);
	void createDoor(int row, int col, int& doorIndex, int& keyIndex);

	sf::Vector2f getPositionByIndex(int row, int col) {return sf::Vector2f(col * P_SIZE + m_boardRectangle.getPosition().x, 
		row * P_SIZE + m_boardRectangle.getPosition().y); };

	vector <vector<std::unique_ptr<Static>>> m_boardStaticItems;
	std::ifstream m_file;
	sf::RectangleShape m_boardRectangle;
	vector <std::unique_ptr<bool>> m_lock; //the pointers to give to key door pairs
};

