#include "Enemy.h"

void Enemy::initShape(const RenderWindow& window)
{
	shape.setRadius(20);
	Color color;
	switch (type)
	{
	case 0:
		color = Color::Blue;
		break;
	case 1:
		color = Color::Red;
		break;
	case 2:
		color = Color::Green;
		break;
	}
	shape.setFillColor(color);
	//Randomize position of balls 
	shape.setPosition(Vector2f(
		static_cast<float>(rand() % window.getSize().x - shape.getGlobalBounds().width),
		static_cast<float>(rand() % window.getSize().y - shape.getGlobalBounds().height)));
}

Enemy::Enemy(const RenderWindow& window, int type) : type(type)
{
	initShape(window);
}

Enemy::~Enemy()
{
}

const CircleShape Enemy::getShape() const
{
	return shape;
}

const int& Enemy::getType() const
{
	return type;
}

void Enemy::render(RenderTarget& target)
{
	target.draw(shape);
}
