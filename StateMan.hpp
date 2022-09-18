#pragma once
/**
* Menedzer stanu do zarzadzania stanami gry umieszczonymi w stosie
*/
#include <stack> //deklaracja stosu
#include <memory> //deklaracja pamieci aby mozna bylo uzywac wskaznikow
#include "State.hpp"

using namespace std;

namespace Engine
{
	class StateMan
	{
	private:
		/**
		* Unikalny wskaznik do aktualnego obiektu stanu
		*/
		stack<unique_ptr<State>> s_stateStack; 
		/**
		* Unikalny wskaznik do nowego obiektu stanu, ktory zostanie wprowadzony do 
		* stosu dopiero po zakonczeniu aktualnego 
		*/
		unique_ptr<State> s_newState;

		/**
		* Wartosc logiczna dla dodawania nowego stanu
		*/
		bool s_add; 
		/**
		* Wartosc logiczna dla zamiany stanu stosu
		*/
		bool s_replace; 
		/**
		* Wartosc logiczna dla usuwania stanu ze stosu
		*/
		bool s_remove; 

	public:
		StateMan();
		~StateMan();

		/**
		* Metoda dodawania nowego stanu do stosu
		* @param[in] toAdd unikalny wskaznik stanu dodawanego
		* @param[in] replace wartosc logiczna do kontrolowania czy stan ma zostac dodany 
		* jako nowy czy tez obecny ma zastac nadpisany 
		*/
		void Add(unique_ptr<State> toAdd, bool replace = false); 
		/**
		* Metoda usuwajaca obecny stan ze stosu
		*/
		void PopCurrent(); 
		/**
		* Metoda do zmiany stanu w stosie, w tej metodzie zostaje dokonana rzeczywista modyfikacja stosu
		*/
		void ProcessStateChange(); 
		/**
		* Metoda zwracajaca przez odniesienie wskaznik do biezacego stanu stosu
		*/
		unique_ptr<State>& GetCurrent(); 
	};
}



