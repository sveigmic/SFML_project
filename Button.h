#ifndef BUTTON_H
#define BUTTON_H

#include "Component.h"
#include <memory>
#include <functional>
#include <SFML\Graphics.hpp>
#include <string>

namespace GUI {

	class Button : public Component {
	public:
		enum Status {
			Normal,
			Selected,
			Pressed,
		};
		typedef std::shared_ptr<Button> sPtr;
		typedef std::function<void()> Action;
									 
		Button();
		Button(const sf::Vector2f& size, const std::string& file);
		~Button();

		void setAction(Action act);
		void setText(const std::string& text);
		void setToggle(bool toggle);
		void setFont(const sf::Font& font, const int& size);

		virtual bool isSelectable() const;
		virtual void select();
		virtual void deselect();
		virtual void activate();
		virtual void deactivate();
		virtual void handleEvent(const sf::Event ev, const sf::RenderWindow* win = nullptr);

		sf::Sprite m_Sprite;
		sf::Text m_Text;

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void changeTexture(Status statusType);
	private:
		Action m_Action;
		sf::Vector2f m_SizeOfTexture;
		sf::Vector2f m_Size;
		sf::Texture m_Texture;
		bool m_Toggle;
	};

}

#endif BUTTON_H