#include "AssetMan.hpp"

using namespace std;

Engine::AssetMan::AssetMan()
{

}

Engine::AssetMan::~AssetMan()
{

}

void Engine::AssetMan::AddTexture(int id, const string& filePath, bool wantRepeated)
{
	auto texture = make_unique<sf::Texture>(); //tworzenie nowej tekstury

	if (texture->loadFromFile(filePath))
	{
		texture->setRepeated(wantRepeated);
		s_textures[id] = move(texture); ///zaladowanie tekstury do mapy tekstur
	}
}
void Engine::AssetMan::AddFont(int id, const string& filePath)
{
	auto font = make_unique<sf::Font>(); //tworzenie nowej czcionki

	if (font->loadFromFile(filePath))
	{
		s_fonts[id] = move(font); ///zaladowanie czcionki do mapy czcionek
	}
}

void Engine::AssetMan::AddSample(int id, const string& filePath)
{
	auto sample = make_unique<sf::SoundBuffer>(); //tworzenie nowego dzwieku

	if (sample -> loadFromFile(filePath))
	{
		s_soundBuffer[id] = move(sample); ///zaladowanie dzwieku do mapy dzwiekow
	}
}

void Engine::AssetMan::AddImage(int id, const string& filePath)
{
	auto img = make_unique<sf::Image>(); //tworzenie nowego obrazu

	if (img-> loadFromFile(filePath))
	{
		s_image[id] = move(img); ///zaladowanie obrazu do mapy obrazow
	}
}

const sf::Texture& Engine::AssetMan::GetTexture(int id) const
{
	return *(s_textures.at(id).get()); ///zwracanie wskaznika tekstury
}

const sf::Font& Engine::AssetMan::GetFont(int id) const
{
	return *(s_fonts.at(id).get()); ///zwracanie wskaznika czcionki
}

const sf::SoundBuffer& Engine::AssetMan::GetSoundBuffer(int id) const
{
	return *(s_soundBuffer.at(id).get()); ///zwracanie wskaznika dzwieku
}

const sf::Image& Engine::AssetMan::GetImage(int id) const
{
	return *(s_image.at(id).get()); ///zwracanie wskaznika obrazu
}