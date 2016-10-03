#pragma once
#include <SFML/Graphics.hpp>

class Player : public sf::Drawable
{
public:
	Player(int width, int height, float x, float y, float windowWidth, bool isAI);
	void setPosition(float x, float y);
	void setScore(int score);
	int getScore();
	void update(float velocity, sf::RectangleShape* ball);
	sf::FloatRect& getBoundingBox();
	sf::RectangleShape getRect();
	sf::Text getScoreText();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	int width;
	int height;
	bool isAI;
	sf::RectangleShape paddle;
	sf::FloatRect playerBoundingBox;
	sf::Vector2f position;
	sf::Text scoreText;
};
