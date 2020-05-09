#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

using namespace std;
using namespace sf;

class Player
{
private:
	RectangleShape shape;

	float movementSpeed;
	int hp;
	int hpMax;

	void initVariables();
	void initShape();
public:
	//Setting default position
	Player(float x = 0.f, float y = 0.f);
	~Player();

	//Accesors
	const RectangleShape& getShape() const;
	const int& getHp() const;
	const int& getHpMax() const;

	//Functions
	void takeDamage(const int damage);
	void gainhealth(const int health);

	void updateInput();
	void updateWindowsBoundsCollision(const RenderTarget* target);
	void update(const RenderTarget* target);
	void render(RenderTarget* target);
};

