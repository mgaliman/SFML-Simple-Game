#include "Player.h"

void Player::initVariables()
{
	movementSpeed = 5.f;
	hpMax = 10;
	hp = hpMax;
}

void Player::initShape()
{
	shape.setFillColor(Color::Green);
	this->shape.setSize(Vector2f(50.f, 50.f));
}

Player::Player(float x, float y)
{
	shape.setPosition(x, y);

	initVariables();
	initShape();
}

Player::~Player()
{

}

//Accessors
const RectangleShape& Player::getShape() const
{
	return shape;
}

const int& Player::getHp() const
{
	return hp;
}

const int& Player::getHpMax() const
{
	return hpMax;
}

//Functions
void Player::takeDamage(const int damage)
{
	if (hp > 0)
		hp -= damage;

	if (hp < 0)
		hp = 0;
}

void Player::gainhealth(const int health)
{
	if (hp < hpMax)
		hp += health;

	if (hp > hpMax)
		hp = hpMax;
}

void Player::updateInput()
{
	//Keyboard input
	//Left
	if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::Left))
		shape.move(-movementSpeed, 0.f);
	//Right
	else if (Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Right))
		shape.move(movementSpeed, 0.f);
	//Up
	if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
		shape.move(0.f, -movementSpeed);
	//Down
	else if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
		shape.move(0.f, movementSpeed);
}

void Player::updateWindowsBoundsCollision(const RenderTarget* target)
{
	//Left
	if (shape.getGlobalBounds().left <= 0.f)
		shape.setPosition(0.f, shape.getGlobalBounds().top);
	//Right
	if (shape.getGlobalBounds().left + shape.getGlobalBounds().width >= target->getSize().x)
		shape.setPosition(target->getSize().x - shape.getGlobalBounds().width, shape.getGlobalBounds().top);
	//Top
	if (shape.getGlobalBounds().top <= 0.f)
		shape.setPosition(shape.getGlobalBounds().left, 0.f);
	//Bottom
	if (shape.getGlobalBounds().top + shape.getGlobalBounds().height >= target->getSize().y)
		shape.setPosition(shape.getGlobalBounds().left, target->getSize().y - shape.getGlobalBounds().height);
}

void Player::update(const RenderTarget* target)
{
	updateInput();

	//Window bounds collision
	updateWindowsBoundsCollision(target);
}

void Player::render(RenderTarget* target)
{
	target->draw(shape);
}
