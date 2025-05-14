#include "Board.h"

Board::Board() :m_boardRectangle(), m_lock()
{
	srand((unsigned)time(NULL));
	m_boardRectangle.setOutlineThickness(2);
	m_boardRectangle.setOutlineColor(sf::Color().Green);
	m_boardRectangle.setFillColor(sf::Color().Transparent);
	m_boardRectangle.setPosition(sf::Vector2f(0, 0));
}

// this function returns the board size
sf::Vector2f Board::getBoardSize()
{
	return m_boardRectangle.getSize();
}

// this function draw the board
void Board::draw()
{
	Graphics::getInstance().getWindow().draw(m_boardRectangle); //draw the board border
	for (int i = 0; i < m_boardStaticItems.size(); i++) 
	{
		for (int j = 0; j < m_boardStaticItems[i].size(); j++)
		{
			if (m_boardStaticItems[i][j] == nullptr)
			{
				continue;
			}

			if (m_boardStaticItems[i][j].get()->isRemoved())
			{
				m_boardStaticItems[i][j].release();
			}
			else
			{
				m_boardStaticItems[i][j]->draw();
			}
		}
	}
}

// this function opens the .txt file to read
bool Board::openFile(ifstream& input, int levelNumber)
{
	string file = "level" + std::to_string(levelNumber) + ".txt"; //pattern to read the new level genericly
	input.open(file);
	if (!input.is_open())
	{
		return false;
	}
	return true;
}

// this function reads the .txt file and sets the board accordingly
bool Board::createBoard(int levelNumber, bool isCountDownLevel, Player& player,
	vector<std::unique_ptr<Demon>>& demons, int& cookies)
{
	int doorIndex = -1, keyIndex = -1;
	ifstream input;
	if (!openFile(input, levelNumber))
	{
		return false;
	}

	int rows, cols;
	std::string line;

	input >> rows >> cols;
	input.get(); //skip to next line
	setBoardSize(rows, cols); //the Board size determined by the number of rows and columns
	for (int row = 0; row < rows; row++)
	{
		std::getline(input, line, '\n');		
		for (int col = 0; col < cols; col++)
		{
			switch (line[col])
			{
			case WallSymbol:
				m_boardStaticItems[row][col] = std::make_unique < Wall >(getPositionByIndex(row, col));
				break;
			case CookieSymbol:
				cookies++;
				m_boardStaticItems[row][col] = std::make_unique < Cookie >(getPositionByIndex(row, col), cookies);
				break;
			case KeySymbol:
				createKey(row, col, doorIndex, keyIndex);
				break;
			case DoorSymbol:
				createDoor(row, col, doorIndex, keyIndex);
				break;
			case PresentSymbol:
				setRandomPresent(row, col, isCountDownLevel);
				break;
			case DemonSymbol:
				setDemon(demons, row, col);
				break;
			case PacmanSymbol:
				player.setStartingPosition(getPositionByIndex(row, col));
				break;
			default:
				m_boardStaticItems[row][col] = nullptr;
				break;
			}
		}
	}
	return true;
}

void Board::createKey(int row, int col, int& doorIndex, int& keyIndex)
{
	keyIndex++; //the current number of keys 
	if (keyIndex > doorIndex) //create a new lock if there are more keys then doors
	{
		m_lock.push_back(std::make_unique<bool>(true));
	}
	m_boardStaticItems[row][col] = std::make_unique < Key >(getPositionByIndex(row, col), m_lock[keyIndex].get());
}

void Board::createDoor(int row, int col, int& doorIndex, int& keyIndex)
{
	doorIndex++; //the current number of doors 
	if (doorIndex > keyIndex) //create a new lock if there are more doors then keys
	{
		m_lock.push_back(std::make_unique<bool>(true));
	}
	m_boardStaticItems[row][col] = std::make_unique < Door >(getPositionByIndex(row, col), m_lock[doorIndex].get());
}

//get a random type of gifts
void Board::setRandomPresent(const int row, const int col, bool isCountDownLevel)
{
	sf::Vector2f position = getPositionByIndex(row, col);
	while (true)
	{
		switch (rand() % RANDOM_PRESENT)
		{
		case 0:
			m_boardStaticItems[row][col] = std::make_unique < AddLife >(position);
			break;
		case 1:
			if (!isCountDownLevel)
			{
				continue;
			}
			m_boardStaticItems[row][col] = std::make_unique < ExtendTime >(position);
			break;
		case 2:
			m_boardStaticItems[row][col] = std::make_unique < FreezeDemons >(position);
			break;
		case 3:
			m_boardStaticItems[row][col] = std::make_unique < Present >(position);
			break;
		}
		break;
	}
}

// this function sets the demon's type (random or smart) and position  
void Board::setDemon(vector<std::unique_ptr<Demon>>& demons, const int row, const int col)
{
	sf::Vector2f position = getPositionByIndex(row, col);
	if (demons.size() % FREQUENCY_DEMON == 0)
	{
		demons.push_back(std::make_unique < SmartDemon >(position));
	}
	else
	{
		demons.push_back(std::make_unique < RandomDemon >(position));
	}
}

Static& Board::getBoardItem(int row, int col)
{
	return *(m_boardStaticItems[row][col].get());
}

// this function sets the board to a new size
void Board::setBoardSize(int rows, int cols)
{
	m_boardStaticItems.clear();
	m_boardStaticItems.resize(rows);
	for (int i = 0; i < rows; i++)
	{
		m_boardStaticItems[i].resize(cols);
	}
	m_boardRectangle.setSize(sf::Vector2f(cols * P_SIZE, rows * P_SIZE));
}