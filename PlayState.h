#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "State.h"
#include "TileMap.h"
#include "Minimap.h"
#include "Player.h"

class PlayState : public State
{
public:
	PlayState(StateStack & stack, Context context);
	~PlayState();

	virtual void draw() override;

	virtual bool update(sf::Time dt) override;

	virtual bool handleEvent(const sf::Event & event) override;

private:
	TileMap m_Map;
	Minimap m_MiniMap;
	Player m_Player;
	sf::Vector2f camMoveSpeed;
	sf::View m_MapView;

};
#endif PLAYSTATE_H
