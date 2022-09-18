#include "PauseGame.hpp"

#include <SFML/Window/Event.hpp>

using namespace std; 

PauseGame::PauseGame(shared_ptr<Context>& context) : s_context(context)
{

}

PauseGame::~PauseGame()
{

}

void PauseGame::Init()
{
	//ustawienie napisu pauza
	s_pauseTitle.setFont(s_context->s_assets->GetFont(MAIN_FONT));
	s_pauseTitle.setString("Pauza");
	s_pauseTitle.setCharacterSize(30);
	s_pauseTitle.setOrigin(s_pauseTitle.getLocalBounds().width / 2, s_pauseTitle.getLocalBounds().height / 2);
	s_pauseTitle.setPosition(s_context->s_window->getSize().x / 2, s_context->s_window->getSize().y / 2);

}
void PauseGame::ProcessInput()
{
	sf::Event event;
	while (s_context->s_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			s_context->s_window->close();
		else if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
			case sf::Keyboard::P:
			{
				s_context->s_states->PopCurrent();
				break;
			}
			default:
			{
				break;
			}
			}
		}
	}
}
void PauseGame::Update(sf::Time deltaTime)
{
	
}
void PauseGame::Draw()
{
	s_context->s_window->draw(s_pauseTitle);
	s_context->s_window->display();
}