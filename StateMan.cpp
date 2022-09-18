#include "StateMan.hpp"

using namespace std;

Engine::StateMan::StateMan():s_add(false), s_replace(false), s_remove(false)
{

}

Engine::StateMan::~StateMan()
{

}

void Engine::StateMan::Add(unique_ptr<State> toAdd, bool replace) 
{
	s_add = true;
	s_newState = move(toAdd); //zapisanie dodawanego stanu w nowym stanie

	s_replace = replace;
}
void Engine::StateMan::PopCurrent()
{
	s_remove = true;
}
void Engine::StateMan::ProcessStateChange()
{
	if (s_remove && (!s_stateStack.empty()))
	{
		s_stateStack.pop();//usuniecie elementu z wierzcholka stosu 

		if (!s_stateStack.empty())
		{
			s_stateStack.top()->Start();
		}

		s_remove = false;
	}

	if (s_add)
	{
		if (s_replace && (!s_stateStack.empty()))
		{
			s_stateStack.pop();//usuniecie elementu z wierzcholka stosu
			s_replace = false;
		}

		if (!s_stateStack.empty())
		{
			s_stateStack.top()->Pause();
		}

		s_stateStack.push(move(s_newState));
		s_stateStack.top()->Init(); //wywolanie inicjalizacji
		s_stateStack.top()->Start(); //wywolanie startu
		s_add = false;
	}
}
unique_ptr<Engine::State>& Engine::StateMan::GetCurrent()
{
	return s_stateStack.top(); ///zwracanie stanu ze szczytu stosu
}