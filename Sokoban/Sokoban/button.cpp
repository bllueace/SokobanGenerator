#include "button.h"

gui::button::button()
{

}

gui::button::button(std::string s, sf::Font& font, sf::Vector2f position, sf::Uint32 style)
{
	//set position
	m_position = position;

	//set initial state
	m_btnstate = gui::state::normal;

	//set button style
	m_style = style;

	switch (m_style)
	{
	case gui::style::none:
	{
		m_textNormal = sf::Color(255, 255, 255);
		m_textHover = sf::Color(255, 255, 255);
		m_textClicked = sf::Color(255, 255, 255);
		m_bgNormal = sf::Color(255, 255, 255, 100);
		m_bgHover = sf::Color(200, 200, 200, 100);
		m_bgClicked = sf::Color(150, 150, 150);
		m_border = sf::Color(255, 255, 255, 100);
	}
	break;

	case gui::style::save:
	{
		m_textNormal = sf::Color(255, 255, 255);
		m_textHover = sf::Color(255, 255, 255);
		m_textClicked = sf::Color(255, 255, 255);
		m_bgNormal = sf::Color(0, 255, 0, 100);
		m_bgHover = sf::Color(0, 200, 0, 100);
		m_bgClicked = sf::Color(0, 150, 0);
		m_border = sf::Color(0, 0, 0, 100);
	}
	break;

	case gui::style::cancel:
	{
		m_textNormal = sf::Color(255, 255, 255);
		m_textHover = sf::Color(255, 255, 255);
		m_textClicked = sf::Color(255, 255, 255);
		m_bgNormal = sf::Color(255, 0, 0, 100);
		m_bgHover = sf::Color(200, 0, 0, 100);
		m_bgClicked = sf::Color(150, 0, 0);
		m_border = sf::Color(255, 255, 255, 100);
	}
	break;

	case gui::style::clean:
	{
		m_textNormal = sf::Color(255, 255, 255);
		m_textHover = sf::Color(255, 255, 255);
		m_textClicked = sf::Color(255, 255, 255);
		m_bgNormal = sf::Color(0, 255, 255, 100);
		m_bgHover = sf::Color(0, 200, 200, 100);
		m_bgClicked = sf::Color(0, 150, 150);
		m_border = sf::Color(255, 255, 255, 100);
	}
	break;

	default:
		break;
	}

	//set up text
	m_text.setString(s);
	m_text.setFont(font);
	m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
	m_text.setFillColor(m_textNormal);

	//set some defauts
	m_borderRadius = 5.f;
	m_borderThickness = 0.f;
	m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.5f);

	//m_button = sf::RectangleShape(m_size, m_borderRadius, m_bgNormal, m_borderThickness, m_border);
	m_button = sf::RectangleShape(sf::Vector2f(50, 300));
	m_button.setOrigin(m_button.getGlobalBounds().width / 2, m_button.getGlobalBounds().height / 2);
	m_button.setPosition(m_position);

	sf::Vector2f textPosition = sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_button.getGlobalBounds().height / 4);

	m_text.setPosition(textPosition);

	m_shadow.setFont(font);
	m_shadow = m_text;
	m_shadow.setOrigin(m_shadow.getGlobalBounds().width / 2, m_shadow.getGlobalBounds().height / 2);
	m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);
}

gui::button::~button()
{

}

void gui::button::setSize(unsigned int size)
{
	m_fontSize = size;
	m_text.setCharacterSize(m_fontSize);
	m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
	m_shadow.setCharacterSize(m_fontSize);
	m_shadow.setOrigin(m_shadow.getGlobalBounds().width / 2, m_shadow.getGlobalBounds().height / 2);
	m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, (m_text.getGlobalBounds().height + m_text.getGlobalBounds().height) * 1.5f);
	//m_button = thor::Shapes::roundedRect(m_size, m_borderRadius, m_bgNormal, m_borderThickness, m_border);
	m_button = sf::RectangleShape(sf::Vector2f(50, 300));

}

