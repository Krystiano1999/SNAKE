#pragma once
/**
* Silnik gry okreslajacy wszystkie stany wystepujace w grze,
* czyli dowolny etap lub fragment kodu, ktory moze przetwarzac dane wejsciowe,
* aby sie zaktualizowac lub zaladowac nowy stan.
*/
#include <SFML/System/Time.hpp>

using namespace std;

/**
* \namespace dokumentacja przestrzeni nazw Engine
*/
namespace Engine
{
	class State 
	{
	public:
		State() {};
		virtual ~State() {}; //destruktor do poprawnego niszczenia obiektow klasy

		/**
		* Czysta metoda wirtualna do wprowadzenia wszystkich poczatkowych ustawien 
		* takich jak ustawienie czcionki czy koloru tekstu.
		*/
		virtual void Init() = 0;
		/**
		* Czysta metoda wirtualna sluzaca do obslugi zdarzen myszki i klawiatury 
		*/
		virtual void ProcessInput() = 0;
		/**
		* Czysta metoda wirtualna, ktora reaguje na dane wejsciowe i ich aktualizowanie 
		* np. zmiana koloru tekstu czy pozycji obiektu
		* @param[in] deltaTime jest to czas, ktory uplynal od ostatniego wywolania metody Update
		*/
		virtual void Update(sf::Time deltaTime) = 0; 
		/**
		* Czysta metoda wirtualna do rysowania wszystkiego w oknie aplikacji,
		* czyli wszystkich spritow i tekstow
		*/
		virtual void Draw() = 0; 

		/**
		* Metoda wirtualna sluzaca do zapauzowania gry
		*/
		virtual void Pause() {}; //metoda do zapauzowania
		/**
		* Metoda wirtualna sluzaca do odpauzowania gry
		*/
		virtual void Start() {}; 
	};
}