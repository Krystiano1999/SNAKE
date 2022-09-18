#include "Game.hpp"
#include "MainMenu.hpp"

using namespace std;

Game::Game(): s_context(make_shared<Context>())
{
    /// dodanie ikony okna
    s_context->s_assets->AddImage(ICON, "assets/img/icon.png");
	/// stworzenie okna gry 
	s_context->s_window->create(sf::VideoMode(640, 672), "Snake v1.0 by Kasprzak, Jagiello, Mierzwa", sf::Style::Close);
    /// ustawienie ikony
    s_context->s_window->setIcon(32,32, (s_context->s_assets->GetImage(ICON)).getPixelsPtr());
    /// przekierowanie do menu
    s_context->s_states->Add(make_unique<MainMenu>(s_context));
}

Game::~Game()
{

}

void Game::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastFrame = sf::Time::Zero;

    while (s_context->s_window->isOpen())
    {
        timeSinceLastFrame += clock.restart();

        while (timeSinceLastFrame > TIME_PER_FRAME)
        {
            timeSinceLastFrame -= TIME_PER_FRAME;
            
            /// nastepowanie zmiany stanu w stosie przed nastepnym cyklem aktualizacji gry
            s_context->s_states->ProcessStateChange();  
            /// pozyskanie biezacego stanu z stateman i wywolanie danych wejsciowych
            s_context->s_states->GetCurrent()->ProcessInput(); 
            /// aktualizacja na biezacym stanie stosu 
            s_context->s_states->GetCurrent()->Update(TIME_PER_FRAME); 
            /// rysowanie tekstu i spritow w oknie renderowania
            s_context->s_states->GetCurrent()->Draw();
        }
    }
}