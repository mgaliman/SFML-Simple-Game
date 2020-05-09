#pragma once

#include"Game.h"
#include<queue>

class State
{
private:
	int key;
	queue<int> leader;
	Clock clock;
	void loading();
	void loadSettings();
public:
	State();
	~State();
	void mainMenu();
	void startingMenu();
	void settingsMenu();
	void worldRecords();
	void creditsMenu();
	int exitMenu();
	void cmdStyleMenu();
};

