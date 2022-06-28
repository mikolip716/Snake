#pragma once
import <iostream>;
import <fstream>;
import <string>;
import <algorithm>;
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include <Windows.h>
#pragma comment(lib,"user32.lib")   //potrzebne do dzialania ukrywania konsoli

class Leaderboard : public Menu
{
private:
	sf::Texture menu_button_texture;
	sf::Texture diff_button_easy_texture;
	sf::Texture diff_button_medium_texture;
	sf::Texture diff_button_hard_texture;
	sf::Texture background_texture;
	sf::Font font;
	sf::Sprite menu_button_sprite;
	sf::Sprite diff_button_easy_sprite;
	sf::Sprite diff_button_medium_sprite;
	sf::Sprite diff_button_hard_sprite;
	sf::Sprite background_sprite;
	sf::Text text;
public:

	bool exit_leaderboard;
	char difficulty;	//e - easy, m - medium, h - hard
	virtual void initialise();
	virtual int event_loop(sf::RenderWindow& window);
	virtual void draw(sf::RenderWindow& window);
	void display_scores(sf::RenderWindow& window);
};