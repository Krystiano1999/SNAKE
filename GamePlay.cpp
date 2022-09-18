#include "GamePlay.hpp"
#include "GameOver.hpp"
#include "PauseGame.hpp"

#include <SFML/Window/Event.hpp>

#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

using namespace std;

GamePlay::GamePlay(shared_ptr<Context>& context) : s_context(context),
s_snakeDirection({ 32.f,0.f }),
s_elapsedTime(sf::Time::Zero),
s_displayEat(false),
s_fastAndFurious(false),
s_isPaused(false),
s_writeName(false),
show_cursor(true)
{
	srand(time(nullptr));
	s_speedy = 0.12;
	s_score = 0;
	s_counter = 0;
	s_counterDisplay = 0;
}

GamePlay::~GamePlay()
{

}

int GamePlay::RandNum(int s_num)
{
	int num = 0, x_width = 18, y_height = 15;
	if (s_num == 1) num = ((rand() % x_width) + 1) * 32;
	else if (s_num == 2) num = ((rand() % y_height) + 1) * 32;
	return num;
}

void GamePlay::Init()
{
	s_context->s_assets->AddSample(PORTALSAMPLE, "assets/sound/portal.ogg");
	s_portalSample.setBuffer(s_context->s_assets->GetSoundBuffer(PORTALSAMPLE));	

	s_context->s_assets->AddSample(APPLESAMPLE, "assets/sound/apple.ogg");
	s_appleSample.setBuffer(s_context->s_assets->GetSoundBuffer(APPLESAMPLE));

	s_context->s_assets->AddSample(MUSHROOMSAMPLE, "assets/sound/mushroom.ogg");
	s_mushroomSample.setBuffer(s_context->s_assets->GetSoundBuffer(MUSHROOMSAMPLE));

	s_context->s_assets->AddSample(BADMUSHROOMSAMPLE, "assets/sound/bad-mushroom.ogg");
	s_badMushroomSample.setBuffer(s_context->s_assets->GetSoundBuffer(BADMUSHROOMSAMPLE));

	s_context->s_assets->AddSample(SPEEDYSAMPLE, "assets/sound/speedy.ogg");
	s_speedySample.setBuffer(s_context->s_assets->GetSoundBuffer(SPEEDYSAMPLE));

	s_context->s_assets->AddTexture(BG, "assets/img/bg.jpg", true);
	s_context->s_assets->AddTexture(APPLE, "assets/img/apple.png");
	s_context->s_assets->AddTexture(WALL, "assets/img/wall.png", true);
	s_context->s_assets->AddTexture(WALL_BLOCK, "assets/img/wall-block.png", true);
	s_context->s_assets->AddTexture(SNAKE, "assets/img/skin.jpg");
	s_context->s_assets->AddTexture(MUSHROOM, "assets/img/mushroom.png");
	s_context->s_assets->AddTexture(BADMUSHROOM, "assets/img/bad-mushroom.png");
	s_context->s_assets->AddTexture(SUGAR, "assets/img/sugar.png");


	s_bg.setTexture(s_context->s_assets->GetTexture(BG));
	s_bg.setTextureRect(s_context->s_window->getViewport(s_context->s_window->getDefaultView()));

	for (auto& wall : s_walls)
	{
		wall.setTexture(s_context->s_assets->GetTexture(WALL));
	}
	s_walls[0].setTextureRect({ 0, 0, (int)s_context->s_window->getSize().x, 32 });
	s_walls[1].setTextureRect({ 0, 0, (int)s_context->s_window->getSize().x, 32 });
	s_walls[1].setPosition(0, s_context->s_window->getSize().y - 128);

	s_walls[2].setTextureRect({ 0, 0, 32, (int)s_context->s_window->getSize().y - 128 });
	s_walls[3].setTextureRect({ 0, 0, 32, (int)s_context->s_window->getSize().y - 128 });
	s_walls[3].setPosition(s_context->s_window->getSize().x - 32, 0);

	s_apple.setTexture(s_context->s_assets->GetTexture(APPLE));
	s_apple.setPosition(352, 352);

	s_mushroom.setTexture(s_context->s_assets->GetTexture(MUSHROOM));
	s_mushroom.setPosition(5000.f, 5000.f);

	s_badmushroom.setTexture(s_context->s_assets->GetTexture(BADMUSHROOM));
	s_badmushroom.setPosition(5000.f, 5000.f);

	s_sugar.setTexture(s_context->s_assets->GetTexture(SUGAR));
	s_sugar.setPosition(5000.f, 5000.f);

	s_snake.Init(s_context->s_assets->GetTexture(SNAKE));

	s_scoreText.setFont(s_context->s_assets->GetFont(MAIN_FONT));
	s_scoreText.setString("Wynik: " + to_string(s_score));
	s_scoreText.setCharacterSize(48);
	s_scoreText.setOrigin(s_scoreText.getLocalBounds().width / 2, s_scoreText.getLocalBounds().height / 2);
	s_scoreText.setPosition(s_context->s_window->getSize().x / 2, s_context->s_window->getSize().y - 50.f);

	s_wrotePlayerText.setFont(s_context->s_assets->GetFont(MAIN_FONT));
	s_wrotePlayerText.setString("Wpisz Swoje Imie");
	s_wrotePlayerText.setCharacterSize(28);
	s_wrotePlayerText.setOrigin(s_wrotePlayerText.getLocalBounds().width / 2, s_wrotePlayerText.getLocalBounds().height / 2);
	s_wrotePlayerText.setPosition(s_context->s_window->getSize().x / 2, s_context->s_window->getSize().y / 2 - 100.f);

	s_playerText.setFont(s_context->s_assets->GetFont(MAIN_FONT));
	s_playerText.setCharacterSize(48);
	s_playerText.setPosition(s_context->s_window->getSize().x * 2 / 5, s_context->s_window->getSize().y / 2);
	s_playerText.setFillColor(sf::Color::Green);

	//ustawienie instrukcji menu gry
	s_playerInstruction.setFont(s_context->s_assets->GetFont(MAIN_FONT));
	s_playerInstruction.setString("Wcisnij enter i zacznij gre. Powodzenia!");
	s_playerInstruction.setCharacterSize(13);
	s_playerInstruction.setOrigin(s_playerInstruction.getLocalBounds().width / 2, s_playerInstruction.getLocalBounds().height / 2);
	s_playerInstruction.setPosition(s_context->s_window->getSize().x / 2, s_context->s_window->getSize().y - 50.f);
}
void GamePlay::ProcessInput()
{
	sf::Event event;
	while (s_context->s_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			s_context->s_window->close();
		else if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode < 128)
			{
				s_playerInput += event.text.unicode;
			}
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			sf::Vector2f newDirection = s_snakeDirection;
			if (!s_writeName)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Return:
					s_writeName = true;
					break;
				case sf::Keyboard::BackSpace:
					if (!s_playerInput.empty())
						s_playerInput.pop_back();
						//s_playerInput = s_playerInput.substr(0, s_playerInput.length() - 1);
					break;
				default:
					break;
				}
			}
			else 
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
				case sf::Keyboard::W:
					newDirection = { 0.f,-32.f };
					break;
				case sf::Keyboard::Down:
				case sf::Keyboard::S:
					newDirection = { 0.f,32.f };
					break;
				case sf::Keyboard::Left:
				case sf::Keyboard::A:
					newDirection = { -32.f,0.f };
					break;
				case sf::Keyboard::Right:
				case sf::Keyboard::D:
					newDirection = { 32.f,0.f };
					break;
				case sf::Keyboard::Escape:
				case sf::Keyboard::P:
					s_context->s_states->Add(make_unique<PauseGame>(s_context));
					break;
				default:
					break;
				}
			}

			if (abs(s_snakeDirection.x) != abs(newDirection.x) || abs(s_snakeDirection.y) != abs(newDirection.y))
			{
				s_snakeDirection = newDirection;
			}
		}

	}
}

