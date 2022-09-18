#pragma once
/* Pierwszy stan gry czyli menu */
#include <memory>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Audio.hpp>

#include "State.hpp"
#include "Game.hpp"

using namespace std;

class MainMenu:public Engine::State
{
private:
	shared_ptr<Context> s_context;

	/// Tytul gry
	sf::Text s_gameTitle;
	/// Przycisk graj
	sf::Text s_playButton;
	/// Przycisk ranking
	sf::Text s_rankButton;
	/// Przycisk wyjscie
	sf::Text s_exitButton;
	/// Pierwsza linia instrukcji
	sf::Text s_gameInstruction;
	/// Druga linia instrukcji
	sf::Text s_gameInstruction2;
	/// Tlo menu
	sf::Sprite s_bgMenu;
	/// Muzyka w menu
	sf::Sound s_startGameSong;

	sf::Cursor cursor;

	/**
	* Wartosc logiczna do sprawdzenia czy kursor jest na obiekcie
	*/
	bool s_isPlayButtonSelected;
	/**
	* Wartosc logiczna do sprawdzenia czy kliknieto w obiekt, na ktorym jest kursor
	*/
	bool s_isPlayButtonPressed;

	/**
	* Wartosc logiczna do sprawdzenia czy kursor jest na obiekcie
	*/
	bool s_isRankButtonSelected;
	/**
	* Wartosc logiczna do sprawdzenia czy kliknieto w obiekt, na ktorym jest kursor
	*/
	bool s_isRankButtonPressed;

	/**
	* Wartosc logiczna do sprawdzenia czy kursor jest na obiekcie
	*/
	bool s_isExitButtonSelected;
	/**
	* Wartosc logiczna do sprawdzenia czy kliknieto w obiekt, na ktorym jest kursor
	*/
	bool s_isExitButtonPressed;

public:
	MainMenu(shared_ptr<Context>& context);
	~MainMenu();

	/*override - specyfikator do oznaczania funkcji w klasie jako takiej, ktora powinna przeciazyc wirtualna funkcje z klasy bazowej
			sprawdza czy nadpisujemy metode klasy bazowej i nie tworzymy nowej*/
	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;
};