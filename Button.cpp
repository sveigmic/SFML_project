#include "Button.h"
#include <iostream>
#include <SFML\Graphics\RenderStates.hpp>

using namespace GUI;

Button::Button()
{
}

Button::Button(const sf::Vector2f& size, const std::string& file):m_SizeOfTexture(size), m_Action(), m_Texture(),m_Toggle(false), m_Sprite(), m_Text() {
	try {
		m_Texture.loadFromFile(file);
	}
	catch (int e) {
		std::cout << "Cant load btn texture: " << e << std::endl;
	}
	m_Size = sf::Vector2f(m_SizeOfTexture.x, m_SizeOfTexture.y / 3.f);
	m_Sprite = sf::Sprite(m_Texture, sf::IntRect(0, m_Size.y*Status::Normal, m_SizeOfTexture.x, m_Size.y));
	sf::FloatRect bounds = m_Sprite.getGlobalBounds();
	m_Sprite.setOrigin(std::floor(bounds.left + (bounds.width / 2.f)), std::floor(bounds.top + (bounds.height / 2.f)));
	m_Text.setColor(sf::Color::White);
}

Button::~Button()
{
}

void Button::setAction(Action act)
{
	m_Action = std::move(act);
}

void Button::setText(const std::string & text)
{
	m_Text.setString(text);	
	sf::FloatRect bounds = m_Text.getLocalBounds();
	m_Text.setOrigin(std::floor(bounds.left + (bounds.width / 2.f)), std::floor(bounds.top + (bounds.height / 2.f)));
	m_Text.setPosition(m_Sprite.getPosition());
}

void Button::setToggle(bool toggle)
{
	m_Toggle = toggle;
}

void Button::setFont(const sf::Font& font, const int& size)
{
	m_Text.setFont(font);
	m_Text.setCharacterSize(size);
}

bool Button::isSelectable() const
{
	return true;
}

void Button::select()
{
	Component::select();
	changeTexture(Status::Selected);
}

void Button::deselect()
{
	Component::deselect();
	changeTexture(Status::Normal);
}

void Button::activate()
{
	Component::activate();
	changeTexture(Status::Pressed);
	if (m_Action) {
		m_Action();
	}
}

void Button::deactivate()
{
	Component::deactivate();
	changeTexture(Status::Normal);
}

void Button::handleEvent(const sf::Event ev, const sf::RenderWindow* win)
{

	if (ev.key.code == sf::Mouse::Left) {
		if (ev.type == sf::Event::MouseButtonPressed && Component::isSelected()) {
			changeTexture(Status::Pressed);
		}
		else if (ev.type == sf::Event::MouseButtonReleased && Component::isSelected()) {
			activate();
			select();
		}
	} else if (ev.type == sf::Event::MouseMoved) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(*win);
		sf::Vector2f mousePosTrans = this->getInverseTransform().transformPoint(mousePos.x, mousePos.y);
		if (m_Sprite.getGlobalBounds().contains(mousePosTrans.x, mousePosTrans.y)) {
			if (!Component::isSelected()) select();
		}
		else {
			deselect();
			if (Component::isActive()) Component::deactivate();
		}
	}
}

void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(m_Sprite, states);
	target.draw(m_Text, states);
}

void Button::changeTexture(Status statusType)
{
	sf::IntRect rect = sf::IntRect(0, m_Size.y*statusType, m_SizeOfTexture.x, m_Size.y);
	m_Sprite.setTextureRect(rect);
}

