#ifndef EDITSTATE_H
#define EDITSTATE_H

#include "State.h"
#include "TileMap.h"

class EditState: public State
{
public:
	EditState(StateStack & stack, Context context);
	~EditState();
	virtual void draw() override;

	virtual bool update(sf::Time dt) override;

	virtual bool handleEvent(const sf::Event & event) override;

private:
	TileMap m_Map;
	sf::Vector2f camMoveSpeed;

private:


private:

};

#endif EDITSTATE_H

