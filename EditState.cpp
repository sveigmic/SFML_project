#include "EditState.h"



EditState::EditState(StateStack & stack, Context context) : State(stack, context), m_Map(), camMoveSpeed(0, 0) {
	m_Map.loadDefaultMap();
}


EditState::~EditState()
{
}

void EditState::draw()
{
	getContext().m_Window->draw(m_Map);
}

bool EditState::update(sf::Time dt)
{
	sf::View view = getContext().m_Window->getView();
	view.move(camMoveSpeed);
	getContext().m_Window->setView(view);
	m_Map.update(getContext().m_Window);
	return true;
}

bool EditState::handleEvent(const sf::Event & ev)
{
	if (ev.type == sf::Event::KeyPressed) {
		switch (ev.key.code) {
		case sf::Keyboard::Escape:
			stateStackClear();
			stateStackPush(States::Menu);
			break;
		}
	}
	sf::Vector2i mousePos = sf::Mouse::getPosition(*getContext().m_Window);
	sf::Vector2f coordPos = getContext().m_Window->mapPixelToCoords(mousePos);

	if (ev.type == sf::Event::MouseButtonPressed) {
		m_Map.setTile(sf::Vector2i(coordPos.x / 64, coordPos.y / 64),Tiles::Grass);
	}
	if (ev.type == sf::Event::MouseWheelMoved) {
		sf::View view = getContext().m_Window->getView();
		if (ev.mouseWheel.delta < 0) {
			view.zoom(1.1f);
		}
		else {
			view.zoom(0.9f);
		}
		getContext().m_Window->setView(view);
	}
	else if (ev.type == sf::Event::MouseMoved) {
		float border = 40;

		sf::Vector2i winSize(getContext().m_Window->getSize());
		float tmp;
		if (mousePos.x < border) {
			camMoveSpeed.x = -(border - mousePos.x);
		}
		else if ((tmp = abs(winSize.x - mousePos.x)) < border) {
			camMoveSpeed.x = border - tmp;
		}
		else camMoveSpeed.x = 0;

		if (mousePos.y < border) {
			camMoveSpeed.y = -(border - mousePos.y);
		}
		else if ((tmp = abs(winSize.y - mousePos.y)) < border) {
			camMoveSpeed.y = border - tmp;
		}
		else camMoveSpeed.y = 0;
	}

	return false;
}
