#include "Leaderboard.h"

void Leaderboard::initialise()
{
    exit_leaderboard = false;
    if (!menu_button_texture.loadFromFile("resources/menu_btn.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading menu button failed";
        exit(1);
    }
    if (!diff_button_easy_texture.loadFromFile("resources/button_easy.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading button-easy failed";
        exit(1);
    }
    if (!diff_button_medium_texture.loadFromFile("resources/button_medium.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading button-medium failed";
        exit(1);
    }
    if (!diff_button_hard_texture.loadFromFile("resources/button_hard.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading button-hard failed";
        exit(1);
    }
    if (!background_texture.loadFromFile("resources/leaderboard_bg.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading background failed";
        exit(1);
    }
    //brak obslugi bledu odczytu, zwracane jest false mimo poprawnego wczytania, prawdopodobnie blad w bibliotece
    font.loadFromFile("resources/calibri_regular.ttf");

    menu_button_sprite.setTexture(menu_button_texture);
    menu_button_sprite.setOrigin(100.f, 25.f);
    menu_button_sprite.setPosition(600.f, 550.f);
    diff_button_easy_sprite.setTexture(diff_button_easy_texture);
    diff_button_easy_sprite.setOrigin(90.f, 25.f);
    diff_button_easy_sprite.setPosition(190.f, 50.f);
    diff_button_easy_sprite.setColor(sf::Color(100, 100, 100));
    diff_button_medium_sprite.setTexture(diff_button_medium_texture);
    diff_button_medium_sprite.setOrigin(90.f, 25.f);
    diff_button_medium_sprite.setPosition(400.f, 50.f);
    diff_button_hard_sprite.setTexture(diff_button_hard_texture);
    diff_button_hard_sprite.setOrigin(90.f, 25.f);
    diff_button_hard_sprite.setPosition(610.f, 50.f);
    background_sprite.setTexture(background_texture);
    background_sprite.setOrigin(300.f, 200.f);
    background_sprite.setPosition(400.f, 300.f);

    difficulty = 'e';

    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(36);
    text.setPosition(120.f, 65.f);
}

int Leaderboard::event_loop(sf::RenderWindow& window)
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
                exit_leaderboard = true;
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
                    exit_leaderboard = true;
                }
                if (is_button_pressed(diff_button_easy_sprite.getGlobalBounds(), mouse_pos))
                {
                    difficulty = 'e';
                    diff_button_easy_sprite.setColor(sf::Color(100, 100, 100));
                    diff_button_medium_sprite.setColor(sf::Color(255, 255, 255));
                    diff_button_hard_sprite.setColor(sf::Color(255, 255, 255));
                }
                if (is_button_pressed(diff_button_medium_sprite.getGlobalBounds(), mouse_pos))
                {
                    difficulty = 'm';
                    diff_button_easy_sprite.setColor(sf::Color(255, 255, 255));
                    diff_button_medium_sprite.setColor(sf::Color(100, 100, 100));
                    diff_button_hard_sprite.setColor(sf::Color(255, 255, 255));
                }
                if (is_button_pressed(diff_button_hard_sprite.getGlobalBounds(), mouse_pos))
                {
                    difficulty = 'h';
                    diff_button_easy_sprite.setColor(sf::Color(255, 255, 255));
                    diff_button_medium_sprite.setColor(sf::Color(255, 255, 255));
                    diff_button_hard_sprite.setColor(sf::Color(100, 100, 100));
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

void Leaderboard::display_scores(sf::RenderWindow& window)
{
    std::string filename;
    std::string line;
    std::string record;
    std::string name_saved;
    std::string score_saved;
    std::string delimiter = ",";
    float update_pos_y;
    int pos = 0;
    switch (difficulty)
    {
    case 'e':
    {
        filename = "leaderboard_easy.txt";
        break;
    }
    case 'm':
    {
        filename = "leaderboard_medium.txt";
        break;
    }
    case 'h':
    {
        filename = "leaderboard_hard.txt";
        break;
    }
    default:
        break;
    }
    std::ifstream file(filename);
    if (!file.good())
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "error: leaderboard file cannot be opened" << '\n';
        exit(1);
    }
    text.setPosition(120.f, 65.f);
    while (std::getline(file, line))
    {
        name_saved = line.substr(0, line.find(delimiter));
        score_saved = line.substr(line.find(delimiter) + 1, line.size());
        pos++;
        update_pos_y = text.getGlobalBounds().top + 25.f;
        text.setString(std::to_string(pos));
        text.setPosition(120.f, update_pos_y);
        window.draw(text);
        text.setString(name_saved);
        text.setPosition(320.f, update_pos_y);
        window.draw(text);
        text.setString(score_saved);
        text.setPosition(520.f, update_pos_y);
        window.draw(text);
    }
    file.close();
}

void Leaderboard::draw(sf::RenderWindow& window)
{
    window.clear(sf::Color(17, 41, 23, 255));
    window.draw(menu_button_sprite);
    window.draw(diff_button_easy_sprite);
    window.draw(diff_button_medium_sprite);
    window.draw(diff_button_hard_sprite);
    window.draw(background_sprite);
    display_scores(window);
    window.display();
}