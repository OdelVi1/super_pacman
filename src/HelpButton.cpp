#include "HelpButton.h"

HelpButton::HelpButton(float height) : Button(GameTextures::HELP_BUTTON),
m_instruction(Graphics::getInstance().getTexture(GameTextures::INSTRUCTION)),
m_return(Graphics::getInstance().getTexture(GameTextures::RETURN))
{
	m_sprite.scale(BUTTON_WIDTH / m_sprite.getGlobalBounds().width,
		BUTTON_HEIGHT / m_sprite.getGlobalBounds().height);
	m_instruction.scale(Graphics::getInstance().getWindow().getSize().x / m_instruction.getGlobalBounds().width,
		Graphics::getInstance().getWindow().getSize().y / m_instruction.getGlobalBounds().height);
	
	float window_center_x = (Graphics::getInstance().getWindow().getSize().x / float(CENTER));
	m_sprite.setPosition(sf::Vector2f(window_center_x - m_sprite.getGlobalBounds().width / CENTER, height));

	m_return.scale(SCALE_SIZE, SCALE_SIZE);
	m_return.setPosition(sf::Vector2f(window_center_x - m_return.getGlobalBounds().width / CENTER,
		POSITION));
}

void HelpButton::doThis()
{
	Graphics::getInstance().getWindow().clear();
	Graphics::getInstance().getWindow().draw(m_instruction);
	Graphics::getInstance().getWindow().draw(m_return);
	Graphics::getInstance().getWindow().display();
	auto e = sf::Event();
	while (Graphics::getInstance().getWindow().isOpen())
	{
		if (Graphics::getInstance().getWindow().pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
			{
				Graphics::getInstance().getWindow().close();
			}
			case sf::Event::MouseButtonReleased:
			{
				if (e.mouseButton.button == sf::Mouse::Left)
				{
					auto location = Graphics::getInstance().getWindow().mapPixelToCoords({ e.mouseButton.x, e.mouseButton.y });
					if (m_return.getGlobalBounds().contains(location))
					{
						return;
					}
				}
			}
			}
		}
	}
}