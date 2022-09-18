#pragma once
/**
* Menedzer punktow do zapisywania rankingu do pliku teksowego, oraz odczytu z pliku tekstowego
*/
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>

using namespace std;

namespace Engine
{
	class ScoreMan 
	{
	public:
		/**
		* Struktura do zapisywania i odczytu punktow, zawierajaca imie i punkty gracza 
		*/
		struct Score {
			string name;
			int score;
		};

		/**
		* Metoda zapisujaca wynik do rankingu
		* @param[in] score ilosc punktow
		* @param[in] s_name imie gracza
		*/
		void SetScore(int score, string s_name);

		/**
		* Funkcja odczytujaca ranking z pliku
		* @param[in] filename nazwa pliku
		* @param[in] separator separator 
		*/
		string GetFromFile(string filename, int separator);
	};
}