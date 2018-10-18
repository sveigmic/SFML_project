#ifndef STATESTACK_H
#define STATESTACK_H

#include <SFML\System\NonCopyable.hpp>
#include <SFML\Graphics.hpp>
#include <map>
#include <vector>
#include <memory>
#include <functional>

#include "State.h"
#include "StatesIdentifiers.h"



class StateStack: public sf::NonCopyable
{
public:

	enum Actions {
		Push,
		Pop,
		Clear,
	};


	 explicit StateStack(State::Context context);
	~StateStack();

	void handleEvents(const sf::Event& ev);
	void update(sf::Time dt);
	void draw();

	void push(States::ID stateID);
	void pop();
	void clear();

	template<typename T> void registerState(States::ID stateID);

private:
	State::uPtr createState(States::ID id);
	void applyWaitingChanges();

private:
	struct WaitingChange {
		explicit WaitingChange(Actions act, States::ID id = States::ID::None);
		States::ID m_Id;
		Actions m_Action;
	};

	State::Context m_Context;
	std::vector<WaitingChange> m_StateQueue;
	std::map<States::ID, std::function<State::uPtr()>> m_RegisteredStates;
	std::vector<State::uPtr> m_Stack;
};

template<typename T>
void StateStack::registerState(States::ID stateID) {
	m_RegisteredStates[stateID] = [this]() {
		return State::uPtr(new T(*this,m_Context));
	};
}

#endif STATESTACK_H