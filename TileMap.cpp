#include "TileMap.h"

#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 



TileMap::TileMap(): m_TileSize(64,64)
{
	m_ActTile = sf::RectangleShape(sf::Vector2f(m_TileSize));
	m_ActTile.setFillColor(sf::Color::Transparent);
	m_ActTile.setOutlineColor(sf::Color::Red);
	m_ActTile.setOutlineThickness(5);

}


TileMap::~TileMap()
{
}

bool TileMap::loadTileSet() {
	if (!m_Tileset.loadFromFile("./resources/tiles/tileset.png")) {
		throw("Cant load tileset");
	}
	m_TileSetRow = 2;
}


bool TileMap::loadDefaultMap() {
	loadTileSet();
	srand(time(NULL));
	for (int i = 0; i < 150; i++) {
		for (int j = 0; j < 150; j++) {
			int x = rand() % 3;
			switch (x) {
			case 0:
				m_Map[i][j] = Tiles::Water;
				break;
			case 1:
				m_Map[i][j] = Tiles::Grass;
				break;
			case 2:
				m_Map[i][j] = Tiles::Sand;
				break;
			}
		}

	}
	reloadVertexArray();
	return true;
}

bool TileMap::reloadVertexArray()
{
	int width, height;
	width = height = 150;
	m_Vertices.setPrimitiveType(sf::Quads);
	m_Vertices.resize(width * height * 4);
	for (unsigned int i = 0; i < width; ++i) {
		for (unsigned int j = 0; j < height; ++j)
		{


			Tiles::ID tileNumber = m_Map[i][j];

			int tu = tileNumber % (m_Tileset.getSize().x / m_TileSize.x);
			int tv = tileNumber / (m_Tileset.getSize().x / m_TileSize.x);
			sf::Vertex* quad = &m_Vertices[(i + j * width) * 4];

			quad[0].position = sf::Vector2f(i * m_TileSize.x, j * m_TileSize.y);
			quad[1].position = sf::Vector2f((i + 1) * m_TileSize.x, j * m_TileSize.y);
			quad[2].position = sf::Vector2f((i + 1) * m_TileSize.x, (j + 1) * m_TileSize.y);
			quad[3].position = sf::Vector2f(i * m_TileSize.x, (j + 1) * m_TileSize.y);

			quad[0].texCoords = sf::Vector2f(tu * m_TileSize.x, tv * m_TileSize.y);
			quad[1].texCoords = sf::Vector2f((tu + 1) * m_TileSize.x, tv * m_TileSize.y);
			quad[2].texCoords = sf::Vector2f((tu + 1) * m_TileSize.x, (tv + 1) * m_TileSize.y);
			quad[3].texCoords = sf::Vector2f(tu * m_TileSize.x, (tv + 1) * m_TileSize.y);
		}
	}
	return true;
}

void TileMap::update(sf::RenderWindow * window)
{
	
	sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
	sf::Vector2f worldPos = window->mapPixelToCoords(mousePos);
	sf::Vector2i tilePos(worldPos.x / m_TileSize.x, worldPos.y / m_TileSize.y);
	m_ActTile.setPosition(m_TileSize.x * tilePos.x, m_TileSize.y * tilePos.y);
}

void TileMap::handleEvents(const sf::Event & ev)
{
}

void TileMap::setTile(const sf::Vector2i& pos,Tiles::ID id)
{
	m_Map[pos.x][pos.y] = id;
	reloadVertexArray();
}

void TileMap::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	sf::RectangleShape x(sf::Vector2f(64.f, 64.f));

	states.transform *= getTransform();
	states.texture = &m_Tileset;
	target.draw(m_Vertices, states);
	target.draw(m_ActTile, states);
}