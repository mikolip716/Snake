#pragma once

import <list>;
import <iostream>;
import <ranges>;
#include <SFML/Graphics.hpp>
#include <Windows.h>
#pragma comment(lib,"user32.lib")   //potrzebne do dzialania ukrywania konsoli

class Snake
{
private:
	sf::Texture segment_texture;
public:
	std::list<sf::Sprite> body;
	std::list<sf::Sprite>::iterator head;
	std::list<sf::Sprite>::iterator tail;
	sf::Vector2f direction;
	void initialise();
	void move();
	bool collides(sf::Sprite& thing);
	void grow();
	bool collides_with_self();
	void draw(sf::RenderWindow& window);
	void reset();
};