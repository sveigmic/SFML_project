#include "PlayState.h"
#include <iostream>
#include <cmath>


PlayState::PlayState(StateStack & stack, Context context) : State(stack, context), m_Map(), camMoveSpeed(0, 0),
m_Player("./resources/sprites/player.png", sf::Vector2f(150.f, 117.f), sf::Vector2f(200.f, 200.f)),
m_MapView(sf::FloatRect(0, 0, sf::VideoMode::getDesktopMode().width * 0.80, sf::VideoMode::getDesktopMode().height)) {
	m_Map.loadDefaultMap();
	m_MapView.setViewport(sf::FloatRect(0, 0, 0.80, 1));
	//m_MiniMap.init(m_MapView);					
	getContext().m_Window->setView(m_MapView);
}


PlayState::~PlayState()
{
}

void PlayState::draw()
{
	//m_Map.reloadVertexArray();
	
	getContext().m_Window->setView(m_MapView);
	getContext().m_Window->draw(m_Map);
	getContext().m_Window->draw(m_Player);
	getContext().m_Window->setView(m_MiniMap.m_View);
    getContext().m_Window->draw(m_Map);
	getContext().m_Window->draw(m_Player);
	getContext().m_Window->setView(*getContext().m_MainView);
}

bool PlayState::update(sf::Time dt)
{
	getContext().m_Window->setView(m_MapView);
	m_Map.update(getContext().m_Window);
	return true;			    
}

bool PlayState::handleEvent(const sf::Event & ev)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*getContext().m_Window);
	if (ev.type == sf::Event::KeyPressed) {
		switch (ev.key.code) {
		case sf::Keyboard::Escape:
			stateStackClear();
			stateStackPush(States::Menu);
			break;
		case sf::Keyboard::Up:
			m_Player.updateDirection(Direction::Up);
			m_Player.move(sf::Vector2f(0, -4));
			break;
		case sf::Keyboard::Left:
			m_Player.updateDirection(Direction::Left);
			m_Player.move(sf::Vector2f(-4, 0));
			break;
		case sf::Keyboard::Right:
			m_Player.updateDirection(Direction::Right);
			m_Player.move(sf::Vector2f(4, 0));
			break;
		case sf::Keyboard::Down:
			m_Player.updateDirection(Direction::Down);
			m_Player.move(sf::Vector2f(0, 4));
			break;
		}

	}
	if (ev.type == sf::Event::MouseWheelMoved) {
		if (ev.mouseWheel.delta < 0) {
			m_MapView.zoom(1.1f);
		}
		else {
			m_MapView.zoom(0.9f);
		}
	}
	return false;
}