#include "Component.h"
   
using namespace GUI;	

Component::Component(): m_Selected(false), m_Active(false)
{
}


Component::~Component()
{
}

bool Component::isSelected() const
{
	return m_Selected;
}

void Component::select()
{
	m_Selected = true;
}

void Component::deselect()
{
	m_Selected = false;
}

bool Component::isActive() const
{
	return m_Active;
}

void Component::activate()
{
	m_Active = true;
}

void Component::deactivate()
{
	m_Active = false;
}

