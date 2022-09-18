#include "Snake.hpp"
#include <iostream>

using namespace std;

Snake::Snake() : s_body(list<sf::Sprite>(4))
{
	s_head = --s_body.end(); //ustawienie glowy weza na ostatni element ciala w liscie
	s_tail = s_body.begin(); //ustawienie ogona od poczatku listy
}

Snake::~Snake()
{

}

// ustawienie poczatkowe weza w gornym lewym rogu okna 
void Snake::Init(const sf::Texture& texture)
{
	float x = 32.f;
	for (auto& piece : s_body)
	{
		piece.setTexture(texture);
		piece.setPosition({ x, 32.f });
		x += 32.f;
	}
}

void Snake::Move(const sf::Vector2f& direction)
{
	s_tail->setPosition(s_head->getPosition() + direction);
	s_head = s_tail;
	++s_tail;
	if (s_tail == s_body.end())
	{
		s_tail = s_body.begin();
	}
}

void Snake::Portal(const sf::Vector2f& direction)
{
	sf::Vector2f s_pos = s_head->getPosition();
	float x_pos = s_pos.x;
	float y_pos = s_pos.y;
	if (x_pos < 32) 
	{
		s_head->setPosition(576, s_pos.y);
	}
	else if (x_pos > 576)
	{
		s_head->setPosition(32, s_pos.y);
	}
	if (y_pos < 32)
	{
		s_head->setPosition(s_pos.x, 512);
	}
	else if (y_pos > 512)
	{
		s_head->setPosition(s_pos.x, 32);
	}
}

bool Snake::IsOn(const sf::Sprite& other)const
{
	return other.getGlobalBounds().intersects(s_head->getGlobalBounds());
}

bool Snake::IsBottom(const sf::Sprite& other)const
{
	return other.getGlobalBounds().intersects(s_tail->getGlobalBounds());
}

void Snake::Grow(const sf::Vector2f& direction)
{
	sf::Sprite newPiece;
	newPiece.setTexture(*(s_body.begin()->getTexture()));
	newPiece.setPosition(s_head->getPosition() + direction);

	s_head = s_body.insert(++s_head, newPiece);
}

void Snake::Decrease(const sf::Vector2f& direction)
{
	s_tail = s_body.erase(s_tail);
}

bool Snake::IsSelfIntersecting() const
{
	bool flag = false;

	for (auto piece = s_body.begin(); piece != s_body.end();++piece)
	{
		if (s_head != piece)
		{
			flag = IsOn(*piece);
			if (flag) break;
		}
	}
	return flag;
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	for (auto& piece : s_body)
	{
		target.draw(piece);
	}
}