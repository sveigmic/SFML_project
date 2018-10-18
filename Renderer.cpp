#include "Renderer.h"

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::visitMenuState(MenuState & menuState)
{
}

void Renderer::visitEditState(EditState & editState)
{
}

void Renderer::visitButton(GUI::Button & btn)
{
	sf::RenderStates states;
	states.transform *= btn.getTransform();
	target.draw(btn.m_Sprite, states);
	target.draw(btn.m_Text, states);
}
