#include "GameOver.hpp"
#include "GamePlay.hpp"
#include "MainMenu.hpp"

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

#include <SFML/Window/Event.hpp>

using namespace std;

GameOver::GameOver(shared_ptr<Context>& context) : s_context(context), s_isRetryButtonSelected(true), s_isRetryButtonPressed(false), s_isMenuButtonSelected(false), s_isMenuButtonPressed(false), s_isExitButtonSelected(false), s_isExitButtonPressed(false)
{

}

GameOver::~GameOver()
{

}


void GameOver::Init()
{
	s_context->s_assets->AddTexture(BGGAMEOVER, "assets/img/snake4.jpg");
	s_bgGameOver.setTexture(s_context->s_assets->GetTexture(BGGAMEOVER));

	//ustawienie tytulu gry
	s_gameOverTitle.setFont(s_context->s_assets->GetFont(MAIN_FONT));
	s_gameOverTitle.setString("GAME OVER!");
	s_gameOverTitle.setStyle(sf::Text::Bold);
	s_gameOverTitle.setLetterSpacing(2.f);
	s_gameOverTitle.setCharacterSize(64);
	s_gameOverTitle.setOrigin(s_gameOverTitle.getLocalBounds().width / 2, s_gameOverTitle.getLocalBounds().height / 2);
	s_gameOverTitle.setPosition(s_context->s_window->getSize().x / 2, 100.f);

	//ustawienie przycisku graj
	s_retryButton.setFont(s_context->s_assets->GetFont(MAIN_FONT));
	s_retryButton.setString("Graj ponownie");
	s_retryButton.setCharacterSize(32);
	s_retryButton.setOrigin(s_retryButton.getLocalBounds().width / 2, s_retryButton.getLocalBounds().height / 2);
	s_retryButton.setPosition((s_context->s_window->getSize().x / 2), (s_context->s_window->getSize().y / 4) * 3 - 75.f);

	//ustawienie przycisku menu
	s_menuButton.setFont(s_context->s_assets->GetFont(MAIN_FONT));
	s_menuButton.setString("Menu");
	s_menuButton.setCharacterSize(32);
	s_menuButton.setOrigin(s_menuButton.getLocalBounds().width / 2, s_menuButton.getLocalBounds().height / 2);
	s_menuButton.setPosition((s_context->s_window->getSize().x / 2), (s_context->s_window->getSize().y / 4) * 3 - 25.f);

	//ustawienie przycisku wyjdz
	s_exitButton.setFont(s_context->s_assets->GetFont(MAIN_FONT));
	s_exitButton.setString("Wyjdz");
	s_exitButton.setCharacterSize(32);
	s_exitButton.setOrigin(s_exitButton.getLocalBounds().width / 2, s_exitButton.getLocalBounds().height / 2);
	s_exitButton.setPosition((s_context->s_window->getSize().x / 2), (s_context->s_window->getSize().y / 4) * 3 + 25.f);

	s_context->s_assets->AddSample(GAMEOVERSONG, "assets/sound/gameover.ogg");
	s_gameOverSong.setBuffer(s_context->s_assets->GetSoundBuffer(GAMEOVERSONG));
	s_gameOverSong.play();


}
void GameOver::ProcessInput()
{
	sf::Event event;
	while (s_context->s_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			s_context->s_window->close();
		else if (event.type == sf::Event::MouseMoved)
		{
			if (event.mouseMove.x > s_retryButton.getPosition().x - s_retryButton.getGlobalBounds().width / 2
				&& event.mouseMove.x < s_retryButton.getPosition().x + s_retryButton.getGlobalBounds().width / 2
				&& event.mouseMove.y>s_retryButton.getPosition().y - s_retryButton.getCharacterSize() / 2
				&& event.mouseMove.y < s_retryButton.getPosition().y + s_retryButton.getCharacterSize() / 2)
			{
				s_isRetryButtonSelected = true;
				s_isMenuButtonSelected = false;
				s_isExitButtonSelected = false;
			}
			else if(event.mouseMove.x > s_menuButton.getPosition().x - s_menuButton.getGlobalBounds().width / 2
				&& event.mouseMove.x < s_menuButton.getPosition().x + s_menuButton.getGlobalBounds().width / 2
				&& event.mouseMove.y>s_menuButton.getPosition().y - s_menuButton.getCharacterSize() / 2
				&& event.mouseMove.y < s_menuButton.getPosition().y + s_menuButton.getCharacterSize() / 2)
			{
				s_isRetryButtonSelected = false;
				s_isMenuButtonSelected = true;
				s_isExitButtonSelected = false;
			}
			else if (event.mouseMove.x > s_exitButton.getPosition().x - s_exitButton.getGlobalBounds().width / 2
				&& event.mouseMove.x < s_exitButton.getPosition().x + s_exitButton.getGlobalBounds().width / 2
				&& event.mouseMove.y>s_exitButton.getPosition().y - s_exitButton.getCharacterSize() / 2
				&& event.mouseMove.y < s_exitButton.getPosition().y + s_exitButton.getCharacterSize() / 2)
			{
				s_isRetryButtonSelected = false;
				s_isMenuButtonSelected = false;
				s_isExitButtonSelected = true;
			}
			else
			{
				s_isRetryButtonSelected = false;
				s_isMenuButtonSelected = false;
				s_isExitButtonSelected = false;
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (s_isRetryButtonSelected)
				s_isRetryButtonPressed = true;
			else if (s_isMenuButtonSelected)
				s_isMenuButtonPressed = true;
			else if (s_isExitButtonSelected)
				s_isExitButtonPressed = true;
		}
	}
}
void GameOver::Update(sf::Time deltaTime)
{
	if (s_isRetryButtonSelected)
	{
		s_retryButton.setFillColor(sf::Color::Color(220, 170, 40));
		s_menuButton.setFillColor(sf::Color::White);
		s_exitButton.setFillColor(sf::Color::White);
	}
	else if (s_isMenuButtonSelected)
	{
		s_retryButton.setFillColor(sf::Color::White);
		s_menuButton.setFillColor(sf::Color::Color(220, 170, 40));
		s_exitButton.setFillColor(sf::Color::White);
	}
	else if(s_isExitButtonSelected)
	{
		s_retryButton.setFillColor(sf::Color::White);
		s_menuButton.setFillColor(sf::Color::White);
		s_exitButton.setFillColor(sf::Color::Color(220, 170, 40));
	}
	else
	{
		s_retryButton.setFillColor(sf::Color::White);
		s_menuButton.setFillColor(sf::Color::White);
		s_exitButton.setFillColor(sf::Color::White);
	}

	if (s_isRetryButtonSelected || s_isExitButtonSelected || s_isMenuButtonSelected)
	{
		if (cursor.loadFromSystem(sf::Cursor::Hand))
			s_context->s_window->setMouseCursor(cursor);
	}
	else
		if (cursor.loadFromSystem(sf::Cursor::Arrow))
			s_context->s_window->setMouseCursor(cursor);

	if (s_isRetryButtonPressed)
	{
		s_context->s_states->Add(make_unique<GamePlay>(s_context), true);
	}
	else if (s_isMenuButtonPressed)
	{
		s_context->s_states->Add(make_unique<MainMenu>(s_context), true);
	}
	else if (s_isExitButtonPressed)
	{
		s_context->s_window->close();
	}
}
void GameOver::Draw()
{
	s_context->s_window->clear(sf::Color::Black);
	s_context->s_window->draw(s_bgGameOver);
	s_context->s_window->draw(s_gameOverTitle);
	s_context->s_window->draw(s_retryButton);
	s_context->s_window->draw(s_menuButton);
	s_context->s_window->draw(s_exitButton);
	s_context->s_window->display();
}