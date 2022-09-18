#pragma once
/* Dodatkowy stan gry - ranking */
#include <memory>
#include <array>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio.hpp>

#include "State.hpp"
#include "Game.hpp"

using namespace std;

class Ranking :public Engine::State
{
private:
	shared_ptr<Context> s_context;

	/// Tytul rankingu
	sf::Text s_rankTitle;
	/// Przycisk menu
	sf::Text s_menuButton;
	/// Instrukcja w rankingu
	sf::Text s_rankInstruction;
	/// Tlo rankingu
	sf::Sprite s_bgRank;
	/// Dzwiek rankingu
	sf::Sound s_rankingSong;

	sf::Cursor cursor;

	/// Ranking
	sf::Text s_text;

	/**
	* Wartosc logiczna do sprawdzenia czy kursor jest na obiekcie
	*/
	bool s_isMenuButtonSelected;
	/**
	* Wartosc logiczna do sprawdzenia czy kliknieto w obiekt, na ktorym jest kursor
	*/
	bool s_isMenuButtonPressed;

public:
	Ranking(shared_ptr<Context>& context);
	~Ranking();

	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;
};