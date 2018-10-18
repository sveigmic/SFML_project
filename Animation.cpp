#include "Animation.h"

Animation::Animation() {
}

Animation::Animation(const sf::Texture& tex): m_Texture(&tex) {
}

Animation::~Animation() {
}

void Animation::addFrame(sf::IntRect rect)
{
	m_Frames.push_back(rect);
}

void Animation::setSpriteSheet(const sf::Texture & texture) {
	m_Texture = &texture;
}

void Animation::setFrame(size_t n) {
	actFrame = n;
	sf::IntRect rect = m_Frames[n];

	m_vertices[0].position = sf::Vector2f(0.f, 0.f);
	m_vertices[1].position = sf::Vector2f(0.f, static_cast<float>(rect.height));
	m_vertices[2].position = sf::Vector2f(static_cast<float>(rect.width), static_cast<float>(rect.height));
	m_vertices[3].position = sf::Vector2f(static_cast<float>(rect.width), 0.f);

	float left = static_cast<float>(rect.left) + 0.0001f;
	float right = left + static_cast<float>(rect.width);
	float top = static_cast<float>(rect.top);
	float bottom = top + static_cast<float>(rect.height);

	m_vertices[0].texCoords = sf::Vector2f(left, top);
	m_vertices[1].texCoords = sf::Vector2f(left, bottom);
	m_vertices[2].texCoords = sf::Vector2f(right, bottom);
	m_vertices[3].texCoords = sf::Vector2f(right, top);
}

sf::IntRect& Animation::getFrame(size_t n)
{
	return m_Frames[n];
}

void Animation::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = m_Texture;
	target.draw(m_vertices, 4, sf::Quads, states);
}