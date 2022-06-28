#include "Window.h"
#include "Main_menu.h"
#include "Options.h"
#include "Leaderboard.h"
#include "Game.h"
#include <Windows.h>
#pragma comment(lib,"user32.lib")   //potrzebne do dzialania ukrywania konsoli

void Window::main_loop()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Snake");
    window.setFramerateLimit(60);
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    char difficulty;
    int change_window = 0;
    Main_menu menu;
    Options options_menu;
    Leaderboard leaderboard_menu;
    Game game_screen;
    menu_type menu_t = main_menu;
    Menu* screen_ptr = &menu;

    menu.initialise();
    leaderboard_menu.initialise();
    options_menu.initialise();
    game_screen.initialise();

    while (window.isOpen())
    {
        switch (menu_t)
        {
        case main_menu:
        {
            switch (change_window)
            {
            case 1:     //przejscie do gry
            {
                menu_t = game;
                game_screen.exit_game = false;
                screen_ptr = &game_screen;
                break;
            }
            case 2:     //przejscie do opcji
            {
                menu_t = options;
                options_menu.exit_options = false;
                screen_ptr = &options_menu;
                break;
            }
            case 3:     //przejscie do tabeli wynikow
            {
                menu_t = leaderboard;
                leaderboard_menu.exit_leaderboard = false;
                screen_ptr = &leaderboard_menu;
                break;
            }
            case 4:
            {
                window.close();
                break;
            }
            default:
                break;
            }
            break;
        };
        case game:
        {
            if (game_screen.exit_game == true)
            {
                menu_t = main_menu;
                screen_ptr = &menu;
            }
            break;
        };
        case options:
        {
            if (options_menu.exit_options == true)
            {
                menu_t = main_menu;
                screen_ptr = &menu;
            }
            if (options_menu.change_difficulty)
            {
                game_screen.difficulty = options_menu.difficulty;
                options_menu.change_difficulty = false;
            }
            if (options_menu.player_input.begin() != options_menu.player_input.end())
            {
                game_screen.name = options_menu.player_input;
            }
            else
            {
                game_screen.name = "play1";
            }
            game_screen.set_speed();
            break;
        }
        case leaderboard:
        {
            if (options_menu.change_difficulty)
            {
                leaderboard_menu.difficulty = options_menu.difficulty;
                options_menu.change_difficulty = false;
            }
            if (leaderboard_menu.exit_leaderboard == true)
            {
                menu_t = main_menu;
                screen_ptr = &menu;
            }
            break;
        }
        default:
            break;
        }
        change_window = screen_ptr->event_loop(window);
        screen_ptr->draw(window);
    }
}
