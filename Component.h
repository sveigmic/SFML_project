#ifndef CONPONENT_H
#define CONPONENT_H

#include <SFML/System/NonCopyable.hpp>
#include <SFML\Graphics.hpp>
#include <memory>


namespace GUI {

	class Component : public sf::Drawable, public sf::Transformable, public sf::NonCopyable
	{
	public:
		typedef std::shared_ptr<Component> sPtr;


		Component();
		~Component();

		virtual bool isSelectable() const = 0;
		bool isSelected() const;
		virtual void select();
		virtual void deselect();
		bool isActive() const;
		virtual void activate();
		virtual void deactivate();
		virtual void handleEvent(const sf::Event ev, const sf::RenderWindow* win = nullptr) = 0;

	private:
		bool m_Selected, m_Active;
	};
}
#endif CONPONENT_H


