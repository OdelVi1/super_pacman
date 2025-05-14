#include "Button.h"

Button::Button(GameTextures texture) : m_sprite(), 
m_texture(Graphics::getInstance().getTexture(texture))
{
	m_sprite.setTexture(m_texture);
}

void Button::draw()
{
	Graphics::getInstance().getWindow().draw(m_sprite);
}

void Button::checkEvent(sf::Event& e)
{
	auto location = Graphics::getInstance().getWindow().mapPixelToCoords({ e.mouseButton.x, e.mouseButton.y });
	if (!m_sprite.getGlobalBounds().contains(location))
	{
		return;
	}
	switch (e.type)
	{
	case sf::Event::MouseButtonReleased:
	{
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			doThis();
			e = sf::Event();
		}
	}
	break;
	}
}