#include "Minimap.h"
#include <iostream>



Minimap::Minimap()
{
	sf::Vector2f win_size(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
	float x_size = win_size.x*0.2;
	float y_coefic = x_size / win_size.y;
	m_View.reset(sf::FloatRect(0.8*win_size.x, (1-y_coefic)*win_size.y, x_size,y_coefic*win_size.y));
	m_View.setViewport(sf::FloatRect(0.8, (1 - y_coefic), 1, 1));
	m_View.setCenter(0.8*win_size.x, (1 - y_coefic)*win_size.y);
	m_View.setSize(x_size, y_coefic*win_size.y);
	m_View.move(60*220,60*220);
	m_View.zoom(80.f);
}

Minimap::~Minimap()
{
}

void Minimap::init(const sf::View & mapview)
{
	m_View.setCenter(mapview.getCenter());
}
