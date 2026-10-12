#include <SFML/Graphics.hpp>

constexpr unsigned int WINDOW_WIDTH = 800;
constexpr unsigned int WINDOW_HEIGHT = 600;

constexpr float PADDLE_WIDTH = 100.f; //Paddle's width
constexpr float PADDLE_HEIGHT = 20.f; //Paddle's height
constexpr float PADDLE_GAP = 30.f; // The gap below the paddle
const sf::Color PADDLE_COLOR = sf::Color::White; // Paddle's color
constexpr float PADDLE_SPEED = 400.f; // pixels per second

int main() 
{
    const float paddleStartX = (WINDOW_WIDTH - PADDLE_WIDTH) / 2.f;
    const float paddleStartY = (WINDOW_HEIGHT - PADDLE_HEIGHT - PADDLE_GAP);

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Breakout");
    sf::RectangleShape paddle({PADDLE_WIDTH, PADDLE_HEIGHT}); // Create a paddle with size
    paddle.setFillColor(PADDLE_COLOR);
    paddle.setPosition({paddleStartX, paddleStartY}); // Set the paddle's initial position

    sf::Clock clock;

    while (window.isOpen())
    {
        const float dt = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) // true while Left arrow is held
        {
            paddle.move({-PADDLE_SPEED * dt, 0.f}); // Move the paddle left
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) // true while Right arrow is held
        {
            paddle.move({PADDLE_SPEED * dt, 0.f}); // Move the paddle right
        }

        sf::Vector2f position = paddle.getPosition(); //copy the paddle's position

        if (position.x <= 0.f)
        {
            position.x = 0.f; // Keep the paddle within the left boundary
        }
        else if (position.x + PADDLE_WIDTH >= WINDOW_WIDTH)
        {
            position.x = WINDOW_WIDTH - PADDLE_WIDTH; // Keep the paddle within the right boundary
        }

        paddle.setPosition(position); // Update the paddle's position

        window.clear();
        window.draw(paddle); 
        window.display();

    }
}
