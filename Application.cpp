#pragma once
#include "Application.h"
#include <iostream>
#include "StringManager.h"
#include "MenuState.h"
#include "PlayState.h"
#include "EditState.h"


Application::Application(): m_Window(), m_Fps(0), m_UpdateTime(sf::Time::Zero),
	m_StateStack(State::Context(m_Window, m_Fonts, new sf::View(sf::FloatRect(0, 0, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height)), m_GuiView)) {
	sf::VideoMode videoMode(1920, 1080, 32);
	m_Window.create(videoMode, "Game", sf::Style::Fullscreen);
	m_Window.setFramerateLimit(60);
	loadFonts();
	sf::Texture f;
	f.loadFromFile("./resources/tiles/tile.png");
	m_AppInfo = sf::Text("", m_Fonts.get(Fonts::Broshk), 40);
	m_AppInfo.setColor(sf::Color::White);
	registerStates();
	m_StateStack.push(States::Menu);

}


Application::~Application() {
}

void Application::run() {
	sf::Clock clk;
	sf::Time timeSinceLastUp = sf::Time::Zero;
	while (m_Window.isOpen()) {
		sf::Time dt = clk.restart();
		timeSinceLastUp += dt;
		while (timeSinceLastUp > FrameTime) {
			timeSinceLastUp -= FrameTime;

			handleInput();
			update(dt);
		}
		updateAppInfo(dt);
		render();
	}
}


void Application::handleInput() {
	sf::Event ev;
	while (m_Window.pollEvent(ev)) {
		if (ev.type == sf::Event::Closed) {
			m_Window.close();
		}
		
		m_StateStack.handleEvents(ev);
	}
}

void Application::update(sf::Time dt) {
	m_StateStack.update(dt);
	m_AppInfo.setPosition(20,20);

}

void Application::updateAppInfo(sf::Time dt) {
	m_UpdateTime += dt;
	m_Fps++;
	if (m_UpdateTime >= sf::seconds(1.0f)) {
		m_AppInfo.setString("FPS = " + toString(m_Fps) + "\n");

		m_UpdateTime -= sf::seconds(1.0f);
		m_Fps = 0;
	}
}

void Application::render() {
	m_Window.clear();
	m_StateStack.draw();
	m_Window.draw(m_AppInfo);
	m_Window.display();
}

void Application::loadFonts()
{
	m_Fonts.load(Fonts::Broshk, "./resources/fonts/broshk.otf");
}

void Application::registerStates() {
	m_StateStack.registerState<MenuState>(States::Menu);
	m_StateStack.registerState<PlayState>(States::Play);
	m_StateStack.registerState<EditState>(States::Edit);
}