#include  "Options.h"

void Options::initialise()
{
    exit_options = false;
    if (!controls_texture.loadFromFile("resources/controls.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading controls failed";
        exit(1);
    }
    if (!menu_button_texture.loadFromFile("resources/menu_btn.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading menu button failed";
        exit(1);
    }
    if (!difficulty_bar_texture.loadFromFile("resources/diff_bar.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading difficulty bar failed";
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
    if (!name_bar_texture.loadFromFile("resources/name_bar.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading name bar failed";
        exit(1);
    }
    if (!input_bar_texture.loadFromFile("resources/input_bar.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading input bar failed";
        exit(1);
    }
    //brak obslugi bledu odczytu, zwracane jest false mimo poprawnego wczytania, prawdopodobnie blad w bibliotece
    font.loadFromFile("resources/calibri_regular.ttf");

    controls_sprite.setTexture(controls_texture);
    controls_sprite.setOrigin(300.f, 100.f);
    controls_sprite.setPosition(400.f, 415.f);
    menu_button_sprite.setTexture(menu_button_texture);
    menu_button_sprite.setOrigin(100.f, 25.f);
    menu_button_sprite.setPosition(600.f, 550.f);
    difficulty_bar_sprite.setTexture(difficulty_bar_texture);
    difficulty_bar_sprite.setOrigin(300.f, 25.f);
    difficulty_bar_sprite.setPosition(400.f, 100.f);
    diff_button_easy_sprite.setTexture(diff_button_easy_texture);
    diff_button_easy_sprite.setOrigin(90.f, 25.f);
    diff_button_easy_sprite.setPosition(190.f, 165.f);
    diff_button_medium_sprite.setTexture(diff_button_medium_texture);
    diff_button_medium_sprite.setOrigin(90.f, 25.f);
    diff_button_medium_sprite.setPosition(400.f, 165.f);
    diff_button_hard_sprite.setTexture(diff_button_hard_texture);
    diff_button_hard_sprite.setOrigin(90.f, 25.f);
    diff_button_hard_sprite.setPosition(610.f, 165.f);
    name_bar_sprite.setTexture(name_bar_texture);
    name_bar_sprite.setOrigin(300.f, 25.f);
    name_bar_sprite.setPosition(400.f, 225.f);
    input_bar_sprite.setTexture(input_bar_texture);
    input_bar_sprite.setOrigin(300.f, 25.f);
    input_bar_sprite.setPosition(400.f, 280.f);

    name.setFont(font);
    name.setFillColor(sf::Color::Black);
    name.setCharacterSize(36);
    sf::FloatRect rect = name.getLocalBounds();
    name.setOrigin(rect.left + rect.width / 2.0f, rect.top + rect.height / 2.0f);
    name.setPosition(350.f, 255.f);

    difficulty = 'e';
    diff_button_easy_sprite.setColor(sf::Color(100, 100, 100));
    change_difficulty = false;
    is_reading_text = false;
    valid = true;

    validate_input = "[A-Za-z0-9]*";
}

int Options::event_loop(sf::RenderWindow& window)
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
                exit_options = true;
                input_bar_sprite.setColor(sf::Color(255, 255, 255));
                is_reading_text = false;
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
                    input_bar_sprite.setColor(sf::Color(255, 255, 255));
                    exit_options = true;
                    is_reading_text = false;
                }
                if (is_button_pressed(diff_button_easy_sprite.getGlobalBounds(), mouse_pos))
                {
                    difficulty = 'e';
                    change_difficulty = true;
                    diff_button_easy_sprite.setColor(sf::Color(100, 100, 100));
                    diff_button_medium_sprite.setColor(sf::Color(255, 255, 255));
                    diff_button_hard_sprite.setColor(sf::Color(255, 255, 255));
                    input_bar_sprite.setColor(sf::Color(255, 255, 255));
                    is_reading_text = false;
                }
                if (is_button_pressed(diff_button_medium_sprite.getGlobalBounds(), mouse_pos))
                {
                    difficulty = 'm';
                    change_difficulty = true;
                    diff_button_easy_sprite.setColor(sf::Color(255, 255, 255));
                    diff_button_medium_sprite.setColor(sf::Color(100, 100, 100));
                    diff_button_hard_sprite.setColor(sf::Color(255, 255, 255));
                    input_bar_sprite.setColor(sf::Color(255, 255, 255));
                    is_reading_text = false;
                }
                if (is_button_pressed(diff_button_hard_sprite.getGlobalBounds(), mouse_pos))
                {
                    difficulty = 'h';
                    change_difficulty = true;
                    diff_button_easy_sprite.setColor(sf::Color(255, 255, 255));
                    diff_button_medium_sprite.setColor(sf::Color(255, 255, 255));
                    diff_button_hard_sprite.setColor(sf::Color(100, 100, 100));
                    input_bar_sprite.setColor(sf::Color(255, 255, 255));
                    is_reading_text = false;
                }
                if (is_button_pressed(input_bar_sprite.getGlobalBounds(), mouse_pos))
                {
                    input_bar_sprite.setColor(sf::Color(100, 100, 100));
                    is_reading_text = true;
                }
                else
                {
                    input_bar_sprite.setColor(sf::Color(255, 255, 255));
                    is_reading_text = false;
                }
            }
            break;
        }
        case sf::Event::TextEntered:
        {
            if (is_reading_text)
            {
                if (event.text.unicode == '\b' and player_input.begin() != player_input.end())  // \b - backspace
                {
                    player_input.erase(player_input.end() - 1);
                }
                else if (event.text.unicode != '\b')
                {
                    player_input += event.text.unicode;
                    valid = std::regex_match(player_input, validate_input);
                    if (!valid or player_input.size() > 5)
                    {
                        player_input.erase(player_input.end() - 1);
                    }
                }
                name.setString(player_input);
            }
            break;
        }
        default:
            break;
        }
    }
    return 0;
}

void Options::draw(sf::RenderWindow& window)
{
    window.clear(sf::Color(17, 41, 23, 255));
    window.draw(controls_sprite);
    window.draw(menu_button_sprite);
    window.draw(difficulty_bar_sprite);
    window.draw(diff_button_easy_sprite);
    window.draw(diff_button_medium_sprite);
    window.draw(diff_button_hard_sprite);
    window.draw(name_bar_sprite);
    window.draw(input_bar_sprite);
    window.draw(name);
    window.display();
}