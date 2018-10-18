#ifndef APPLICATION_H
#define APPLICATION_H

#include "StateStack.h"
#include "ResourceIdentifiers.h"
#include "ResourceHolder.h"

#include <SFML\Graphics.hpp>
#include <SFML\System\NonCopyable.hpp>

class Application : public sf::NonCopyable
{
public:
	Application();
	~Application();
	void run();

private:
	//constants
	const sf::Time FrameTime = sf::seconds(1.0f / 60.0f);

	//variables
	sf::RenderWindow m_Window;
	sf::Text m_AppInfo;
	sf::View* m_MainView;
	sf::View* m_GuiView;

	int m_Fps;
	sf::Time m_UpdateTime;

	StateStack m_StateStack;

	//fucntions
	void handleInput();
	void update(sf::Time dt);
	void updateAppInfo(sf::Time dt);
	void render();


	void loadFonts();
	void registerStates();

	FontHolder m_Fonts;
};

#endif APPLICATION_H
