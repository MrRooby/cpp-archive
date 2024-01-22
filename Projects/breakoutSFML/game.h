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
	
	sf::RenderWindow* window;	// ³atwiej u¿ywaæ okna gdy jest pointer'em (zmiany itd.)
	sf::Clock clock;
	sf::Time elapsed;
	

	bool isrunning = false;

	bool DEV = false;			// Opcja pozwalaj¹ca wyœwietliæ hitbox'y elementów na ekranie (u¿yteczne przy debugowaniu)
	
	bool ImGoingInsane = true;	// zabezpieczenie przed naliczaniem siê punktów w nieskoñczonoœæ
	
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