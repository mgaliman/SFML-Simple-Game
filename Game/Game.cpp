#include "Game.h"

void Game::initVariables()
{
	endGame = false;
	pauseGame = false;
	spawnTimerMax = 10.f;
	spawnTimer = spawnTimerMax;
	maxEnemies = 10;
	points = 0;
}

void Game::initWindow()
{
	//Windsow Size & FPS
	window = new RenderWindow(VideoMode(800,600) , "SPA_PROJ_001_CUSTOM_GAME", Style::Close | Style::Titlebar);
	window->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (!font.loadFromFile("Fonts/PixellettersFull.ttf"))
		cout << "ERROR::GAME::INITFONTS::COUL NOT LOAD PixellettersFull.ttf\n";
}

void Game::initText()
{
	//Gui text init
	guiText.setFont(font);
	guiText.setFillColor(Color::Yellow);
	guiText.setCharacterSize(32);

	//Info text init
	infoText.setFont(font);
	infoText.setFillColor(Color::Yellow);
	infoText.setCharacterSize(32);

	//Pause game text
	pauseGameText.setFont(font);
	pauseGameText.setFillColor(Color::Magenta);
	pauseGameText.setCharacterSize(80);
	pauseGameText.setPosition(190, 220);
	pauseGameText.setString("GAME PAUSED!");

	//End game text
	endGameText.setFont(font);
	endGameText.setFillColor(Color::Red);
	endGameText.setCharacterSize(160);
	endGameText.setPosition(50, 150);
	endGameText.setString("GAME OVER!");

	//Restart text
	restartText.setFont(font);
	restartText.setFillColor(Color::Red);
	restartText.setCharacterSize(50);
	restartText.setPosition(170, 300);
	restartText.setString("PRESS ENTER TO RESTART");
}

void Game::initAudio()
{
	if(!music.openFromFile("Audio/Soundtrack.wav"))
		cout << "ERROR::GAME::INITAUDIO::COULD NOT LOAD Soundtrack.wav\n";
	if(!kill.loadFromFile("Audio/Kill.wav"))
		cout << "ERROR::GAME::INITAUDIO::COULD NOT LOAD Kill.wav\n";
	if(!heal.loadFromFile("Audio/Heal.wav"))
		cout << "ERROR::GAME::INITAUDIO::COULD NOT LOAD Heal.wav\n";
	if(!hurt.loadFromFile("Audio/Hurt.wav"))
		cout << "ERROR::GAME::INITAUDIO::COULD NOT LOAD Hurt.wav\n";
	if(!gameOver.loadFromFile("Audio/GameOver.wav"))
		cout << "ERROR::GAME::INITAUDIO::COULD NOT LOAD GameOver.wav\n";
}

void Game::initWorld()
{
	if (!worldBackgroundText.loadFromFile("Textures/background.jpg"))
		cout << "ERROR::GAME::INITWORLD::COULD NOT LOAD background.jpg\n";

	worldBackground.setTexture(worldBackgroundText);
}

void Game::restart()
{
	delete window;
	Game restart;
	restart.run();
}

//Constructors and destructors
Game::Game()
{
	//Starting up the engine
	initVariables();
	initWindow();
	initFonts();
	initText();
	initAudio();
	music.play();
	music.setLoop(true);
	initWorld();
}

Game::~Game()
{
	//Clearing memory
	delete window;
}

void Game::run()
{
	//Game Loop
	while (window->isOpen())
	{
		update();
		render();
	}
	updateHighScore();
	updateHistogram();
}

bool& Game::getEndGame()
{
	return endGame;
}

//Functions
bool Game::running()
{
	return window->isOpen();
}

void Game::pollEvents()
{
	Event e;
	while (window->pollEvent(e))
	{
		//Exit
		if (e.Event::type == Event::Closed || e.Event::key.code == Keyboard::Escape)
			window->close();

		//Pause
		if (e.Event::key.code == Keyboard::P)
			pauseGame = true;
		
		if (e.Event::key.code == Keyboard::R)
			pauseGame = false;

		//Restart
		if (endGame && e.Event::key.code == Keyboard::Enter)
			restart();
	}
}

void Game::spawnEnemies()
{
	//Timer for spawning enemies
	if (spawnTimer < spawnTimerMax)
		spawnTimer += 1.f;
	else
	{
		//Spawn enemy
		if (enemies.size() < maxEnemies)
		{
			enemies.push_back(Enemy(*window, randBallType()));

			spawnTimer = 0.f;
		}
	}
}

//Getting random balls
int Game::randBallType()
{
	//Default color
	int type = 0;

	//Random collor ball
	int randValue = rand() % 100 + 1;
	if (randValue > 60 && randValue <= 80)
		type = 1;
	else if (randValue > 80 && randValue <= 100)
		type = 2;

	return type;
}

