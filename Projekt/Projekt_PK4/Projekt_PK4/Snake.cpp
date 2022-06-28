#include "Snake.h"

void Snake::initialise()
{
	body = std::list<sf::Sprite>(4);
    auto end = std::ranges::end(body);
	head = --end;
	tail = std::ranges::begin(body);

    if (!segment_texture.loadFromFile("resources/segment.png"))
    {
        ShowWindow(GetConsoleWindow(), SW_RESTORE);
        std::cerr << "Loading snake segment failed";
        exit(1);
    }
    float x = 100.f;
    for (auto& element : body)
    {
        element.setTexture(segment_texture);
        element.setPosition({ x, 200.f });
        x += 25.f;
    }
}

void Snake::move()
{
    tail->setPosition(head->getPosition() + direction);
    head = tail;
    tail++;
    if (tail == std::ranges::end(body))
    {
        tail = std::ranges::begin(body);
    }
}

bool Snake::collides(sf::Sprite& thing)
{
    if (thing.getGlobalBounds().intersects(head->getGlobalBounds()))
    {
        return true;
    }
	return false;
}

void Snake::grow()
{
    sf::Sprite new_segment;
    new_segment.setTexture(*(std::ranges::begin(body)->getTexture()));
    new_segment.setPosition(head->getPosition() + direction);
    head = body.insert(++head, new_segment);
}

bool Snake::collides_with_self()
{
    bool collision = false;
    for (auto element = std::ranges::begin(body); element != std::ranges::end(body); ++element)
    {
        if (head != element)
        {
            collision = collides(*element);
            if (collision)
            {
                break;
            }
        }
    }
    return collision;
}


void Snake::draw(sf::RenderWindow& window)
{
    for (auto element = std::ranges::begin(body); element != std::ranges::end(body); ++element)
    {
        window.draw(*element);
    }
}

void Snake::reset()
{
    initialise();
    direction = sf::Vector2f(0.f, 0.f);
}
