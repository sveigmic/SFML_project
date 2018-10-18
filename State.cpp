#pragma once
#include "State.h"
#include "StateStack.h"

State::Context::Context(sf::RenderWindow& window, FontHolder& fonts, sf::View* mainView, sf::View* guiView)
			:m_Window(&window), m_Fonts(&fonts), m_MainView(mainView), m_GUIView(guiView){
}

State::State(StateStack& stateStack, Context context):m_StateStack(&stateStack), m_Context(context) {
}

State::~State() {
}

void State::stateStackPush(States::ID id) {
	m_StateStack->push(id);
}

void State::stateStackPop() {
	m_StateStack->pop();
}

void State::stateStackClear() {
	m_StateStack->clear();
}

State::Context State::getContext() const
{
	return m_Context;
}

