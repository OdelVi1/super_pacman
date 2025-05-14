#include "Level.h"

Level::Level():m_demonVector(), m_pacmanMoving(false),
m_board(), m_Position(BOARD_X_POSITION, BOARD_Y_POSITION), m_level(0), m_score(0), m_life(LIFE), 
m_cookies(0), m_bfsTree(), m_sound(), m_gameStatus(m_life, m_score, m_level)
{
	m_player = std::make_unique < Player >(m_life, m_score);
}

bool Level::loadLevel() // Return False if No more levels to load
{
	m_gameStatus.startGame();
	m_level++;
	m_demonVector.clear(); //for next level, we want the demons from the file
	//create the Board according the file
	bool boardResult = m_board.createBoard(m_level, 
		isCountDownLevel(), *m_player.get(), m_demonVector, m_cookies);

	if (!boardResult) 
	{
		if (m_level == 1) //the file not opened
		{
			std::cerr << "could not open file. no valid level found\n";
			exit(EXIT_FAILURE);
		}
		m_level--; // Will draw last level + 1 without decreasing here
		m_gameStatus.setGameWon(); // We won because we dont have more levels
		draw();
		winSound();
		std::this_thread::sleep_for(std::chrono::milliseconds(SHOW_GAME_STATUS_TIME));
		return false;
	}
	TimeClock::getInstance().reset(); //new level = new clock
	if (isCountDownLevel())
	{
		TimeClock::getInstance().addCountDownTime(LEVEL_TIME);
	}
	return true;
}

bool Level::run()
{
	sf::Event e;
	gameReset();
	while (Graphics::getInstance().getWindow().isOpen() && m_cookies > 0)
	{
		if (isGameOver())
		{
			drawGameOver();
			return false;
		}

		if (Graphics::getInstance().getWindow().pollEvent(e))
		{
			switch (e.type) {
			case sf::Event::Closed:
			{
				Graphics::getInstance().getWindow().close();
				return false;
			}
			break;
			case sf::Event::KeyPressed:
			{
				m_player->setDirection(e.key.code);
				m_pacmanMoving = true;
			}
			break;
			case sf::Event::KeyReleased:
			{
				m_pacmanMoving = false;
				break;
			}
			}
		}
		movePlayer();
		moveDemons();
		handleStaticCollisions();
		handlePlayerDemonCollision();
		draw();
	}
	return true; // if life > 0, level won
}

bool Level::isCountDownLevel()
{
	return (m_level % 2 == 0);
}

void Level::gameReset()
{
	m_player->setBlink();
	for (auto& d : m_demonVector)
	{
		d->setBlink();
	}
	TimeClock::getInstance().getClock().restart();
}

bool Level::isGameOver()
{
	if (m_life == 0)
		return true;

	if (isCountDownLevel() &&
		LEVEL_TIME - TimeClock::getInstance().getClock().getElapsedTime().asSeconds() <= 0)
		return true;

	return false;
}

void Level::drawGameOver()
{
	m_gameStatus.setGameOver();
	draw();
	m_sound.setBuffer(Graphics::getInstance().getSoundBuffer(GameSounds::GAME_OVER));
	m_sound.play();
	std::this_thread::sleep_for(std::chrono::milliseconds(SHOW_GAME_STATUS_TIME));
}

void Level::movePlayer()
{
	m_player->resetPacman();
	if (m_pacmanMoving)
	{
		m_player->move(m_board.getBoardSize());
	}

	//Clear the tree if Super Pacman becuase the smart demon not chasing after him
	if (m_player->isSuperPacman())
	{
		m_bfsTree.clear();
	}
	else if (m_bfsTree.empty() || m_pacmanMoving) //Update the tree only if empty or the player has moved
	{
		setBfsTree(m_player->getPositionAsMatrixIndex());
	}
}

void Level::moveDemons()
{
	if (m_player->getRemainigFrozenDemonsSeconds() > 0) //Do not move the demons if they are frozen
	{
		for (int i = 0; i < m_demonVector.size(); i++)
		{
			m_demonVector[i]->freezeDemon();
		}
	}
	else
	{
		for (int i = 0; i < m_demonVector.size(); i++)
		{
			m_demonVector[i]->setDirection(m_bfsTree);
			m_demonVector[i]->move(m_board.getBoardSize());
		}
	}
}

