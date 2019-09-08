#include <SFML/Graphics.hpp>
// #define LOG
#ifdef LOG
#include <spdlog/spdlog.h>
#define LOG_INFO(...)          spdlog::info(__VA_ARGS__)
#define LOG_DEBUG(...)          spdlog::debug(__VA_ARGS__)
#else
#define LOG_INFO
#define LOG_DEBUG
#endif

sf::Vector2f viewSize(1024, 768);
sf::VideoMode vm(viewSize.x, viewSize.y);

int main()
{
    #ifdef LOG
    spdlog::set_level(spdlog::level::debug);
    #endif
    LOG_INFO("Welcome to spdlog!");
    LOG_INFO("SFML works!");

    sf::RenderWindow window(vm, "SFML works!", sf::Style::Default);

    sf::RectangleShape rect(sf::Vector2f(500.0f, 300.0f));
    rect.setFillColor(sf::Color::Yellow);
    rect.setPosition(viewSize.x / 2, viewSize.y / 2);
    rect.setOrigin(sf::Vector2f(rect.getSize().x / 2, rect.getSize().y / 2));

    LOG_DEBUG("Start main loop!");
    while (window.isOpen())
    {
        // Handle Keyboard Events
        // Update Game Objects in the scene
        window.clear(sf::Color::Red);
        // Render Game Objects
        window.draw(rect);
        window.display();
    }

    return 0;
}
