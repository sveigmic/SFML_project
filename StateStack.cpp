#include "StateStack.h"
#include <cassert>
#include <iostream>


StateStack::StateStack(State::Context context): m_Stack(), m_RegisteredStates(), m_Context(context) {
}


StateStack::~StateStack()
{
}


void StateStack::handleEvents(const sf::Event& ev) {
	for (auto x = m_Stack.rbegin(); x != m_Stack.rend(); x++) {
		if (!x->get()->handleEvent(ev)) break;
	}
	applyWaitingChanges();
}

void StateStack::update(sf::Time dt) {
	for (auto x = m_Stack.rbegin(); x != m_Stack.rend(); x++) {
		if (!x->get()->update(dt)) break;;
	}
	applyWaitingChanges();
}

void StateStack::draw() {
	for (auto x = m_Stack.begin(); x != m_Stack.end(); x++) {
		x->get()->draw();
	}
}

void StateStack::push(States::ID stateID) {
	m_StateQueue.push_back(WaitingChange(Actions::Push,stateID));
	
}				 

void StateStack::pop() {
	m_StateQueue.push_back(WaitingChange(Actions::Pop));
}

void StateStack::clear() {
	m_StateQueue.push_back(WaitingChange(Actions::Clear));
}

State::uPtr StateStack::createState(States::ID id)
{
	auto x = m_RegisteredStates.find(id);
	assert(x != m_RegisteredStates.end());
	return x->second();
}

void StateStack::applyWaitingChanges() {
	for (std::vector<WaitingChange>::iterator it = m_StateQueue.begin(); it != m_StateQueue.end(); it++) {
		switch (it->m_Action) {
		case Push:
			m_Stack.push_back(createState(it->m_Id));
			break;
		case Pop:
			m_Stack.pop_back();
			break;
		case Clear:
			m_Stack.clear();
			break;
		}
	}
	m_StateQueue.clear();
}

StateStack::WaitingChange::WaitingChange(Actions act, States::ID id) : m_Action(act), m_Id(id) {
}
