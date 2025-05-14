#include "NewGameButton.h"

NewGameButton::NewGameButton(float height) : Button(GameTextures::NEW_GAME_BUTTON)
{
	m_sprite.scale(BUTTON_WIDTH / m_sprite.getGlobalBounds().width, 
		BUTTON_HEIGHT / m_sprite.getGlobalBounds().height);
	float window_center_x = (Graphics::getInstance().getWindow().getSize().x / float(2));
	m_sprite.setPosition(sf::Vector2f(window_center_x - m_sprite.getGlobalBounds().width / 2, height));
}

void NewGameButton::doThis()
{
	Controller controller;
	controller.startGame();
}
