#include <SFML/Graphics.hpp>

constexpr unsigned int WINDOW_WIDTH = 800;
constexpr unsigned int WINDOW_HEIGHT = 600;

int main() {
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Breakout");
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        window.clear();
        window.display();
    }
}
