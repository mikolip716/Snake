#include "Menu.h"

bool Menu::is_button_pressed(sf::FloatRect button, sf::Vector2i mouse_pos)
{
	sf::Vector2f mouse_pos_f(mouse_pos);
	if (button.contains(mouse_pos_f))
	{
		return true;
	}
	return false;

}