#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Game.hpp"

using namespace std;

class PauseGame : public Engine::State
{
private:
	shared_ptr<Context> s_context;

	/// Napis pauza
	sf::Text s_pauseTitle;
public:
	PauseGame(std::shared_ptr<Context>& context);
	~PauseGame();

	void Init() override;
	void ProcessInput() override;
	void Update(sf::Time deltaTime) override;
	void Draw() override;
};

