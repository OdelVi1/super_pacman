#include "Menu.h"

Menu::Menu() : m_title(), m_rectangleShape()
{
	m_rectangleShape.setFillColor(sf::Color().Black);
	m_rectangleShape.setPosition(sf::Vector2f(MENU_X_POSITION * 2, MENU_Y_POSITION + BUTTON_DISTANCE));

	//create Buttons
	m_newGameButton = new NewGameButton(MENU_Y_POSITION);
	m_helpButton = new HelpButton(MENU_Y_POSITION + (BUTTON_HEIGHT + BUTTON_DISTANCE));
	m_exitButton = new ExitButton(MENU_Y_POSITION + (BUTTON_HEIGHT + BUTTON_DISTANCE) * 2);
}

void Menu::domenu()
{
	while (Graphics::getInstance().getWindow().isOpen())
	{
		sf::Event e;
		draw();
		while (Graphics::getInstance().getWindow().pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
			{
				Graphics::getInstance().getWindow().close();
			}
			break;
			}
		}
		m_exitButton->checkEvent(e);
		m_helpButton->checkEvent(e);
		m_newGameButton->checkEvent(e);
	}
}

Menu::~Menu()
{
	delete m_newGameButton;
	delete m_helpButton;
	delete m_exitButton;
}

void Menu::draw()
{
	Graphics::getInstance().getWindow().clear();
	m_title.draw();
	m_newGameButton->draw();
	m_helpButton->draw();
	m_exitButton->draw();
	Graphics::getInstance().getWindow().display();
}