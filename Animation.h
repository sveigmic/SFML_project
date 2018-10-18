#pragma once
#include <string>
#include <SFML\Graphics.hpp>
#include <vector>
class Animation: public sf::Drawable, public sf::Transformable 
{
public:
	Animation();
	Animation(const sf::Texture& tex);
	~Animation();
	void addFrame(sf::IntRect rect);
	void setSpriteSheet(const sf::Texture& texture);
	void setFrame(size_t n);
	sf::IntRect& getFrame(size_t n);
private:
	std::vector<sf::IntRect> m_Frames;
	const sf::Texture* m_Texture;
	size_t actFrame;
	sf::Vertex m_vertices[4];

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

