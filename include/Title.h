#pragma once
#include "Graphics.h"
#include <SFML/Graphics.hpp>

class Title
{
public:
	Title();
	~Title() = default;
	sf::FloatRect getGlobalBounds() { return m_sprite.getGlobalBounds(); };
	void draw() { Graphics::getInstance().getWindow().draw(m_sprite); };
private:
	sf::Sprite m_sprite;
};