void gui::button::setStyle(sf::Uint32 style)
{
	//set button style
	m_style = style;

	switch (m_style)
	{
	case gui::style::none:
	{
		m_textNormal = sf::Color(255, 255, 255);
		m_textHover = sf::Color(255, 255, 255);
		m_textClicked = sf::Color(255, 255, 255);
		m_bgNormal = sf::Color(255, 255, 255, 100);
		m_bgHover = sf::Color(200, 200, 200, 100);
		m_bgClicked = sf::Color(150, 150, 150);
		m_border = sf::Color(255, 255, 255, 100);
	}
	break;

	case gui::style::save:
	{
		m_textNormal = sf::Color(255, 255, 255);
		m_textHover = sf::Color(255, 255, 255);
		m_textClicked = sf::Color(255, 255, 255);
		m_bgNormal = sf::Color(0, 255, 0, 100);
		m_bgHover = sf::Color(0, 200, 0, 100);
		m_bgClicked = sf::Color(0, 150, 0);
		m_border = sf::Color(0, 0, 0, 100);
	}
	break;

	case gui::style::cancel:
	{
		m_textNormal = sf::Color(255, 255, 255);
		m_textHover = sf::Color(255, 255, 255);
		m_textClicked = sf::Color(255, 255, 255);
		m_bgNormal = sf::Color(255, 0, 0, 100);
		m_bgHover = sf::Color(200, 0, 0, 100);
		m_bgClicked = sf::Color(150, 0, 0);
		m_border = sf::Color(255, 255, 255, 100);
	}
	break;

	case gui::style::clean:
	{
		m_textNormal = sf::Color(255, 255, 255);
		m_textHover = sf::Color(255, 255, 255);
		m_textClicked = sf::Color(255, 255, 255);
		m_bgNormal = sf::Color(0, 255, 255, 100);
		m_bgHover = sf::Color(0, 200, 200, 100);
		m_bgClicked = sf::Color(0, 150, 150);
		m_border = sf::Color(255, 255, 255, 100);
	}
	break;

	default:
		break;
	}
}

void gui::button::setFont(sf::Font& font)
{
	m_text.setFont(font);
	m_shadow.setFont(font);
}

