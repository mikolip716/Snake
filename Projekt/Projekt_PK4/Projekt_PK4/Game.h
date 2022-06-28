#pragma once

import <iostream>;
import <string>;
import <vector>;
import <fstream>;
import <algorithm>;
import <ranges>;
import <filesystem>;
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Snake.h"
#include "Food.h"
#include "Game_over.h"
#include <Windows.h>
#pragma comment(lib,"user32.lib")   //potrzebne do dzialania ukrywania konsoli

class Game : public Menu
{
	private:
		int score;
		int game_speed;
		bool paused;
		sf::Texture background_texture;
		sf::Texture wall_n_texture;
		sf::Texture wall_s_texture;
		sf::Texture wall_e_texture;
		sf::Texture wall_w_texture;
		sf::Texture score_bar_texture;
		sf::Texture pause_texture;
		sf::Sprite background_sprite;
		sf::Sprite wall_n_sprite;
		sf::Sprite wall_s_sprite;
		sf::Sprite wall_e_sprite;
		sf::Sprite wall_w_sprite;
		sf::Sprite score_bar_sprite;
		sf::Sprite pause_sprite;
		sf::Font font;
		std::vector<sf::Sprite> walls;
		sf::Clock clock;
		Snake snake;
		Food food;
		Game_over game_over;
	public:
		sf::Text score_text;
		sf::Text difficulty_text;
		int prev_score;
		bool exit_game;
		char difficulty;	//e - easy, m - medium, h - hard
		std::string name;
		virtual void initialise();
		virtual int event_loop(sf::RenderWindow& window);
		virtual void draw(sf::RenderWindow& window);
		bool check_wall_collision();
		void set_speed();
		void lose(sf::RenderWindow& window);
		void get_input(sf::Event event, sf::RenderWindow& window);
		void save_score();
};
