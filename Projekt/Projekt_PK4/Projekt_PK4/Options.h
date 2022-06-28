#pragma once
import <iostream>;
import <regex>;
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include <Windows.h>
#pragma comment(lib,"user32.lib")   //potrzebne do dzialania ukrywania konsoli

class Options : public Menu
{
	private:
		sf::Texture controls_texture;
		sf::Texture menu_button_texture;
		sf::Texture difficulty_bar_texture;
		sf::Texture diff_button_easy_texture;
		sf::Texture diff_button_medium_texture;
		sf::Texture diff_button_hard_texture;
		sf::Texture name_bar_texture;
		sf::Texture input_bar_texture;
		sf::Font font;
		sf::Sprite menu_button_sprite;
		sf::Sprite controls_sprite;
		sf::Sprite difficulty_bar_sprite;
		sf::Sprite diff_button_easy_sprite;
		sf::Sprite diff_button_medium_sprite;
		sf::Sprite diff_button_hard_sprite;
		sf::Sprite name_bar_sprite;
		sf::Sprite input_bar_sprite;
		sf::Text name;
		std::regex validate_input;
		bool valid;
	public:
		bool change_difficulty;
		bool exit_options;
		bool is_reading_text;
		char difficulty;
		std::string player_input;
		virtual void initialise();
		virtual int event_loop(sf::RenderWindow& window);
		virtual void draw(sf::RenderWindow& window);
		void input_text();
};