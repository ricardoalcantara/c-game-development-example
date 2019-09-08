#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>

int main()
{
    #ifdef DEBUG
    spdlog::set_level(spdlog::level::debug);
    #endif
    spdlog::info("Welcome to spdlog!");
    spdlog::info("SFML works!");

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    spdlog::debug("Start main loop!");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
