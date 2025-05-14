#pragma once
#include "Title.h"
#include "Button.h"
#include "Graphics.h"
#include "NewGameButton.h"
#include "ExitButton.h"
#include "HelpButton.h"

const float MENU_HEIGHT = 1000;
const float MENU_WIDTH = 1000;
const float MENU_X_POSITION = 100;
const float MENU_Y_POSITION = 300;
const float BUTTON_DISTANCE = 50;

class Menu
{
public:
	Menu();
	~Menu();
	void draw();
	void domenu();

private:
	NewGameButton *m_newGameButton;
	HelpButton *m_helpButton;
	ExitButton *m_exitButton;
	sf::RectangleShape m_rectangleShape;
	Title m_title;
};