void GamePlay::Update(sf::Time deltaTime)
{
	if (!s_writeName)
	{
		if (s_elapsedTime.asSeconds() >= 0.3)
		{
			show_cursor = !show_cursor;
			s_elapsedTime = sf::Time::Zero;
		}
		s_playerText.setString(s_playerInput + (show_cursor ? '_' : ' '));
	}
	else
	{
		s_fullName = s_playerInput;

		s_counter++;
		s_elapsedTime += deltaTime;
		if (s_elapsedTime.asSeconds() > s_speedy) 
		{
			bool isOnWall = false;

			if (s_displayEat && s_counterDisplay + 357 < s_counter)
			{
				s_mushroom.setPosition(5000.f, 5000.f);
				s_badmushroom.setPosition(5000.f, 5000.f);
				s_sugar.setPosition(5000.f, 5000.f);
				s_counterDisplay = 0;
				s_displayEat = false;
			}

			if (s_fastAndFurious && s_counterDisplay + 250 < s_counter)
			{
				s_speedy = 0.12;
				s_counterDisplay = 0;
				s_fastAndFurious = false;
			}

			for (auto& wall : s_walls)
			{
				if (s_counter >= 3500)
				{
					wall.setTexture(s_context->s_assets->GetTexture(WALL_BLOCK));
				}
				if (s_snake.IsOn(wall))
				{
					if (s_counter < 3500)
					{
						s_snake.Portal(s_snakeDirection);
						s_portalSample.play();
					}
					else
					{
						s_context->s_states->Add(make_unique<GameOver>(s_context), true);
						break;
					}
				}
			}

			if (s_snake.IsOn(s_apple))
			{
				s_snake.Grow(s_snakeDirection);

				s_apple.setPosition(RandNum(1), RandNum(2));
				s_score += 5;
				s_scoreText.setString("Wynik: " + to_string(s_score));
				s_scoreText.setFillColor(sf::Color::Green);

				s_appleSample.play();
			}
			else
			{
				s_snake.Move(s_snakeDirection);
			}

			if (s_snake.IsBottom(s_apple))
			{
				s_apple.setPosition(RandNum(1), RandNum(2));
			}

			if (s_counter % 115 == 0 && s_score != 0)
			{
				s_mushroom.setPosition(RandNum(1), RandNum(2));
				s_displayEat = true;
				s_counterDisplay = s_counter;
			}

			if (s_snake.IsOn(s_mushroom))
			{
				s_snake.Grow(s_snakeDirection);
				s_mushroom.setPosition(5000.f, 5000.f);
				s_score += 10;
				s_scoreText.setString("Wynik: " + to_string(s_score));
				s_scoreText.setFillColor(sf::Color::Green);
				s_mushroomSample.play();
			}

			if (s_counter % 145 == 0 && s_score != 0)
			{
				s_badmushroom.setPosition(RandNum(1), RandNum(2));
				s_displayEat = true;
				s_counterDisplay = s_counter;
			}

			if (s_snake.IsOn(s_badmushroom))
			{
				s_snake.Grow(s_snakeDirection);
				s_badmushroom.setPosition(5000.f, 5000.f);
				s_score -= 5;
				s_scoreText.setFillColor(sf::Color::Red);
				s_scoreText.setString("Wynik: " + to_string(s_score));
				s_badMushroomSample.play();
			}

			if (s_counter % 175 == 0 && s_score != 0)
			{
				s_sugar.setPosition(RandNum(1), RandNum(2));
				s_displayEat = true;
				s_counterDisplay = s_counter;
			}

			if (s_snake.IsOn(s_sugar))
			{
				s_speedy = 0.07;
				s_fastAndFurious = true;
				s_sugar.setPosition(5000.f, 5000.f);
				s_scoreText.setString("Wynik: " + to_string(s_score));
				s_scoreText.setFillColor(sf::Color::White);
				s_speedySample.play();
			}

			if (s_snake.IsSelfIntersecting())
			{
				s_context->s_scores->SetScore(s_score, s_fullName);
				s_context->s_states->Add(make_unique<GameOver>(s_context), true);
			}

			s_elapsedTime = sf::Time::Zero;
		}
	}
}
void GamePlay::Draw()
{
	if (!s_writeName)
	{
		s_context->s_window->clear();
		s_context->s_window->draw(s_wrotePlayerText);
		s_context->s_window->draw(s_playerText);
		s_context->s_window->draw(s_playerInstruction);
		s_context->s_window->display();
	}
	else
	{
		s_context->s_window->clear();
		s_context->s_window->draw(s_bg);
		s_context->s_window->draw(s_apple);
		s_context->s_window->draw(s_mushroom);
		s_context->s_window->draw(s_badmushroom);
		s_context->s_window->draw(s_sugar);
		s_context->s_window->draw(s_snake);
		for (auto& wall : s_walls)
		{
			s_context->s_window->draw(wall);
		}
		s_context->s_window->draw(s_scoreText);
		s_context->s_window->display();
	}
}

void GamePlay::Pause()
{
	s_isPaused = true;
}
void GamePlay::Start()
{
	s_isPaused = false;
}