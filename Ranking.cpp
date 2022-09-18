#include "Ranking.hpp"
#include "MainMenu.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Audio.hpp>

#include <time.h>
#include <iostream>

using namespace std;

Ranking::Ranking(shared_ptr<Context>& context) :s_context(context), s_isMenuButtonSelected(false), s_isMenuButtonPressed(false)
{
	srand(time(nullptr));
}

Ranking::~Ranking()
{

}


void Ranking::Init()
{
	s_context->s_assets->AddSample(HIGHSCORESOUND, "assets/sound/highscore.ogg");
	s_rankingSong.setBuffer(s_context->s_assets->GetSoundBuffer(HIGHSCORESOUND));
	s_rankingSong.play();

	s_context->s_assets->AddTexture(BG_HIGHSCORE, "assets/img/bg-rank.png");
	s_bgRank.setTexture(s_context->s_assets->GetTexture(BG_HIGHSCORE));

	//ustawienie tytulu gry
	s_rankTitle.setFont(s_context->s_assets->GetFont(MAIN_FONT));
	s_rankTitle.setString("Ranking punktow");
	s_rankTitle.setStyle(sf::Text::Bold);
	s_rankTitle.setLetterSpacing(1.5f);
	s_rankTitle.setCharacterSize(60);
	s_rankTitle.setOrigin(s_rankTitle.getLocalBounds().width / 2, s_rankTitle.getLocalBounds().height);
	s_rankTitle.setPosition(s_context->s_window->getSize().x / 2, 70.f);

	//ustawienie przycisku menu
	s_menuButton.setFont(s_context->s_assets->GetFont(MAIN_FONT));
	s_menuButton.setString("Menu");
	s_menuButton.setCharacterSize(36);
	s_menuButton.setOrigin(s_menuButton.getLocalBounds().width / 2, s_menuButton.getLocalBounds().height / 2);
	s_menuButton.setPosition(s_context->s_window->getSize().x / 2, (s_context->s_window->getSize().y / 4) * 3);

	//ustawienie instrukcji menu gry
	s_rankInstruction.setFont(s_context->s_assets->GetFont(MAIN_FONT));
	s_rankInstruction.setString("Aby zagrac wroc do menu");
	s_rankInstruction.setCharacterSize(13);
	s_rankInstruction.setOrigin(s_rankInstruction.getLocalBounds().width / 2, s_rankInstruction.getLocalBounds().height / 2);
	s_rankInstruction.setPosition(s_context->s_window->getSize().x / 2, s_context->s_window->getSize().y - 50.f);

	//Ranking
	s_text.setFont(s_context->s_assets->GetFont(MAIN_FONT));
	s_text.setString(s_context->s_scores->GetFromFile("highscores.txt", !1 ? 40 : -1));
	s_text.setCharacterSize(24);
	s_text.setOrigin(s_text.getLocalBounds().width / 2, s_text.getLocalBounds().height / 2);
	s_text.setPosition(s_context->s_window->getSize().x / 2, s_context->s_window->getSize().y/2 - 50.f);

}
void Ranking::ProcessInput()
{
	sf::Event event;
	while (s_context->s_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			s_context->s_window->close();
		else if (event.type == sf::Event::MouseMoved)
		{
			if (event.mouseMove.x > s_menuButton.getPosition().x - s_menuButton.getGlobalBounds().width / 2
				&& event.mouseMove.x < s_menuButton.getPosition().x + s_menuButton.getGlobalBounds().width / 2
				&& event.mouseMove.y>s_menuButton.getPosition().y - s_menuButton.getCharacterSize() / 2
				&& event.mouseMove.y < s_menuButton.getPosition().y + s_menuButton.getCharacterSize() / 2)
			{
				s_isMenuButtonSelected = true;
			}
			else
			{
				s_isMenuButtonSelected = false;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (s_isMenuButtonSelected)
				s_isMenuButtonPressed = true;
		}
	}
}
void Ranking::Update(sf::Time deltaTime)
{
	if (s_isMenuButtonSelected)
	{
		s_menuButton.setFillColor(sf::Color::Color(220, 170, 40));
	}
	else
	{
		s_menuButton.setFillColor(sf::Color::White);
	}

	if (s_isMenuButtonSelected)
	{
		if (cursor.loadFromSystem(sf::Cursor::Hand))
			s_context->s_window->setMouseCursor(cursor);
	}
	else
		if (cursor.loadFromSystem(sf::Cursor::Arrow))
			s_context->s_window->setMouseCursor(cursor);

	if (s_isMenuButtonPressed)
	{
		s_context->s_states->Add(make_unique<MainMenu>(s_context), true);
	}
}
void Ranking::Draw()
{
	s_context->s_window->clear();
	s_context->s_window->draw(s_bgRank);
	s_context->s_window->draw(s_rankTitle);
	s_context->s_window->draw(s_text);
	s_context->s_window->draw(s_menuButton);
	s_context->s_window->draw(s_rankInstruction);
	s_context->s_window->display();
}