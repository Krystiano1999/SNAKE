#include "MainMenu.hpp"
#include "GamePlay.hpp"
#include "Ranking.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Cursor.hpp>

#include <iostream>
#include <time.h>

using namespace std;

MainMenu::MainMenu(shared_ptr<Context>& context) :s_context(context), s_isPlayButtonSelected(false), s_isPlayButtonPressed(false), s_isRankButtonSelected(false), s_isRankButtonPressed(false), s_isExitButtonSelected(false), s_isExitButtonPressed(false)
{
	srand(time(nullptr));
}

MainMenu::~MainMenu()
{

}


void MainMenu::Init()
{
	int s_iPhoto = 0;

	s_iPhoto = (rand() % 3) + 1;
	
	s_context->s_assets->AddSample(STARTGAMESOUND, "assets/sound/startgame.ogg");
	s_startGameSong.setBuffer(s_context->s_assets->GetSoundBuffer(STARTGAMESOUND));
	s_startGameSong.setLoop(true);
	s_startGameSong.play();

	s_context->s_assets->AddFont(MAIN_FONT,"assets/font/arial.ttf");
	s_context->s_assets->AddTexture(BGMENU, "assets/img/snake"+ to_string(s_iPhoto)+".jpg");


	s_bgMenu.setTexture(s_context->s_assets->GetTexture(BGMENU));

	//ustawienie tytulu gry
	s_gameTitle.setFont(s_context->s_assets->GetFont(MAIN_FONT));
	s_gameTitle.setString("SNAKE");
	s_gameTitle.setStyle(sf::Text::Bold);
	s_gameTitle.setLetterSpacing(1.5f);
	s_gameTitle.setCharacterSize(60);
	s_gameTitle.setOrigin(s_gameTitle.getLocalBounds().width / 2, s_gameTitle.getLocalBounds().height);
	s_gameTitle.setPosition((s_context->s_window->getSize().x / 4)*3, 70.f);

	//ustawienie przycisku graj
	s_playButton.setFont(s_context->s_assets->GetFont(MAIN_FONT));
	s_playButton.setString("Graj");
	s_playButton.setCharacterSize(32);
	s_playButton.setOrigin(s_playButton.getLocalBounds().width / 2, s_playButton.getLocalBounds().height / 2);
	s_playButton.setPosition((s_context->s_window->getSize().x / 4) * 3, (s_context->s_window->getSize().y / 4)*3 - 75.f);

	//ustawienie przycisku ranking
	s_rankButton.setFont(s_context->s_assets->GetFont(MAIN_FONT));
	s_rankButton.setString("Ranking");
	s_rankButton.setCharacterSize(32);
	s_rankButton.setOrigin(s_rankButton.getLocalBounds().width / 2, s_rankButton.getLocalBounds().height / 2);
	s_rankButton.setPosition((s_context->s_window->getSize().x / 4) * 3, (s_context->s_window->getSize().y / 4)*3 - 25.f);

	//ustawienie przycisku wyjdz
	s_exitButton.setFont(s_context->s_assets->GetFont(MAIN_FONT));
	s_exitButton.setString("Wyjdz");
	s_exitButton.setCharacterSize(32);
	s_exitButton.setOrigin(s_exitButton.getLocalBounds().width / 2, s_exitButton.getLocalBounds().height / 2);
	s_exitButton.setPosition((s_context->s_window->getSize().x / 4) * 3, (s_context->s_window->getSize().y / 4)*3 + 25.f);

	//ustawienie instrukcji menu gry
	s_gameInstruction.setFont(s_context->s_assets->GetFont(MAIN_FONT));
	s_gameInstruction.setString("Witamy w grze");
	s_gameInstruction.setCharacterSize(13);
	s_gameInstruction.setOrigin(s_gameInstruction.getLocalBounds().width / 2, s_gameInstruction.getLocalBounds().height / 2);
	s_gameInstruction.setPosition(s_context->s_window->getSize().x / 2, s_context->s_window->getSize().y - 50.f);
	//ustawienie instrukcji sterowania wezem
	s_gameInstruction2.setFont(s_context->s_assets->GetFont(MAIN_FONT));
	s_gameInstruction2.setString("Sterowanie odbywa sie za pomoca strzalek lub klawiszy WASD");
	s_gameInstruction2.setCharacterSize(13);
	s_gameInstruction2.setOrigin(s_gameInstruction2.getLocalBounds().width / 2, s_gameInstruction2.getLocalBounds().height / 2);
	s_gameInstruction2.setPosition(s_context->s_window->getSize().x / 2, s_context->s_window->getSize().y - 25.f);
}
void MainMenu::ProcessInput()
{
	sf::Event event;
	while (s_context->s_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			s_context->s_window->close();
		else if (event.type == sf::Event::MouseMoved)
		{
			if (event.mouseMove.x > s_playButton.getPosition().x - s_playButton.getGlobalBounds().width / 2
				&& event.mouseMove.x < s_playButton.getPosition().x + s_playButton.getGlobalBounds().width / 2
				&& event.mouseMove.y>s_playButton.getPosition().y - s_playButton.getCharacterSize() / 2
				&& event.mouseMove.y < s_playButton.getPosition().y + s_playButton.getCharacterSize() / 2)
			{
				s_isPlayButtonSelected = true;
				s_isRankButtonSelected = false;
				s_isExitButtonSelected = false;
			}else if (event.mouseMove.x > s_rankButton.getPosition().x - s_rankButton.getGlobalBounds().width / 2
				&& event.mouseMove.x < s_rankButton.getPosition().x + s_rankButton.getGlobalBounds().width / 2
				&& event.mouseMove.y>s_rankButton.getPosition().y - s_rankButton.getCharacterSize() / 2
				&& event.mouseMove.y < s_rankButton.getPosition().y + s_rankButton.getCharacterSize() / 2)
			{
				s_isPlayButtonSelected = false;
				s_isRankButtonSelected = true;
				s_isExitButtonSelected = false;
			}else if (event.mouseMove.x > s_exitButton.getPosition().x - s_exitButton.getGlobalBounds().width / 2
				&& event.mouseMove.x < s_exitButton.getPosition().x + s_exitButton.getGlobalBounds().width / 2
				&& event.mouseMove.y>s_exitButton.getPosition().y - s_exitButton.getCharacterSize() / 2
				&& event.mouseMove.y < s_exitButton.getPosition().y + s_exitButton.getCharacterSize() / 2)
			{
				s_isPlayButtonSelected = false;
				s_isRankButtonSelected = false;
				s_isExitButtonSelected = true;
			}
			else
			{
				s_isPlayButtonSelected = false;
				s_isRankButtonSelected = false;
				s_isExitButtonSelected = false;
			}
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (s_isPlayButtonSelected)
				s_isPlayButtonPressed = true;
			else if (s_isRankButtonSelected)
				s_isRankButtonPressed = true;
			else if (s_isExitButtonSelected)
				s_isExitButtonPressed = true;
		}
	}
}
void MainMenu::Update(sf::Time deltaTime)
{
	if (s_isPlayButtonSelected)
	{
		s_playButton.setFillColor(sf::Color::Color(220,170,40));
		s_rankButton.setFillColor(sf::Color::White);
		s_exitButton.setFillColor(sf::Color::White);
	}
	else if(s_isRankButtonSelected)
	{
		s_playButton.setFillColor(sf::Color::White);
		s_rankButton.setFillColor(sf::Color::Color(220, 170, 40));
		s_exitButton.setFillColor(sf::Color::White);
	}
	else if (s_isExitButtonSelected)
	{
		s_playButton.setFillColor(sf::Color::White);
		s_rankButton.setFillColor(sf::Color::White);
		s_exitButton.setFillColor(sf::Color::Color(220, 170, 40));
	}
	else
	{
		s_playButton.setFillColor(sf::Color::White);
		s_rankButton.setFillColor(sf::Color::White);
		s_exitButton.setFillColor(sf::Color::White);
	}

	if (s_isPlayButtonSelected || s_isRankButtonSelected || s_isExitButtonSelected)
	{
		if (cursor.loadFromSystem(sf::Cursor::Hand))
			s_context->s_window->setMouseCursor(cursor);
	}
	else
		if (cursor.loadFromSystem(sf::Cursor::Arrow))
			s_context->s_window->setMouseCursor(cursor);

	if (s_isPlayButtonPressed)
	{
		s_context->s_states->Add(make_unique<GamePlay>(s_context), true);
	}
	else if (s_isRankButtonPressed)
	{
		s_context->s_states->Add(make_unique<Ranking>(s_context), true);
	}
	else if (s_isExitButtonPressed)
	{
		s_context->s_window->close();
	}
}
void MainMenu::Draw()
{
	s_context->s_window->clear();
	s_context->s_window->draw(s_bgMenu);
	s_context->s_window->draw(s_gameTitle);
	s_context->s_window->draw(s_playButton);
	s_context->s_window->draw(s_rankButton);
	s_context->s_window->draw(s_exitButton);
	s_context->s_window->draw(s_gameInstruction);
	s_context->s_window->draw(s_gameInstruction2);
	s_context->s_window->display();
}