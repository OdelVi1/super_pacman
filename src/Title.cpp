#pragma once
#include "Title.h"

Title::Title() : m_sprite()
{
	m_sprite.setTexture(Graphics::getInstance().getTexture(GameTextures::PACMAN_TITLE));
	float window_center_x = (Graphics::getInstance().getWindow().getSize().x / float(2));
	sf::Vector2f position(sf::Vector2f(window_center_x - (m_sprite.getGlobalBounds().width / 2), 20));
	sf::Color border = sf::Color().Green;
	m_sprite.setPosition(position);
}