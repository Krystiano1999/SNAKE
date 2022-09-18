#pragma once

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

#include "AssetMan.hpp"
#include "StateMan.hpp"
#include "ScoreMan.hpp"

using namespace std;
//! Enum.
/*! Wyliczenie listy slownych wartosci do podpiecia czcionek, tekstur oraz sampli */
enum AssetID
{
	/// Czcionka
	MAIN_FONT = 0,
	/// Tlo gry
	BG,
	/// Pokarm - jablko
	APPLE,
	/// Pokarm muchomor
	MUSHROOM,
	/// Pokarm - trujacy muchomor
	BADMUSHROOM,
	/// Pokarm cukier
	SUGAR,
	/// Sciana
	WALL,
	/// Scina nie do przejcia
	WALL_BLOCK,
	/// Tlo menu
	BGMENU,
	/// Tlo konca gry
	BGGAMEOVER,
	/// Waz
	SNAKE,
	/// Dzwiek menu
	STARTGAMESOUND,
	/// Dzwiek konca gry
	GAMEOVERSONG,
	/// Dzwiek przejscia przez portal
	PORTALSAMPLE,
	/// Dzwiek zjedzenia jablka
	APPLESAMPLE,
	/// Dzwiek zjedzenia muchomora
	MUSHROOMSAMPLE,
	/// Dzwiek zjedzenia zleho muchomora
	BADMUSHROOMSAMPLE,
	/// Dzwiek przyspieszenia
	SPEEDYSAMPLE,
	/// Ikona gry
	ICON,
	/// Dzwiek rankingu
	HIGHSCORESOUND,
	/// Tlo rankingu
	BG_HIGHSCORE
};

struct Context
{
	/// wskaznik na menedzer zasobow(tekstur i czcionek)
	unique_ptr<Engine::AssetMan> s_assets; 
	/// wskaznik na menedzer stanu
	unique_ptr<Engine::StateMan> s_states;
	/// wskaznik na menedzer punktow
	unique_ptr<Engine::ScoreMan> s_scores; 
	/// wskaznik do wyrenderowania okna
	unique_ptr<sf::RenderWindow> s_window; 

	Context()
	{
		s_assets = make_unique<Engine::AssetMan>();
		s_states = make_unique<Engine::StateMan>();
		s_scores = make_unique<Engine::ScoreMan>();
		s_window = make_unique<sf::RenderWindow>();
	}
};

class Game
{
private:
	sf::Image s_icon;
	///wskaznik do struktury context
	shared_ptr<Context> s_context; 
	const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f); //ustawienie klatek na sekunde
public:
	Game();
	~Game();

	/**
	* Metoda uruchamiajaca gre
	*/
	void Run();
};