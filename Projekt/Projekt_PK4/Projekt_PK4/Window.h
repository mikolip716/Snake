#pragma once
import <iostream>;
#include <SFML/Graphics.hpp>


class Window
{
	private:
		int res_x;
		int res_y;
		sf::Texture title_texture;
		sf::Sprite title_sprite;
	public:
		Window() { res_x = 800; res_y = 600; };
		void main_loop();
		//void event_loop(sf::RenderWindow& window);
		enum menu_type
		{
			main_menu = 0,
			game = 1,
			options = 2,
			leaderboard = 3
		};

};