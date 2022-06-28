#pragma once
import <iostream>;
#include <SFML/Graphics.hpp>

class Menu
{
	public:
		virtual void initialise() = 0;
		bool is_button_pressed(sf::FloatRect button, sf::Vector2i mouse_pos);
		virtual int event_loop(sf::RenderWindow& window) = 0;
		virtual void draw(sf::RenderWindow& window) = 0;
};