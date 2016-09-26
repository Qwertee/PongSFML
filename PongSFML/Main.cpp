#include <chrono>
#include <thread>
// --------------
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512
#define PADDLE_WIDTH 8
#define PADDLE_HEIGHT 112
#define PADDLE_VELOCITY .02

// TODO: Check to make sure these are correct
#define BALL_WIDTH 10
#define BALL_HEIGHT 10
#define BALL_VELOCITY 0.03 // still working out what this should be exactly

// for limiting the speed at which the game runs.
// May or may not be used at this point.
using namespace std::chrono;

int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PONG");

	// the ball
	sf::RectangleShape ball(sf::Vector2f(BALL_WIDTH, BALL_HEIGHT));
	ball.rotate(45);
	ball.setFillColor(sf::Color::White);
	ball.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	sf::FloatRect ballBoundingBox;
	float ballVelocityX = BALL_VELOCITY;
	float ballVelocityY = BALL_VELOCITY;

	// The paddles
	sf::RectangleShape player1(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
	player1.setFillColor(sf::Color::White);
	sf::RectangleShape player2(sf::Vector2f(PADDLE_WIDTH, PADDLE_HEIGHT));
	player2.setFillColor(sf::Color::White);
	player1.setPosition(20, 100);
	player2.setPosition(WINDOW_WIDTH - 20 - PADDLE_WIDTH, 100);
	sf::FloatRect player1BoundingBox;
	sf::FloatRect player2BoundingBox;

	
	/*

	-----MainLoop----- TODO: add an update and draw method to make this prettier
	
	*/

	// time_point<system_clock> t;
	while (window.isOpen())
	{
		// t = system_clock::now();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//update everything
		// player movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			player1.move(0, -PADDLE_VELOCITY);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			player1.move(0, PADDLE_VELOCITY);
		}

		// Computer paddle movement
		if (player2.getPosition().y + (PADDLE_HEIGHT / 2) < ball.getPosition().y) {
			// move the paddle DOWN
			player2.move(0, PADDLE_VELOCITY);
		}
		if (player2.getPosition().y + (PADDLE_HEIGHT / 2) > ball.getPosition().y) {
			// move the paddle UP
			player2.move(0, -PADDLE_VELOCITY);
		}

		//ball
		ball.move(ballVelocityX, ballVelocityY);

		// Collision checks
		// update the bounding boxes
		ballBoundingBox = ball.getGlobalBounds();
		player1BoundingBox = player1.getGlobalBounds();
		player2BoundingBox = player2.getGlobalBounds();

		// check if the ball has touched either the top or bottom of the display
		if (ball.getPosition().y < 0 || ball.getPosition().y > WINDOW_HEIGHT) {
			ballVelocityY = -ballVelocityY;
		}

		// now check if any of the BoundingBoxes are intersecting and perform 
		// the necessary action(s) if they are.
		if (ballBoundingBox.intersects(player1BoundingBox) || ballBoundingBox.intersects(player2BoundingBox)) {
			ballVelocityX = -ballVelocityX;
		}

		// draw everything
		window.clear();
		window.draw(ball);
		window.draw(player1);
		window.draw(player2);
		window.display();

		// t += milliseconds(33);
		// std::this_thread::sleep_until(t);
	}

	return 0;
}