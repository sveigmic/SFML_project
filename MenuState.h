#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include "Button.h"



class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context context);
	~MenuState();

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
private:
	void exit();

private:
	GUI::Button m_Start;
	GUI::Button m_Editor;
	GUI::Button m_Options;
	GUI::Button m_Exit;
};

#endif MENUSTATE_H
