#pragma once
/* Trzeci stan gry GAME OVER */
#include <memory>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "State.hpp"
#include "Game.hpp"

using namespace std;

class GameOver :public Engine::State
{
private:
	shared_ptr<Context> s_context;

	/// Tytul konca gry
	sf::Text s_gameOverTitle;
	/// Przycisk graj ponownie
	sf::Text s_retryButton;
	/// Przycisk Menu
	sf::Text s_menuButton;
	/// Przycisk wyjscie
	sf::Text s_exitButton;
	/// Tlo konca gry
	sf::Sprite s_bgGameOver;
	/// Dzwiek konca gry
	sf::Sound s_gameOverSong;

	sf::Cursor cursor;

	/**
	* Wartosc logiczna do sprawdzenia czy kursor jest na obiekcie
	*/
	bool s_isRetryButtonSelected;
	/**
	* Wartosc logiczna do sprawdzenia czy kliknieto w obiekt, na ktorym jest kursor
	*/
	bool s_isRetryButtonPressed;

	/**
	* Wartosc logiczna do sprawdzenia czy kursor jest na obiekcie
	*/
	bool s_isMenuButtonSelected;
	/**
	* Wartosc logiczna do sprawdzenia czy kliknieto w obiekt, na ktorym jest kursor
	*/
	bool s_isMenuButtonPressed;

	/**
	* Wartosc logiczna do sprawdzenia czy kursor jest na obiekcie
	*/
	bool s_isExitButtonSelected;
	/**
	* Wartosc logiczna do sprawdzenia czy kliknieto w obiekt, na ktorym jest kursor
	*/
	bool s_isExitButtonPressed;

public:
	GameOver(shared_ptr<Context>& context);
	~GameOver();

	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;
};