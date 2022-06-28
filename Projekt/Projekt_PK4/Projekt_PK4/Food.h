#pragma once

//#include <iostream>
import <iostream>;
import <vector>;
import <random>;
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include <Windows.h>
#pragma comment(lib,"user32.lib")   //potrzebne do dzialania ukrywania konsoli

class Food
{
	private:
		sf::Texture food_texture;
		sf::Vector2i generate_position();
	public:
		bool eaten;
		int value;
		sf::Sprite food_sprite;
		std::vector<int> game_borders;		//0 - lewy x, 1 - prawy x, 2 - gorny y, 3 - dolny y (ilosc kratek tla)
		void initialise(Snake& snake);
		void generate(Snake& snake);
		void draw(sf::RenderWindow& window);
};