#include "UI.h"



List::List() : head( nullptr ) {}



List::~List()
{
	while( head )
	{
		Hierarchy* temp = head;
		head = head->next;
		delete temp;
	}
}



float List::getScore()
{
	return currentScore;
}



void List::insert( float newScore )
{
	currentIndex = 0;

	Hierarchy* newHierarchy = new Hierarchy;
	newHierarchy->score = newScore;
	newHierarchy->next = nullptr;

	if( head == nullptr || newScore < head->score )
	{
		newHierarchy->next = head;
		head = newHierarchy;
		return;
	}

	Hierarchy* current = head;


	while( current->next != nullptr && current->next->score < newScore )
	{
		current = current->next;
		currentIndex++;
	}

	newHierarchy->next = current->next;
	current->next = newHierarchy;
}



void List::saveList( const std::string& fileName )
{
	std::ofstream writeFile;
	writeFile.open( fileName );

	Hierarchy* current = head;

	while( current != nullptr )
	{
		writeFile <<  current->score << std::endl;
		current = current->next;
	}
	
	writeFile.close();
}



void List::operator+( float elapsed )
{
	this->currentScore += elapsed;
}



std::pair<int, float> List::getCurrentScore()
{
	int i = 0;
	Hierarchy* current = head;

	if( !current || currentScore < current->score )
	{
		return std::make_pair( ++i, currentScore );
		std::cout << "[" << i << "] " << currentScore << std::endl;
	}


	while( current->next != nullptr && current->next->score < currentScore )
	{
		current = current->next;
		i++;
	}

	std::cout << "[" << i << "] " << currentScore << std::endl;
	return std::make_pair( i + 2, this->currentScore );
} 



UI::UI()
{
	this->initFont();
	this->initText();
}



UI::~UI()
{
}



void UI::initFont()
{
	this->font.loadFromFile( "assets/dogica.ttf" );
}



void UI::initText()
{
	this->UItext.setFont( this->font );
	this->UItext.setFillColor( sf::Color::White );
	this->UItext.setCharacterSize( 20 );
	this->UItext.setPosition( 5.f, 575.f );

	this->ENDtext.setFont( this->font );
	this->ENDtext.setFillColor( sf::Color::Red );
	this->ENDtext.setCharacterSize( 30 );
	this->ENDtext.setPosition( 200, 300 );

	this->WINtext.setFont( this->font );
	this->WINtext.setFillColor( sf::Color::Green );
	this->WINtext.setCharacterSize( 30 );
	this->WINtext.setPosition( 250, 300 );

	this->HIGHSCOREtext.setFont( this->font );
	this->HIGHSCOREtext.setFillColor( sf::Color::Yellow );
	this->HIGHSCOREtext.setCharacterSize( 30 );
	this->HIGHSCOREtext.setPosition( 120, 50 );

	this->LEADERBOARDtext.setFont( this->font );
	this->LEADERBOARDtext.setFillColor( sf::Color::White );
	this->LEADERBOARDtext.setCharacterSize( 30 );
	this->LEADERBOARDtext.setPosition( 250, 50 );
}



void UI::update( int numEnemies, bool ballin, int HP, float time, std::pair<int, float> myScore )
{
	std::stringstream bottom;
	bottom << "HP[" << HP << "] ";
	if( !ballin && numEnemies > 0 )
	{
		bottom << "PRESS [SPACE] TO LAUNCH TANGERINE";
	}
	else if( ballin )
		bottom << "       SCORE[" << time << "]";

	this->UItext.setString( bottom.str() );

	std::stringstream loss;
	loss << "LUCY IS GONE!" << std::endl;
	loss << "\n PRESS [ESC]";
	this->ENDtext.setString( loss.str() );

	std::stringstream EPIC_VICTORY;
	EPIC_VICTORY << " YOU WIN!" << std::endl;
	EPIC_VICTORY << "\nPRESS [ESC]";
	this->WINtext.setString( EPIC_VICTORY.str() );

	std::stringstream HIGHSCORE;
	HIGHSCORE << "!!!NEW HIGHSCORE!!!" <<  std::endl;
	HIGHSCORE << "\n  [" << myScore.second << "s]";
	this->HIGHSCOREtext.setString( HIGHSCORE.str() );

	std::stringstream leaderboard;
	std::string grammar;
	leaderboard << " GOOD JOB" << std::endl;

	if( myScore.first == 2 )
		grammar = "nd";
	else if( myScore.first == 3 )
		grammar = "rd";
	else if( myScore.first > 3 )
		grammar = "th";
	
	leaderboard << "\nYou're " << myScore.first << grammar << "\n\n[" << myScore.second << "s]";
	this->LEADERBOARDtext.setString( leaderboard.str() );
}



void UI::render( sf::RenderTarget& target, int numEnemies, std::pair<int, float> yourPAIR )
{
	target.draw( this->UItext );

	if( this->endGame == true )
	{
		target.draw( this->ENDtext );
	}

	if( numEnemies <= 0 )
	{
		target.draw( this->WINtext );
	}

	if( yourPAIR.first == 1 && numEnemies <= 0 )
	{
		target.draw( this->HIGHSCOREtext );
	}
	else if( numEnemies <= 0 && yourPAIR.first <= 10 )
	{
		target.draw( this->LEADERBOARDtext );
	}
}


