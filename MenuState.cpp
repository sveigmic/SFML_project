#include "MenuState.h"
#include "ResourceIdentifiers.h"
#include "ResourceHolder.h"
#include <iostream>


MenuState::MenuState(StateStack & stack, Context context):State(stack,context),
m_Start(sf::Vector2f(256.f, 240.f), "./resources/textures/buttons/start.png"),
m_Editor(sf::Vector2f(256.f, 240.f), "./resources/textures/buttons/start.png"),
m_Options(sf::Vector2f(256.f, 240.f), "./resources/textures/buttons/start.png"),
m_Exit(sf::Vector2f(256.f, 240.f), "./resources/textures/buttons/start.png")
{
	int scH = sf::VideoMode::getDesktopMode().height;
	int scW = sf::VideoMode::getDesktopMode().width;
	m_Start.setPosition(sf::Vector2f(scW/2,180));
	m_Start.setFont(getContext().m_Fonts->get(Fonts::Broshk), 50);   
	m_Start.setText("Start");
	m_Start.setAction([this]() {
		stateStackClear();
		stateStackPush(States::Play);
	}); 
	m_Editor.setPosition(sf::Vector2f(scW / 2, 280));
	m_Editor.setFont(getContext().m_Fonts->get(Fonts::Broshk), 50);
	m_Editor.setText("Edit");
	m_Editor.setAction([this]() {
		stateStackClear();
		stateStackPush(States::Edit);
	});
	m_Options.setPosition(sf::Vector2f(scW / 2, 380));
	m_Options.setFont(getContext().m_Fonts->get(Fonts::Broshk), 50);
	m_Options.setText("Options");
	m_Options.setAction([this]() {
		std::cout << "Options not ready yet" << std::endl;
	});
	m_Exit.setPosition(sf::Vector2f(scW / 2, 480));
	m_Exit.setFont(getContext().m_Fonts->get(Fonts::Broshk), 50);
	m_Exit.setText("Exit");
	m_Exit.setAction([this]() {
		exit();
	});
}

MenuState::~MenuState()
{
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().m_Window;

	window.setView(*getContext().m_MainView);
	
	window.draw(m_Start);
	window.draw(m_Editor);
	window.draw(m_Options);
	window.draw(m_Exit);
}

bool MenuState::update(sf::Time dt)
{			
	return true; 
}

bool MenuState::handleEvent(const sf::Event & ev)
{
	m_Start.handleEvent(ev,getContext().m_Window);
	m_Editor.handleEvent(ev, getContext().m_Window);
	m_Options.handleEvent(ev, getContext().m_Window);
	m_Exit.handleEvent(ev, getContext().m_Window);
	return true;
}

void MenuState::exit()
{
	getContext().m_Window->close();
}