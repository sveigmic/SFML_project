#pragma once

#include <SFML\Graphics.hpp>
#include "Directions.h"

class Player: public sf::Drawable, public sf::Transformable
{
public:
	Player();
	Player(std::string file, sf::Vector2f size,sf::Vector2f pos);
	~Player();
	void move(sf::Vector2f offset);
	void updateDirection(Direction::DIRECTION direction);

private:
	sf::Vector2f m_Pos;
	sf::Sprite m_Sprite;
	sf::Vector2f m_SizeOfTexture;
	sf::Vector2f m_Size;
	sf::Texture m_Texture;


	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};