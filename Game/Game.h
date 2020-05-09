#pragma once

#include<iostream>
#include<fstream>
#include<sstream>
#include<ctime>
#include<vector>
#include<list>
#include<chrono>

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>

#include "Player.h"
#include "Enemy.h"

using namespace chrono;

class Game
{
private:
	RenderWindow* window;
	bool endGame;
	bool pauseGame;

	Player player;

	int points;

	//World
	Texture worldBackgroundText;
	Sprite worldBackground;

	//Text
	Font font;
	Text guiText;
	Text infoText;
	Text endGameText;
	Text restartText;
	Text pauseGameText;

	//Audio
	SoundBuffer kill;
	SoundBuffer heal;
	SoundBuffer hurt;
	SoundBuffer gameOver;
	Sound sound;
	Music music;

	//Enemies
	vector<Enemy> enemies;
	float spawnTimerMax;
	float spawnTimer;
	int maxEnemies;

	//Private Functions
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
	void initAudio();
	void initWorld();
	void restart();

public:
	//Constructors and destructors
	Game();
	~Game();

	void run();

	//Accessors
	bool& getEndGame();

	//Functions
	bool running();
	void pollEvents();


	void spawnEnemies();
	int randBallType();
	void updatePlayer();
	void updateCollision();
	void updateHighScore();
	void updateHistogram();
	int getHighScore();
	void updateGui();
	void update();

	void renderGui(RenderTarget* target);
	void renderWorld();
	void render();
};

