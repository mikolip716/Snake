#include "Main_menu.h"


void Main_menu::initialise()
{
    if (!title_texture.loadFromFile("resources/snake_title.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading title screen failed";
        exit(1);
    }
    if (!start_btn_texture.loadFromFile("resources/start_btn.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading start button failed";
        exit(1);
    }
    if (!options_btn_texture.loadFromFile("resources/options_btn.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading options button failed";
        exit(1);
    }
    if (!leaderboard_btn_texture.loadFromFile("resources/leader_btn.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading leaderboard button failed";
        exit(1);
    }
    if (!exit_btn_texture.loadFromFile("resources/exit_btn.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading exit button failed";
        exit(1);
    }
    title_sprite.setTexture(title_texture);
    title_sprite.setOrigin(200.f, 127.5);
    title_sprite.setPosition(400.f, 160.f);
    title_sprite.scale(1.65, 1.65);
    start_btn_sprite.setTexture(start_btn_texture);
    start_btn_sprite.setOrigin(100.f, 25.f);
    start_btn_sprite.setPosition(400.f, 330.f);
    options_btn_sprite.setTexture(options_btn_texture);
    options_btn_sprite.setOrigin(100.f, 25.f);
    options_btn_sprite.setPosition(400.f, 400.f);
    leaderboard_btn_sprite.setTexture(leaderboard_btn_texture);
    leaderboard_btn_sprite.setOrigin(100.f, 25.f);
    leaderboard_btn_sprite.setPosition(400.f, 470.f);
    exit_btn_sprite.setTexture(exit_btn_texture);
    exit_btn_sprite.setOrigin(100.f, 25.f);
    exit_btn_sprite.setPosition(400.f, 540.f);
}

int Main_menu::event_loop(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
        {
            window.close();
            break;
        }
        case sf::Event::KeyPressed:
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mouse_pos(event.mouseButton.x, event.mouseButton.y);
                if (is_button_pressed(start_btn_sprite.getGlobalBounds(), mouse_pos))
                {
                    return 1; //przejdz do gry
                }
                if (is_button_pressed(options_btn_sprite.getGlobalBounds(), mouse_pos))
                {
                    return 2; //przejdz do opcji
                }
                if (is_button_pressed(leaderboard_btn_sprite.getGlobalBounds(), mouse_pos))
                {
                    return 3; //przejdz do tabeli wynikow
                }
                if (is_button_pressed(exit_btn_sprite.getGlobalBounds(), mouse_pos))
                {
                    return 4; //przejdz do tabeli wynikow
                }
            }
            break;
        }
        default:
        {
            return 0; //zostan w menu glownym
            break;
        }  
        }
    }
    return 0; //zostan w menu glownym
}

void Main_menu::draw(sf::RenderWindow& window)
{
    window.clear(sf::Color(17, 41, 23, 255));
    window.draw(start_btn_sprite);
    window.draw(options_btn_sprite);
    window.draw(leaderboard_btn_sprite);
    window.draw(exit_btn_sprite);
    window.draw(title_sprite);
    window.display();
}