#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 512
#define PADDLE_WIDTH 8
#define PADDLE_HEIGHT 112
#define PADDLE_VELOCITY .04

// TODO: Experiment with these values to find the best ones.
#define BALL_WIDTH 10
#define BALL_HEIGHT 10
#define BALL_VELOCITY 0.06 // still working out what this should be exactly

void resetGame(sf::RectangleShape& ball);

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

	Player player1 = Player(PADDLE_WIDTH, PADDLE_HEIGHT, 20, 100, WINDOW_WIDTH, false);
	Player player2 = Player(PADDLE_WIDTH, PADDLE_HEIGHT, WINDOW_WIDTH - 20 - PADDLE_WIDTH, 100, WINDOW_WIDTH, true);

	bool reset = false;

	// load the font used for rendering the scoreText
	sf::Font font;
	if (!font.loadFromFile("Assets/PressStart2P.ttf"))
	{
		// error loading font
		std::cout << "Error reading font file." << std::endl;
	}

	// text to hold the scores
	sf::Text player1ScoreText, player2ScoreText;
	player1ScoreText.setFont(font);
	player1ScoreText.setString("0");
	player1ScoreText.setCharacterSize(50);
	player1ScoreText.setColor(sf::Color::White);
	player1ScoreText.setPosition(WINDOW_WIDTH / 4, 0);

	player2ScoreText.setFont(font);
	player2ScoreText.setString("0");
	player2ScoreText.setCharacterSize(50);
	player2ScoreText.setColor(sf::Color::White);
	player2ScoreText.setPosition((WINDOW_WIDTH / 4 + WINDOW_WIDTH / 2), 0);

	// -----MainLoop----- TODO: add an update and draw method to make this prettier

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//update everything
		player1.update(PADDLE_VELOCITY, &ball);
		player2.update(PADDLE_VELOCITY, &ball);

		//ball
		ball.move(ballVelocityX, ballVelocityY);

		// Collision checks
		// update the bounding boxes
		ballBoundingBox = ball.getGlobalBounds();

		// check if the ball has touched either the top or bottom of the display
		if (ball.getPosition().y < 0 || ball.getPosition().y > WINDOW_HEIGHT)
		{
			ballVelocityY = -ballVelocityY;
		}

		// now check if any of the BoundingBoxes are intersecting and perform 
		// the necessary action(s) if they are.
		if (ballBoundingBox.intersects(player1.getBoundingBox()) || ballBoundingBox.intersects(player2.getBoundingBox()))
		{
			ballVelocityX = -ballVelocityX;
		}

		// TODO: Check for victory condition here and keep track of the scores

		// Check if player won
		if (ball.getPosition().x >= WINDOW_WIDTH)
		{
			player1.setScore(player1.getScore() + 1);
			reset = true;
			player1ScoreText.setString(std::to_string(player1.getScore()));
		}

		// Check if computer won
		if (ball.getPosition().x <= 0)
		{
			player2.setScore(player2.getScore() + 1);
			reset = true;
			player2ScoreText.setString(std::to_string(player2.getScore()));
		}

		// draw everything
		window.clear();
		window.draw(ball);
		window.draw(player1);
		window.draw(player2);
		window.draw(player1ScoreText);
		window.draw(player2ScoreText);
		window.display();


		if (reset)
		{
			resetGame(ball);
			reset = false;
		}
	}

	return 0;
}

void resetGame(sf::RectangleShape& ball)
{
	sf::sleep(sf::seconds(2));
	ball.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}