void Game::updatePlayer()
{
	player.update(window);

	//If player dies
	if (player.getHp() <= 0)
	{
		music.stop();
		endGame = true;
		sound.setBuffer(gameOver);
		sound.play();
	}
}

void Game::updateCollision()
{
	//Check the collision
	for (int i = 0; i < enemies.size(); i++)
	{
		if (player.getShape().getGlobalBounds().intersects(enemies[i].getShape().getGlobalBounds()))
		{
			switch (enemies[i].getType())
			{
			case 0:	//Add points
				points++;
				sound.setBuffer(kill);
				sound.play();
				break;
			case 1:	//Lose health
				player.takeDamage(2);
				sound.setBuffer(hurt);
				sound.play();
				break;
			case 2:	//Gain health
				player.gainhealth(1);
				sound.setBuffer(heal);
				sound.play();
				break;
			}
			//Remove the ball
			enemies.erase(enemies.begin() + i);
		}
	}
}

void Game::updateHighScore()
{
	//Setting high score

	auto begin = high_resolution_clock::now();

	ifstream in("HighScore.bin", ios::in | ios::binary);
	if (!in)
		cout << "ERROR::GAME::UPDATEHIGHSCORE HighScore.bin" << endl;
	int score;
	in >> score;
	in.close();

	auto end = high_resolution_clock::now();

	cout << "\nHighScore.bin loading time in microseconds: " << duration_cast<chrono::microseconds>(end - begin).count() << " us" << endl;

	if (points > score)
	{
		ofstream out("HighScore.bin");
		if (!out)
			cout << "ERROR::GAME::UPDATEHIGHSCORE HighScore.bin" << endl;
		out << points;
		out.close();
	}
}

void Game::updateHistogram()
{
	auto begin = high_resolution_clock::now();

	ifstream in("Histogram.bin", ios::in | ios::binary);
	list<int> histogramScores;
	int n;
	while (in >> n)
	{
		histogramScores.push_back(n);
	}
	in.close();

	auto end = high_resolution_clock::now();

	cout << "Histogram.bin loading time in microseconds: " << duration_cast<chrono::microseconds>(end - begin).count() << " us" << endl;

	histogramScores.push_front(points);

	ofstream out("Histogram.bin", ios::out | ios::binary);
	int a = 1;
	for (auto it = histogramScores.begin(); it != histogramScores.end(); ++it)
	{
		out << *it << endl;
	}
	out.close();

	cout << endl << "SCORE HISTOGRAM:\n";
	for (auto it = histogramScores.rbegin(); it != histogramScores.rend(); ++it)
	{
		cout << a++ << ". score: ";

		int length = static_cast<int>(*it);
		for (int i = 0; i < length; i++)
			cout << '#';
		if(length <= 1)
		cout << " ( " << *it << " enemy )" << endl;
		else
		cout << " ( " << *it << " enemies )" << endl;
	}
}

int Game::getHighScore()
{
	//Getting GUI HighScore
	ifstream HScore("HighScore.bin", ios::in | ios::binary);
	if (!HScore)
		cout << "ERROR::GAME::UPDATEHIGHSCORE HighScore.bin" << endl;
	int a;
	HScore >> a;
	return a;
}

void Game::updateGui()
{
	stringstream ss;
	ss
		<< " Points: " << points << endl
		<< " Health: " << player.getHp()
		<< " / " << player.getHpMax() << endl
		<< " High Score: " << getHighScore() <<endl;
	guiText.setString(ss.str());

	stringstream ps;
	ps << "PAUSE (P) \nRESUME (R) " ;
	infoText.setString(ps.str());
	infoText.setPosition(660, 0);

}

void Game::update()
{
	pollEvents();
	
	if (pauseGame)
	{
		//If paused return stops the loop
		music.setVolume(0);
		return;
	}
	else
	music.setVolume(100);


	if (endGame == false)
	{
		spawnEnemies();
		updatePlayer();
		updateCollision();
		updateGui();
	}
}

void Game::renderGui(RenderTarget* target)
{
	target->draw(guiText);
	target->draw(infoText);
}

void Game::renderWorld()
{
	window->draw(worldBackground);
}

void Game::render()
{
	//Clear every frame
	window->clear();

	//Draw world
	renderWorld();

	//Render stuff
	player.render(window);

	//Different type of for each, for rendering enemies
	for (auto i : enemies)
	{
		i.render(*window);
	}

	//Render gui
	renderGui(window);

	//Render pause text
	if (pauseGame)
		window->draw(pauseGameText);

	//Render end text
	if (endGame)
	{
		window->draw(endGameText);
		window->draw(restartText);
	}

	window->display();
}