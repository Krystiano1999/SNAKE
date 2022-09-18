#pragma once
/* Drugi stan gry czyli rozgrywka */
#include <memory>
#include <array>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Game.hpp"
#include "Snake.hpp"

using namespace std;

class GamePlay : public Engine::State
{
private:
	shared_ptr<Context> s_context;

	/// Tlo planszy gry
	sf::Sprite s_bg;
	/// Pokarm - jablko
	sf::Sprite s_apple;
	/// Pokarm muchomor
	sf::Sprite s_mushroom;
	/// Pokarm Trujacy muchomor
	sf::Sprite s_badmushroom;
	/// Pokarm cukier
	sf::Sprite s_sugar;
	/// Dzwiek portalu
	sf::Sound s_portalSample;
	/// Dzwiek zjedzenia jablka
	sf::Sound s_appleSample;
	/// Dzwiek zjedzenia muchomora
	sf::Sound s_mushroomSample;
	/// Dzwiek zejdzenia trujacego muchomora
	sf::Sound s_badMushroomSample;
	/// Dzwiek zjedzenia cukru
	sf::Sound s_speedySample;
	/// Sciany 
	array<sf::Sprite, 4> s_walls;

	/// Waz 
	Snake s_snake;

	/// Wynik punktowy
	sf::Text s_scoreText;

	/// Kierunek Weza
	sf::Vector2f s_snakeDirection;
	/// Czas wykonania jednego cyklu aktualizacji gry
	sf::Time s_elapsedTime;

	/// Wartosc logiczna sluzaca do zapauzowania gry
	bool s_isPaused;

	/// Wartosc logiczna wyswietlajaca dodatkowe jedzenie
	bool s_displayEat;
	/// Wartosc logiczna do przyspieszenia weza
	bool s_fastAndFurious;
	/// licznik aktualizacji gry
	int s_counter;
	/// licznik aktualizacji gry gdy wyswietlane jest dodatkowe jedzenie
	int s_counterDisplay;

	/// Funkcja losujaca liczbe
	int RandNum(int s_num);
	/// Zmienna typu float do przyspieszania weza
	float s_speedy;

	/// licznik punktow
	int s_score;

	/// Wartosc logiczna do sprawdzania czy zostalo wpisane imie
	bool s_writeName;
	/// Wartosc logiczna do wyswietlania kursora
	bool show_cursor;
	/// Zmienna do wpisania przez uzytkownika swojego imienia
	string s_playerInput;
	/// Clae imie po zatwierdzeniu enterem
	string s_fullName;
	/// Wyswietlanie imienia
	sf::Text s_playerText;
	/// Prosba o wpisanie przez uzytkownika imienia 
	sf::Text s_wrotePlayerText;
	/// Instrukcja dla gracza
	sf::Text s_playerInstruction;
	 
	sf::Cursor cursor;
public:
	GamePlay(shared_ptr<Context>& context);
	~GamePlay();

	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override; 
	void Pause() override;
	void Start() override;
};

