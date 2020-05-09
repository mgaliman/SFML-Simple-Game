#pragma once

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

using namespace std;
using namespace sf;

class Enemy
{
private:
	CircleShape shape;
	int type;

	void initShape(const RenderWindow& window);

public:
	Enemy(const RenderWindow& window, int type);
	~Enemy();

	//Accessor
	const CircleShape getShape() const;
	const int& getType() const;

	//Functions
	void render(RenderTarget& target);
};