// this function returns the bfs tree from the pacman position
void Level::setBfsTree(sf::Vector2i start)
{
	m_bfsTree.clear();
	m_bfsTree.assign(m_board.getBoardIndexSize().y, std::vector<sf::Vector3i>(m_board.getBoardIndexSize().x,
		sf::Vector3i(INT_MAX, -1, -1)));

	m_bfsTree[start.y][start.x].x = 0;

	//set a queue to hold coordinate
	std::queue<sf::Vector2i> queue;

	//put cordinate in the queue
	queue.push(start);

	//chek if the queue is empty
	while (!queue.empty())
	{
		//take a coordinate from the queue
		sf::Vector2i current = queue.front();
		queue.pop();
		setNeighborPaths(start, current, queue);
	}
}

void Level::setNeighborPaths(sf::Vector2i start, sf::Vector2i current, std::queue<sf::Vector2i>& queue)
{
	std::vector<sf::Vector2i> shifts = { { 1,0 },{ -1,0 },{ 0,1 },{ 0,-1 } };

	//check all the neighbors and set their paths 
	for (unsigned int i = 0; i < shifts.size(); i++)
	{
		//set next and check it
		sf::Vector2i next = current + shifts[i];
		if (CellOutOfBoard((sf::Vector2f)next) ||
			dynamic_cast<Wall*> (&m_board.getBoardItem(next.y, next.x)) ||
			dynamic_cast<Door*> (&m_board.getBoardItem(next.y, next.x)))
		{
			continue; //bad path
		}

		//if its a good neighbor(new neighbor = infinite and diffrent from pacman), add it to the tree
		if ((next.y != start.y || next.x != start.x) &&
			m_bfsTree[next.y][next.x].x == INT_MAX)
		{
			queue.push(next);
			m_bfsTree[next.y][next.x].x = m_bfsTree[current.y][current.x].x + 1;
			m_bfsTree[next.y][next.x].y = shifts[i].x;
			m_bfsTree[next.y][next.x].z = shifts[i].y;
		}
	}
}

// this functions checks if a certain cell is out of the board
bool Level::CellOutOfBoard(sf::Vector2f place)
{
	return (place.x < 0 || place.y < 0 || place.x >= m_board.getBoardIndexSize().x ||
		place.y >= m_board.getBoardIndexSize().y);
}

void Level::draw()
{
	Graphics::getInstance().getWindow().clear();
	sf::Vector2f size = m_board.getBoardSize();
	sf::View boardView = sf::View(sf::Vector2f(size.x / 2, size.y / 3), sf::Vector2f(1000, 1000));
	sf::Vector2f factor = sf::Vector2f(size.x / BOARD_VIEW_SIZE, size.y / BOARD_VIEW_SIZE);
	boardView.zoom(factor.x >= factor.y ? factor.x : factor.y);
	Graphics::getInstance().getWindow().setView(boardView);
	m_board.draw();
	for (int i = 0; i < m_demonVector.size(); i++)
	{
		drawMovingObject(m_demonVector[i].get());
	}
	drawMovingObject(m_player.get());
	Graphics::getInstance().getWindow().setView(Graphics::getInstance().getWindow().getDefaultView());
	m_gameStatus.draw();
	Graphics::getInstance().getWindow().display();
}

void Level::drawMovingObject(Moving* object)
{
	int remainingTime = object->getRemainingBlinkTime();
	if (remainingTime <= 0 || remainingTime % 1000 > 500)
	{
		object->draw();
	}
}

void Level::handleStaticCollisions() {
	for (int i = 0; i < m_board.getBoardIndexSize().y; i++)
	{
		for (int j = 0; j < m_board.getBoardIndexSize().x; j++)
		{
			if (&m_board.getBoardItem(i, j) == nullptr)
			{
				continue;
			}
			if (m_player->checkCollision(m_board.getBoardItem(i, j)))
				m_board.getBoardItem(i, j).handleCollision(*m_player.get());
			for (auto& d : m_demonVector)
			{
				if (d->checkCollision(m_board.getBoardItem(i, j)))
				{
					m_board.getBoardItem(i, j).handleCollision(*d.get());
				}
			}
		}
	}
}

void Level::handlePlayerDemonCollision()
{
	for (auto& d : m_demonVector)
	{
		if (m_player->checkCollision(*(d.get())))
		{
			m_player->handleCollision(*(d.get()));
			if (!m_player->isSuperPacman())
			{
				m_player->resetPosition();
				m_player->setBlink();
				m_bfsTree.clear();
				setDemonsCollision();
				break;
			}
		}
	}
}

void Level::setDemonsCollision()
{
	for (auto& d : m_demonVector)
	{
		d->resetPosition();
		d->setBlink();
	}
}

void Level::winSound()
{
	m_sound.setBuffer(Graphics::getInstance().getSoundBuffer(GameSounds::WIN));
	m_sound.play();
}
