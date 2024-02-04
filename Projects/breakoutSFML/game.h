#pragma once
#include "paddle.h"
#include "ball.h"
#include "enemy.h"
#include "UI.h"

#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>


class GAME
{
private:
	
	sf::RenderWindow* window;
	sf::Clock clock;
	sf::Time elapsed;
	sf::Sprite sprite_window;
	sf::Texture texture_window;

	const int resW = 800;
	const int resH = 600;
	

	bool isrunning = false;

	bool DEV = false;
	
	bool ImGoingInsane = true;
	
	bool LVL1 = true;
	bool LVL2 = true;
	bool WIN = false;

	bool saved = false;
			
	float timeIsRelative = 0;

	std::string fileName = "HIGHSCORE.txt";

	std::ifstream readFile;


	UI* ui;
	Paddle* paddle;
	Ball* ball;
	EnemyType* enemyType;
	std::vector<EnemyType*> enemiesType;

	List* list;

	float RTC( float current );

	void initWindow();
	void initPlayer();
	void initUI();

public:

	GAME();
	~GAME();

	float tempTime;

	void run();

	void collisionPaddle();
	void updateEnemies();
	void collisionEnemy();

	int numEnemies();

	void DEVmode();

	void update();
	void render();

};