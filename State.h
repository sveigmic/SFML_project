#ifndef STATE_H
#define STATE_H

#include "State.h"
#include "StatesIdentifiers.h"
#include "ResourceIdentifiers.h"
#include <SFML\Graphics.hpp>
#include <memory>

class StateStack;

class State
{
public:
	typedef std::unique_ptr<State> uPtr;
	struct Context {
		Context(sf::RenderWindow& window, FontHolder& fonts, sf::View* mainView, sf::View* guiView);

		sf::RenderWindow* m_Window;
		sf::View *m_MainView, *m_GUIView;
		FontHolder* m_Fonts;

	}; 
	
	State(StateStack& stateStack, Context context);
	~State();

	virtual void draw() = 0;
	virtual bool update(sf::Time dt) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;

//FUNC
protected:
	void stateStackPush(States::ID id);
	void stateStackPop();
	void stateStackClear();

	Context getContext() const;

private:
	StateStack* m_StateStack;
	Context m_Context;


};

#endif STATE_H

