#pragma once
import <iostream>;
import <string>;
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include <Windows.h>
#pragma comment(lib,"user32.lib")   //potrzebne do dzialania ukrywania konsoli

class Main_menu : public Menu
{
	private:
		sf::Texture title_texture;
		sf::Texture start_btn_texture;
		sf::Texture options_btn_texture;
		sf::Texture leaderboard_btn_texture;
		sf::Texture exit_btn_texture;
	public:
		sf::Sprite start_btn_sprite;
		sf::Sprite options_btn_sprite;
		sf::Sprite leaderboard_btn_sprite;
		sf::Sprite exit_btn_sprite;
		sf::Sprite title_sprite;
		virtual void initialise();
		virtual int event_loop(sf::RenderWindow& window);
		virtual void draw(sf::RenderWindow& window);
};