void gui::button::update(sf::Event& e, sf::RenderWindow& window)
{
	//perform updates for settings from user
	switch (m_style)
	{
	case gui::style::none:
	{
		m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.75f);
		//m_button = thor::Shapes::roundedRect(m_size, m_borderRadius, m_bgNormal, m_borderThickness, m_border);
		m_button = sf::RectangleShape(sf::Vector2f(m_size));

		m_button.setOrigin(m_button.getGlobalBounds().width / 2, m_button.getGlobalBounds().height / 2);
		m_button.setPosition(m_position);
		m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
		sf::Vector2f textPosition = sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_button.getGlobalBounds().height / 4);
		m_text.setPosition(textPosition);
		m_text.setFillColor(m_textNormal);
		m_shadow.setOrigin(m_shadow.getGlobalBounds().width / 2, m_shadow.getGlobalBounds().height / 2);
		m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);
		m_shadow.setFillColor(sf::Color(0, 0, 0));
	}
	break;

	case gui::style::save:
	{
		m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.75f);
		//m_button = thor::Shapes::roundedRect(m_size, m_borderRadius, m_bgNormal, m_borderThickness, m_border);
		m_button = sf::RectangleShape(sf::Vector2f(m_size));
		m_button.setOrigin(m_button.getGlobalBounds().width / 2, m_button.getGlobalBounds().height / 2);
		m_button.setPosition(m_position);
		m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
		sf::Vector2f textPosition = sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_button.getGlobalBounds().height / 4);
		m_text.setPosition(textPosition);
		m_text.setFillColor(m_textNormal);
		m_shadow.setOrigin(m_shadow.getGlobalBounds().width / 2, m_shadow.getGlobalBounds().height / 2);
		m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);
		m_shadow.setFillColor(sf::Color(0, 0, 0));
	}
	break;

	case gui::style::cancel:
	{
		m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.75f);
		//m_button = thor::Shapes::roundedRect(m_size, m_borderRadius, m_bgNormal, m_borderThickness, m_border);
		m_button = sf::RectangleShape(sf::Vector2f(m_size));
		m_button.setOrigin(m_button.getGlobalBounds().width / 2, m_button.getGlobalBounds().height / 2);
		m_button.setPosition(m_position);
		m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
		sf::Vector2f textPosition = sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_button.getGlobalBounds().height / 4);
		m_text.setPosition(textPosition);
		m_text.setFillColor(m_textNormal);
		m_shadow.setOrigin(m_shadow.getGlobalBounds().width / 2, m_shadow.getGlobalBounds().height / 2);
		m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);
		m_shadow.setFillColor(sf::Color(0, 0, 0));
	}
	break;

	case gui::style::clean:
	{
		m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.75f);
		//m_button = thor::Shapes::roundedRect(m_size, m_borderRadius, m_bgNormal, m_borderThickness, m_border);
		m_button = sf::RectangleShape(sf::Vector2f(m_size));
		m_button.setOrigin(m_button.getGlobalBounds().width / 2, m_button.getGlobalBounds().height / 2);
		m_button.setPosition(m_position);
		m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
		sf::Vector2f textPosition = sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_button.getGlobalBounds().height / 4);
		m_text.setPosition(textPosition);
		m_text.setFillColor(m_textNormal);
		m_shadow.setOrigin(m_shadow.getGlobalBounds().width / 2, m_shadow.getGlobalBounds().height / 2);
		m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);
		m_shadow.setFillColor(sf::Color(0, 0, 0));
	}
	break;

	default:
		break;
	}

	//perform updates for user mouse interactions
	sf::Vector2i m_mousePosition = sf::Mouse::getPosition(window);

	bool mouseInButton = m_mousePosition.x >= m_button.getPosition().x - m_button.getGlobalBounds().width / 2
		&& m_mousePosition.x <= m_button.getPosition().x + m_button.getGlobalBounds().width / 2
		&& m_mousePosition.y >= m_button.getPosition().y - m_button.getGlobalBounds().height / 2
		&& m_mousePosition.y <= m_button.getPosition().y + m_button.getGlobalBounds().height / 2;

	if (e.type == sf::Event::MouseMoved)
	{
		if (mouseInButton)
		{
			m_btnstate = gui::state::hovered;
		}

		else
		{
			m_btnstate = gui::state::normal;
		}
	}

	if (e.type == sf::Event::MouseButtonPressed)
	{
		switch (e.mouseButton.button)
		{
		case sf::Mouse::Left:
		{
			if (mouseInButton)
			{
				m_btnstate = gui::state::clicked;
			}

			else
			{
				m_btnstate = gui::state::normal;
			}
		}
		break;
		}
	}

	if (e.type == sf::Event::MouseButtonReleased)
	{
		switch (e.mouseButton.button)
		{
		case sf::Mouse::Left:
		{
			if (mouseInButton)
			{
				m_btnstate = gui::state::hovered;
			}

			else
			{
				m_btnstate = gui::state::normal;
			}
		}
		}
	}

	switch (m_btnstate)
	{
	case gui::state::normal:
	{
		m_button.setFillColor(m_bgNormal);
		m_text.setFillColor(m_textNormal);
	}
	break;

	case gui::state::hovered:
	{
		m_button.setFillColor(m_bgHover);
		m_text.setFillColor(m_textHover);
	}
	break;

	case gui::state::clicked:
	{
		m_button.setFillColor(m_bgClicked);
		m_text.setFillColor(m_textClicked);
	}
	break;
	}
}

void gui::button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	switch (m_style)
	{
	case gui::style::none:
	{
		target.draw(m_button, states);
		target.draw(m_shadow, states);
		target.draw(m_text, states);
	}
	break;

	case gui::style::save:
	{
		target.draw(m_button, states);
		target.draw(m_shadow, states);
		target.draw(m_text, states);
	}
	break;

	case gui::style::cancel:
	{
		target.draw(m_button, states);
		target.draw(m_shadow, states);
		target.draw(m_text, states);
	}
	break;

	case gui::style::clean:
	{
		target.draw(m_button, states);
		target.draw(m_shadow, states);
		target.draw(m_text, states);
	}
	break;

	default:
		break;
	}
}