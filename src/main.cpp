#include <SFML/Graphics.hpp>

constexpr unsigned int WINDOW_WIDTH = 800;
constexpr unsigned int WINDOW_HEIGHT = 600;

constexpr float PADDLE_WIDTH = 100.f; //Paddle's width
constexpr float PADDLE_HEIGHT = 20.f; //Paddle's height
constexpr float PADDLE_GAP = 30.f; // The gap below the paddle
const sf::Color PADDLE_COLOR = sf::Color::White; // Paddle's color
constexpr float PADDLE_SPEED = 400.f; // pixels per second

constexpr float BALL_RADIUS = 10.f; // Ball's radius
constexpr float BALL_DIAMETER = 2.f * BALL_RADIUS; // Ball's diameter
const sf::Color BALL_COLOR = sf::Color::White; // Ball's color
constexpr float BALL_START_SPEED_X = 200.f; // Ball's initial horizontal speed
constexpr float BALL_START_SPEED_Y = -250.f; // Ball's initial vertical speed

int main() 
{
    const float paddleStartX = (WINDOW_WIDTH - PADDLE_WIDTH) / 2.f;
    const float paddleStartY = (WINDOW_HEIGHT - PADDLE_HEIGHT - PADDLE_GAP);

    const sf::Vector2f ballStartVelocity({BALL_START_SPEED_X, BALL_START_SPEED_Y}); // Ball's initial velocity
    sf::Vector2f ballVelocity = ballStartVelocity; // Current velocity of the ball

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Breakout");

    sf::RectangleShape paddle({PADDLE_WIDTH, PADDLE_HEIGHT}); // Create a paddle with size
    paddle.setFillColor(PADDLE_COLOR);
    paddle.setPosition({paddleStartX, paddleStartY}); // Set the paddle's initial position

    sf::CircleShape ball(BALL_RADIUS); // Create a ball with radius
    ball.setFillColor(BALL_COLOR);
    const sf::Vector2f ballStartPosition({WINDOW_WIDTH / 2.f - BALL_RADIUS, WINDOW_HEIGHT / 2.f - BALL_RADIUS}); // Ball's initial position
    ball.setPosition(ballStartPosition); // Set the ball's initial position

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

        ball.move(ballVelocity * dt); // Move the ball based on its velocity and the elapsed time
        
        sf::Vector2f ballPosition = ball.getPosition(); //copy the ball's position
        if (ballPosition.x <= 0.f)
        {
            ballPosition.x = 0.f; // Keep the ball within the left boundary
            ballVelocity.x = -ballVelocity.x; // Reverse the ball's horizontal direction
        }
        if (ballPosition.x >= WINDOW_WIDTH - BALL_DIAMETER)
        {
            ballPosition.x = WINDOW_WIDTH - BALL_DIAMETER; // Keep the ball within the right boundary
            ballVelocity.x = -ballVelocity.x; // Reverse the ball's horizontal direction
        }
        if (ballPosition.y <= 0.f)
        {
            ballPosition.y = 0.f;
            ballVelocity.y = -ballVelocity.y; // Reverse the ball's vertical direction
        }
        if (ballPosition.y >= WINDOW_HEIGHT)
        {
            ballPosition = ballStartPosition; //  Put the ball back at starting position
            ballVelocity = ballStartVelocity; // Reset the ball's velocity
        }

        ball.setPosition(ballPosition); // Update the ball's position
        
        window.clear();
        window.draw(paddle); 
        window.draw(ball);
        window.display();
    }
}
