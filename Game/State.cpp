#include "State.h"

State::State()
{
	mainMenu();
}

State::~State()
{
}

void State::loading()
{
	clock.restart();
	//Setting load screen to 5 sec
	while (clock.getElapsedTime().asSeconds() <= 5)
	{
		cout << "LOADING...";
		system("cls");
	}
	cout << "LOADING FINISHED" << endl;
}

void State::loadSettings()
{
	//Loading from file settings
	ifstream in("Settings.bin",ios::in | ios::binary);
	if (!in)
		cout << "ERROR::STATE:LOADSETTINGS Settings.bin";

	int sett;
	in >> sett;
	if (sett == 1)
		system("color 07");

	else if(sett == 2)
		system("color 14");

	else if(sett == 3)
		system("color 72");
	in.close();
}

void State::mainMenu()
{
	loadSettings();
	system("cls");
	cout << "HELLO! WELCOME TO MAIN MENU!\n\nPress desired key (Press ENTER after):\n [1] START\n [2] SETTING\n [3] WORLD REACORDS\n [4] CREDITS\n [5] EXIT\n";
	cin >> key;

	if (key == 1)
		startingMenu();
	else if (key == 2)
		settingsMenu();
	else if (key == 3)
		worldRecords();
	else if (key == 4)
		creditsMenu();
	else if (key == 5)
		exitMenu();	
}

void State::startingMenu()
{
	system("cls");

	loading();

	//Init game
	Game game;

	//Game loop
	game.run();
}

void State::settingsMenu()
{
	system("cls");
	cout << "SETTINGS\n\nPress desired key (Press ENTER after):\n [1] CMD STYLE\n [2] BACK\n [3] EXIT\n";
	cin >> key;

	if (key==1)
		cmdStyleMenu();
	else if(key==2)
		mainMenu();
	else if(key==3)
		exitMenu();
}

void State::worldRecords()
{
	system("cls");
	cout << "WORLD REACORDS\n\n";

	auto begin = high_resolution_clock::now();

	ifstream in("Leaderboard.bin", ios::in | ios::binary);
	if (!in)
		cout << "ERROR::STATE::WORLDREACORDS Leaderbord.txt";
	int num;
	while (in >> num)
	{
		leader.push(num);
	}
	in.close();
	auto end = high_resolution_clock::now();

	vector<string> GOJ{ "GALIMAN", "OBAMA" ,"JESUS" };
	int goj = 0;
	while (!leader.empty())
	{
		cout << GOJ[goj++] << "\t" << leader.front() << endl;
		leader.pop();
	}
	cout << endl;

	in.close();
	cout<< "Leaderboard.bin loading time in microseconds: " << duration_cast<chrono::microseconds>(end - begin).count() << " us";
	cout << "\nPress desired key (Press ENTER after): {\n [1] BACK\n [2] EXIT\n";
	cin >> key;
	if (key == 1)
		mainMenu();
	else if (key == 2)
		exitMenu();
}

void State::creditsMenu()
{
	system("cls");
	cout << "CREDITS\n\nMarko Galiman \nProgrammer at Algebra University \nFrom Rovinj \n:)\n\nPress desired key (Press ENTER after):\n [1] BACK\n [2] EXIT\n";
	cin >> key;

	if (key == 1)
	mainMenu();
	else if (key == 2)
	exitMenu();
}

int State::exitMenu()
{
	system("cls");
	cout << "You've exited the game.\n\nPRESS ANY BUTTON TO CLOSE THE WINDOW\n";
	return 1;
}

void State::cmdStyleMenu()
{
	system("cls");
	cout << "BACKGOUND COLOR\n\nPress desired key (Press ENTER after):\n [1] BLACK & WHITE\n [2] BLUE & RED \n [3] WHITE & GREEN\n [4] BACK\n";
	cin >> key;

	ofstream out("Settings.bin", ios::out | ios::binary);
	if (!out)
		cout << "ERROR::STATE::BACKGOUNDCOLORMENU Setting.bin";

	if (key == 1)
	{
		system("color 07");
		out << 1;
		cmdStyleMenu();
	}
	else if (key == 2)
	{		
		system("color 14");
		out << 2;
		cmdStyleMenu();
	}
	else if (key == 3)
	{
		system("color 72");
		out << 3;
		cmdStyleMenu();
	}
	else if (key == 4)
		settingsMenu();

	out.close();
}