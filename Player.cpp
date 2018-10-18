#include "Player.h"
#include <iostream>

Player::Player()
{
}

Player::Player(std::string file, sf::Vector2f size, sf::Vector2f pos) : m_SizeOfTexture(size), m_Pos(pos)
{
	try {
		m_Texture.loadFromFile(file);
	}
	catch (int e) {
		std::cout << "Cant load btn texture: " << e << std::endl;
	}
	m_Size = sf::Vector2f(m_SizeOfTexture.x, m_SizeOfTexture.y);
	m_Sprite = sf::Sprite(m_Texture, sf::IntRect(0, 0, m_SizeOfTexture.x, m_SizeOfTexture.y));
	m_Sprite.setPosition(pos);
	//sf::FloatRect bounds = m_Sprite.getGlobalBounds();
	//m_Sprite.setOrigin(std::floor(bounds.left + (bounds.width / 2.f)), std::floor(bounds.top + (bounds.height / 2.f)));
}

Player::~Player()
{
}

void Player::move(sf::Vector2f offset)
{
	m_Sprite.move(offset);
}

void Player::updateDirection(Direction::DIRECTION direction)
{
	m_Sprite.setTextureRect(sf::IntRect(0, m_SizeOfTexture.y*(int)direction, m_SizeOfTexture.x, m_SizeOfTexture.y));
}

void Player::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_Sprite, states);
}