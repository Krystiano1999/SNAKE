#pragma once
/**
* Menedzer zasobow do przechowywania oraz zarzadzania wszystkimi uzywanymi teksturami, czcionkami oraz dzwiekami
*/
#include <map>
#include <memory>
#include <string>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio.hpp>

using namespace std;

/*! \namespace 
*	Przestrzen nazw okreslajaca silnik gry
*/
namespace Engine
{
	class AssetMan
	{
	private:
		map<int, unique_ptr<sf::Texture>>s_textures;/// kontener tekstur
		map<int, unique_ptr<sf::Font>>s_fonts;/// kontener czcionek
		map<int, unique_ptr<sf::SoundBuffer >>s_soundBuffer;/// kontener dzwiekow
		map<int, unique_ptr<sf::Image >>s_image;/// kontener obrazow
	public:
		AssetMan();
		~AssetMan();

		/**
		* Metoda dodajaca teksture
		* @param[in] id numer identyfikacyjny tekstury
		* @param[in] filePath sciezka do tekstury
		* @param[in] wantRepeated wartosc logiczna, od ktorej zalezy czy tekstura ma sie powielac
		*/
		void AddTexture(int id, const string& filePath, bool wantRepeated = false); 
		/**
		* Metoda dodajaca czcionke
		* @param[in] id numer identyfikacyjny czcionki
		* @param[in] filePath sciezka do czcionki
		*/
		void AddFont(int id, const string &filePath);
		/**
		* Metoda dodajaca dzwiek
		* @param[in] id numer identyfikacyjny dzwieku
		* @param[in] filePath sciezka do dzwieku
		*/
		void AddSample(int id, const string& filePath); 
		/**
		* Metoda dodajaca ikone
		* @param[in] id numer identyfikacyjny ikony
		* @param[in] filePath sciezka do ikony
		*/
		void AddImage(int id, const string& filePath); 

		/**
		* Pobranie tekstury z mapy tekstur
		* @param[in] id identyfikator tekstury
		*/
		const sf::Texture& GetTexture(int id) const; 
		/**
		* Pobranie czcionki z mapy czcionek
		* @param[in] id identyfikator czcionki
		*/
		const sf::Font& GetFont(int id) const; 
		/**
		* Pobranie dzwieku z mapy dzwiekow
		* @param[in] id identyfikator dzwieku
		*/
		const sf::SoundBuffer& GetSoundBuffer(int id) const; 
		/**
		* Pobranie obrazu z mapy obrazow
		* @param[in] id identyfikator obrazu
		*/
		const sf::Image& GetImage(int id) const;
	};
}
