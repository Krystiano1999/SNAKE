#pragma once
/* Klasa weza do ciala weza zostala uzyta lista nie tablica poniewaz tablica nie moze byc zwiekszana dynamicznie bez relokacji */
#include <list>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

using namespace std;
/*! \class Snake */
class Snake : public sf::Drawable
{
private:
	/// Cialo weza
	list<sf::Sprite> s_body;
	/// Glowa weza
	list<sf::Sprite>::iterator s_head;
	/// Ogon weza
	list<sf::Sprite>::iterator s_tail;
public:
	Snake();
	~Snake();
	
	/**
	* Metoda inicjujaca weza
	* @param[in] texture tekstura weza
	*/
	void Init(const sf::Texture& texture); // metoda inicjujaca weza
	/**
	* Metoda do kierowania weza
	* @param[in] direction kierunek weza
	*/
	void Move(const sf::Vector2f& direction); 
	/**
	* Metoda sluzaca do wykrycia kolizji z innym obiektem np. sciana lub jedzenie
	* @param[in] other sprite innego elementu niz waz
	*/
	bool IsOn(const sf::Sprite& other)const; 
	/**
	* Metoda sluzaca do wykrycia czy cos zanjduje sie pod ogonem weza
	* @param[in] other sprite innego elementu niz waz
	*/
	bool IsBottom(const sf::Sprite& other)const; 
	/**
	* Metoda do wzrostu weza
	* @param[in] direction kierunek weza
	*/
	void Grow(const sf::Vector2f& direction); // metoda 
	/**
	* Metoda do skracania weza
	* @param[in] direction kierunek weza
	*/
	void Decrease(const sf::Vector2f& direction);
	/**
	* Metoda do sprawdzenia czy waz uderzyl sam w siebie 
	* @param[in] 
	*/
	bool IsSelfIntersecting() const; 

	/**
	* Metoda rysujaca weza (wbudowana w SFML)
	* @param[in] target obiekt do rysowania
	* @param[in] states renderowanie stanow uzywanych do rysowania
	*/
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override; // metoda rysowania weza
	/**
	* Metoda do przechodzenia przez sciany
	* @param[in] direction kierunek weza
	*/
	void Portal(const sf::Vector2f& direction);
};

