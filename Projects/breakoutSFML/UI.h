#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <utility>
#include <string>



class List
{
protected:

	struct Hierarchy
	{
		float score;
		Hierarchy* next;
	};

	float currentScore = 0.f;
	int currentIndex = 0;

public:

	List();
	~List();

	Hierarchy* head;

	void operator+( float elapsed );

	std::pair< int, float > getCurrentScore();

	float getScore();

	void insert( float newScore );					// wpisywanie wyniku do listy

	void saveList( const std::string& fileName );	// zapisywanie wyników do pliku

};



class UI
{
private:
	
	sf::Font font;
	sf::Text UItext;
	sf::Text ENDtext;
	sf::Text WINtext;
	sf::Text HIGHSCOREtext;
	sf::Text LEADERBOARDtext;


	void initFont();
	void initText();

public:

	UI();
	~UI();

	float yourSCORE;
	bool endGame = false;

	void update( int numEnemies, bool ballin, int HP, float update, std::pair<int, float> yourPAIR );
	void render( sf::RenderTarget& target, int numEnemies, std::pair<int, float> yourPAIR );
};