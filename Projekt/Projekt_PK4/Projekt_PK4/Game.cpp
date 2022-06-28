#include "Game.h"

void Game::initialise()
{
    exit_game = false;
    score = 0;
    paused = false;
    if (!background_texture.loadFromFile("resources/background3.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading background failed";
        exit(1);
    }
    if (!wall_n_texture.loadFromFile("resources/wall_n.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading wall failed";
        exit(1);
    }
    if (!wall_s_texture.loadFromFile("resources/wall_s.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading wall failed";
        exit(1);
    }
    if (!wall_w_texture.loadFromFile("resources/wall_w.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading wall failed";
        exit(1);
    }
    if (!wall_e_texture.loadFromFile("resources/wall_e.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading wall failed";
        exit(1);
    }
    if (!score_bar_texture.loadFromFile("resources/score_bar.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading score bar failed";
        exit(1);
    }
    if (!pause_texture.loadFromFile("resources/pause.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading pause screen failed";
        exit(1);
    }
    font.loadFromFile("resources/calibri_regular.ttf");   //brak obslugi bledu odczytu, zwracane jest false mimo poprawnego wczytania

    background_sprite.setTexture(background_texture);
    background_sprite.setOrigin(325.f, 225.f);
    background_sprite.setPosition(400.f,325.f);
    wall_n_sprite.setTexture(wall_n_texture);
    wall_s_sprite.setTexture(wall_s_texture);
    wall_w_sprite.setTexture(wall_w_texture);
    wall_e_sprite.setTexture(wall_e_texture);
    wall_n_sprite.setOrigin(350.f, 12.5);
    wall_s_sprite.setOrigin(350.f, 12.5);
    wall_w_sprite.setOrigin(12.5, 250.f);
    wall_e_sprite.setOrigin(12.5, 250.f);
    wall_n_sprite.setPosition(400.f, 87.5);
    wall_s_sprite.setPosition(400.f, 562.5);
    wall_w_sprite.setPosition(62.5, 325.f);
    wall_e_sprite.setPosition(737.5, 325.f);
    score_bar_sprite.setTexture(score_bar_texture);
    score_bar_sprite.setOrigin(350.f, 25.f);
    score_bar_sprite.setPosition(400.f, 37.5);
    pause_sprite.setTexture(pause_texture);

    walls.push_back(wall_n_sprite);
    walls.push_back(wall_s_sprite);
    walls.push_back(wall_w_sprite);
    walls.push_back(wall_e_sprite);

    score_text.setFont(font);
    score_text.setCharacterSize(36);
    score_text.setFillColor(sf::Color::Black);
    difficulty_text = score_text;
    score_text.setPosition(165.f,12.5);
    score_text.setString("0");
    difficulty_text.setPosition(565.f, 12.5);
    difficulty_text.setString("Easy");

    snake.initialise();
    food.initialise(snake);
    game_over.initialise();


    difficulty = 'e';
    name = "play1";
    set_speed();
}

int Game::event_loop(sf::RenderWindow& window)
{
    sf::Time time;
    sf::Event event{};
    get_input(event, window);

    if (!paused)
    {
        if (food.eaten)
        {
            food.generate(snake);
        }
        if (snake.collides(food.food_sprite))
        {
            snake.grow();
            food.eaten = true;
            score += food.value;
            score_text.setString(std::to_string(score));
        }
        time = clock.getElapsedTime();
        if (snake.direction != sf::Vector2f(0.f, 0.f))
        {
            if (time.asMilliseconds() > game_speed)
            {
                snake.move();
                clock.restart();
            }
        }
        if (check_wall_collision() or snake.collides_with_self())
        {
            lose(window);
        }
    }
    return 0;
}

void Game::draw(sf::RenderWindow& window)
{
	window.clear(sf::Color(17, 41, 23, 255));
    window.draw(background_sprite);
    for (auto wall = std::ranges::begin(walls); wall != std::ranges::end(walls); ++wall)
    {
        window.draw(*wall);
    }
    window.draw(score_bar_sprite);
    window.draw(score_text);
    window.draw(difficulty_text);
    food.draw(window);
    snake.draw(window);
    if (paused)
    {
        window.draw(pause_sprite);
    }
	window.display();
}

bool Game::check_wall_collision()
{
    bool collision = false;
    for (auto &wall : walls)
    {
        collision = snake.collides(wall);
        if (collision == true)
        {
            break;
        }
    }
    return collision;
}

void Game::set_speed()
{
    switch (difficulty)
    {
    case 'e':
    {
        game_speed = 85;
        difficulty_text.setString("Easy");
        break;
    } 
    case 'm':
    {
        game_speed = 70;
        difficulty_text.setString("Medium");
        break;
    }
    case 'h':
    {
        game_speed = 55;
        difficulty_text.setString("Hard");
        break;
    }
    default:
        break;
    }
}

void Game::lose(sf::RenderWindow& window)
{
    snake.reset();
    score_text.setString("0");
    game_over.score_text.setString(std::to_string(score));
    save_score();
    prev_score = score;
    score = 0;
    paused = false;
    while (exit_game == false)
    {
        game_over.event_loop(window);
        game_over.draw(window);
        if (game_over.exit_game == true)
        {
            exit_game = true;
        }
        if (game_over.restart == true)
        {
            break;
        }
    }
}

void Game::save_score()
{
    std::string filename;
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
    std::ofstream temp("temp.txt");
    std::string line;
    std::string delimiter = ",";
    std::string score_str;
    std::string temp_str;
    std::string to_replace;
    std::string to_save = name + "," + std::to_string(score);
    int score_val = 0;
    bool save = false;
    int line_num = 0;
    const char* path = filename.c_str();
    bool replaced = false;
    while (std::getline(file, line))
    {
        line_num++;
    }
    file.clear();
    file.seekg(0);
    while (std::getline(file, line))
    {
        score_str = line.substr(line.find(delimiter) + 1, line.size());
        if (score_str.size() != 0)
        {
            score_val = std::stoi(score_str);
        }
        if (score > score_val)
        {
            to_replace = line;
            save = true;
            break;
        }
    }
    file.clear();
    file.seekg(0);
    if (line_num < 10 and !save)
    {
        while (file >> temp_str)
        {
            temp << temp_str;
            temp << '\n';
        }
        file.seekg(0, std::ios::end);
        temp << to_save;
        temp << '\n';
        file.close();
        temp.close();
        std::filesystem::remove(path);
        std::filesystem::rename("temp.txt", path);
    }
    if (line_num < 10 and save)
    {
        while (file >> temp_str)
        {
            if (to_replace == temp_str and !replaced)
            {
                replaced = true;
                std::string temp_2 = temp_str;
                temp_str = to_save;
                temp << temp_str;
                temp << '\n';
                temp << temp_2;
                temp << '\n';
                continue;
            }
            temp << temp_str;
            temp << '\n';
        }
        file.close();
        temp.close();
        std::filesystem::remove(path);
        std::filesystem::rename("temp.txt", path);
    }
    if (save and line_num >= 10)
    {
        while (file >> temp_str)
        {
            if (line_num > 0)
            {
                line_num--;
                if (to_replace == temp_str and !replaced)
                {
                    line_num--;
                    replaced = true;
                    std::string temp_2 = temp_str;
                    temp_str = to_save;
                    temp << temp_str;
                    temp << '\n';
                    if (line_num > 0)
                    {
                        temp << temp_2;
                        temp << '\n';
                    }
                    continue;
                }
                temp << temp_str;
                temp << '\n';
            }
        }
        file.close();
        temp.close();
        std::filesystem::remove(path);
        std::filesystem::rename("temp.txt", path);
    }
    file.close();
    temp.close();
}

void Game::get_input(sf::Event event, sf::RenderWindow& window)
{
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
            if (event.key.code == sf::Keyboard::W)
            {
                if (snake.direction != sf::Vector2f(0.f, 25.f))
                {
                    snake.direction = sf::Vector2f(0.f, -25.f);
                }
            }
            if (event.key.code == sf::Keyboard::S)
            {
                if (snake.direction != sf::Vector2f(0.f, -25.f))
                {
                    snake.direction = sf::Vector2f(0.f, 25.f);
                }
            }
            if (event.key.code == sf::Keyboard::A)
            {
                if (snake.direction != sf::Vector2f(25.f, 0.f))
                {
                    snake.direction = sf::Vector2f(-25.f, 0.f);
                }
            }
            if (event.key.code == sf::Keyboard::D)
            {
                if (snake.direction != sf::Vector2(-25.f, 0.f))
                {
                    snake.direction = sf::Vector2f(25.f, 0.f);
                }
            }
            if (event.key.code == sf::Keyboard::P)
            {
                if (!paused)
                {
                    paused = true;
                }
                else
                {
                    paused = false;
                }
            }
            if (event.key.code == sf::Keyboard::Escape)
            {
                if (paused)
                {
                    exit_game = true;
                    paused = false;
                    score = 0;
                    score_text.setString('0');
                    snake.reset();
                }
            }
            break;
        }
        default:
        {
            break;
        }
        }

    }
}
