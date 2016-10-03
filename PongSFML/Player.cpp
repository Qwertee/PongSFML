#include "Player.h"
#include <iostream>


Player::Player(int width, int height, float x, float y, float windowWidth, bool isAI)
{
	this->width = width;
	this->height = height;
	this->position.x = x;
	this->position.y = y;
	this->isAI = isAI;
	paddle.setFillColor(sf::Color::White);
	paddle.setSize(sf::Vector2f(width, height));
	paddle.setPosition(this->position.x, this->position.y);

	// set the font for rendering the scoreText
	sf::Font font;
	if (!font.loadFromFile("Assets/PressStart2P.ttf"))
	{
		// error loading font
		std::cout << "Error reading font file." << std::endl;
	}

	// set the scoreText text to the appropriate values
	scoreText.setFont(font);
	scoreText.setCharacterSize(50);
	scoreText.setColor(sf::Color::White);
	scoreText.setString("0");
	// set the position of the text
	if (!isAI)
	{
		// if player the human player (left)
		scoreText.setPosition(windowWidth / 4, 0);
	}
	else
	{
		// if the player is the computer (right)
		scoreText.setPosition((windowWidth / 4 + windowWidth / 2), 0);
	}
}

// updates the position of the player
void Player::setPosition(float x, float y)
{
	this->position.x = x;
	this->position.y = y;
}

void Player::setScore(int score)
{
	this->scoreText.setString(std::to_string(score));
}

int Player::getScore()
{
	return std::stoi(this->scoreText.getString().toAnsiString());
}

void Player::update(float velocity, sf::RectangleShape* ball)
{
	// update the player's position
	// first the human player
	if (!this->isAI)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			paddle.move(0, -velocity);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			paddle.move(0, velocity);
		}
	}
	else
	{
		// now the computer
		if (paddle.getPosition().y + (height / 2) < ball->getPosition().y)
		{
			// move the paddle DOWN
			paddle.move(0, velocity);
		}
		if (paddle.getPosition().y + (height / 2) > ball->getPosition().y)
		{
			// move the paddle UP
			paddle.move(0, -velocity);
		}
	}
	// update the bounding box for the paddles
	playerBoundingBox = paddle.getGlobalBounds();
}

sf::FloatRect& Player::getBoundingBox()
{
	return playerBoundingBox;
}

sf::RectangleShape Player::getRect()
{
	return paddle;
}

sf::Text Player::getScoreText()
{
	return scoreText;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(paddle, states);
}
