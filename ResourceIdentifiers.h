#ifndef RESOURCEIDENTIFIERS_H
#define RESOURCEIDENTIFIERS_H

#include <SFML\Graphics.hpp>

namespace Fonts {
	enum ID {
		Broshk,
	};
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Font, Fonts::ID>	FontHolder;
#endif RESOURCEIDENTIFIERS_H