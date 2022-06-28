#pragma once
import <iostream>;
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include <Windows.h>
#pragma comment(lib,"user32.lib")   //potrzebne do dzialania ukrywania konsoli

class Game_over : Menu
{
	private:
		sf::Font font;
		sf::Texture menu_button_texture;
		sf::Texture start_button_texture;
		sf::Texture game_over_texture;
		sf::Sprite menu_button_sprite;
		sf::Sprite start_button_sprite;
		sf::Sprite game_over_sprite;
	public:
		sf::Text score_text;
		bool exit_game;
		bool restart;
		bool close_game;
		int score;
		virtual void initialise();
		virtual int event_loop(sf::RenderWindow& window);
		virtual void draw(sf::RenderWindow& window);
};