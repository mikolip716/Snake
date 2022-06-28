#include "Game_over.h"

void Game_over::initialise()
{
    if (!menu_button_texture.loadFromFile("resources/menu_btn.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading menu button failed";
        exit(1);
    }
    if (!start_button_texture.loadFromFile("resources/start_btn.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading start button failed";
        exit(1);
    }
    if (!game_over_texture.loadFromFile("resources/game_over.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading game over screen failed";
        exit(1);
    }
    //brak obslugi bledu odczytu, zwracane jest false mimo poprawnego wczytania, prawdopodobnie blad w bibliotece
    font.loadFromFile("resources/calibri_regular.ttf");

    menu_button_sprite.setTexture(menu_button_texture);
    menu_button_sprite.setOrigin(100.f, 25.f);
    menu_button_sprite.setPosition(600.f, 450.f);
    start_button_sprite.setTexture(start_button_texture);
    start_button_sprite.setOrigin(100.f, 25.f);
    start_button_sprite.setPosition(200.f, 450.f);
    game_over_sprite.setTexture(game_over_texture);
    game_over_sprite.setOrigin(300.f, 150.f);
    game_over_sprite.setPosition(400.f, 250.f);

    score_text.setFont(font);
    score_text.setCharacterSize(64);
    score_text.setFillColor(sf::Color::Black);
    score_text.setString('0');
    score_text.setPosition(340.f, 300.f);

    exit_game = false;
    restart = false;
    close_game = false;
}

int Game_over::event_loop(sf::RenderWindow& window)
{
    exit_game = false;
    restart = false;
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
        {
            window.close();
            exit(0);
            break;
        }
        case sf::Event::KeyPressed:
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                exit_game = true;
            }
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mouse_pos(event.mouseButton.x, event.mouseButton.y);
                if (is_button_pressed(menu_button_sprite.getGlobalBounds(), mouse_pos))
                {
                    exit_game = true;
                }
                if (is_button_pressed(start_button_sprite.getGlobalBounds(), mouse_pos))
                {
                    restart = true;
                }
            }
            break;
        }
        default:
            break;
        }
    }
	return 0;
}

void Game_over::draw(sf::RenderWindow& window)
{
    window.clear(sf::Color(17, 41, 23, 255));
    window.draw(game_over_sprite);
    window.draw(start_button_sprite);
    window.draw(menu_button_sprite);
    window.draw(score_text);
    window.display();
}
