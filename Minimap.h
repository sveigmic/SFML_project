#pragma once

#include <SFML\Graphics.hpp>

class Minimap
{
public:
	Minimap();
	~Minimap();
	
	void init(const sf::View& mapview);

	sf::Vector2i m_Size;
	sf::View m_View;
	sf::RectangleShape m_Border;
};