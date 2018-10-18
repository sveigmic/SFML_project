#ifndef TILEMAP_H
#define TILEMAP_H

#include <SFML\Graphics.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include "TileIdentifiers.h"

class TileMap: public sf::Drawable, public sf::Transformable
{
public:
	TileMap();
	~TileMap();
	bool loadTileSet();
	bool loadDefaultMap();

	void update(sf::RenderWindow* window);
	void handleEvents(const sf::Event& ev);


	void setTile(const sf::Vector2i& pos, Tiles::ID id);

	sf::VertexArray* getVertex() {
		return &m_Vertices;
	}

	bool reloadVertexArray();
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	
	
private:
	int m_TileSetRow;
	Tiles::ID m_Map[150][150];
	sf::VertexArray m_Vertices;
	sf::Texture m_Tileset;
	sf::Vector2i m_TileSize;
	sf::RectangleShape m_ActTile;
};
#endif TILEMAP_H

