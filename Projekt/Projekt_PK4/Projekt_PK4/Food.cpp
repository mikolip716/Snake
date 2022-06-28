#include "Food.h"
#include "Game.h"


void Food::initialise(Snake& snake)
{
    if (!food_texture.loadFromFile("resources/pepper.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading food sprite failed";
        exit(1);
    }
    food_sprite.setTexture(food_texture);
    game_borders = {1, 25, 1, 17};
    generate(snake);
    value = 100;
}

void Food::generate(Snake& snake)
{
    bool retry = false;
    sf::Vector2i position;
    position = generate_position();
    for (auto& segment : snake.body)
    {
        if (segment.getGlobalBounds().contains(position.x, position.y))
        {
            retry = true;
        }
    }
    if (retry)
    {
        generate(snake);
    }
    else
    {
        food_sprite.setPosition(position.x, position.y);
    }
    eaten = false;
}

sf::Vector2i Food::generate_position()
{
    std::random_device device;
    std::mt19937 rng(device());
    std::uniform_int_distribution<std::mt19937::result_type> generator_x(game_borders[0], game_borders[1]);
    std::uniform_int_distribution<std::mt19937::result_type> generator_y(game_borders[2], game_borders[3]);
    int x = 75 + (generator_x(rng) * 25);       //przeliczenie pozycji z kratek tla na piksele
    int y = 100 + (generator_y(rng) * 25);
    return sf::Vector2i(x, y);
}

void Food::draw(sf::RenderWindow& window)
{
    if (!eaten)
    {
        window.draw(food_sprite);
    }
}
