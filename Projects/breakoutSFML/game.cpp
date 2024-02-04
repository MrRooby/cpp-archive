#include "game.h"
#include <iostream>


void GAME::initWindow()
{
	this->window = new sf::RenderWindow( sf::VideoMode( resW, resH ), "BREAKOUT", sf::Style::Close | sf::Style::Titlebar );
	this->texture_window.loadFromFile("assets/background.png");
	this->sprite_window.setTexture(this->texture_window);
	this->window->setFramerateLimit( 60 );
}



void GAME::initUI()
{
	this->ui = new UI();	
	this->list = new List();
}



void GAME::initPlayer()
{
	this->paddle = new Paddle();
	this->ball   = new Ball();
}



GAME::GAME()												// inicjalizacja gry
{
	this->initWindow();
	std::cout << "[]  window initialised  []" << std::endl;
	this->initUI();
	std::cout << "[]    UI initialised    []" << std::endl;
	this->initPlayer();
	std::cout << "[]  player initialised  []" << std::endl;

	this->readFile.open( this->fileName );

	
	std::string line;

	while( std::getline( readFile, line ) )
	{
		std::string insertName;
		float tempScore;

		std::istringstream iss( line );
		if( iss >> tempScore )
		{
			this->list->insert( tempScore );
		}
	}
	this->readFile.close();
}



GAME::~GAME()
{
	delete this->window;
	delete this->paddle;
	delete this->ball;
	for( auto* n : this->enemiesType )
		delete n;
	delete this->list;
}



///////////////////////////////////////////////////// FUNKCJE ////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GAME::collisionPaddle()
{
	// kolizja z lew¹ stron¹ paletki
	if( this->paddle->getHitboxLEFT().getGlobalBounds().intersects( this->ball->getHitbox().getGlobalBounds() ) )
	{
		this->ball->yV = -1.f;
		this->ball->xV = -1.f;
	}

	// kolizja z praw¹ stron¹ paletki
	if( this->paddle->getHitboxRIGHT().getGlobalBounds().intersects( this->ball->getHitbox().getGlobalBounds() ) )
	{
		this->ball->yV = -1.f;
		this->ball->xV = 1.f;
	}
}


void GAME::updateEnemies()
{
	for( unsigned i = 0; i < 13; i++ )		// kolumny
	{
		for( unsigned n = 0; n < 4; n++ )   // wiersze
		{
			this->enemiesType.emplace_back( new EnemyType( i * 60 + 11, n * 60 + 11 ) );
		}
	}
}



void GAME::collisionEnemy()
{
	for( size_t i = 0; i < this->enemiesType.size(); i++ )
	{
		if( this->ball->getHitbox().getGlobalBounds().intersects( this->enemiesType[i]->getHitbox().getGlobalBounds() ) )
		{
			this->enemiesType.erase( this->enemiesType.begin() + i );
			this->ball->yV = -this->ball->yV;
			
			std::cout << "Enemies left: [" << this->enemiesType.size() <<"]" << std::endl;
		}
	}
}



int GAME::numEnemies()
{
	return this->enemiesType.size();
}



float GAME::RTC( float current )
{
	timeIsRelative = current + this->list->getScore();
	timeIsRelative = ceil( timeIsRelative * 100.f ) / 100.f;
	return timeIsRelative;
}



void GAME::DEVmode()
{
	if( DEV == true )
	{
		this->paddle->devMODE = true;
		this->ball->devMODE = true;
		for( size_t i = 0; i < this->enemiesType.size(); i++ )
		{
			this->enemiesType[ i ]->devMODE = true;
		}
	}
	else
	{
		this->paddle->devMODE = false;
		this->ball->devMODE = false;
		for( size_t i = 0; i < this->enemiesType.size(); i++ )
		{
			this->enemiesType[ i ]->devMODE = false;
		}		
	}
}



void GAME::run()
{
	this->updateEnemies();

	while( this->window->isOpen() )
	{
		this->update();
		this->render();
		isrunning = true;
	}

	if( WIN )
	{					
		this->list->insert( this->list->getScore() );		//zapis zaktualizowanej tabeli wyników do pliku .txt
		this->list->saveList( fileName );	
	}

	isrunning = false;
}



void GAME::update()
{
	sf::Event press;

	//zamykanie okna 
	while( this->window->pollEvent( press ) )
	{
		if( press.Event::type == sf::Event::Closed )
			this->window->close();
		if( press.Event::KeyPressed && press.Event::key.code == sf::Keyboard::Escape )
			this->window->close();
	}


	this->collisionPaddle();


	this->collisionEnemy();


	if( this->ball->ballin == true ) // funkcja zapewnia ¿e pi³ka porusza siê dopiero po naciœniêciu spacji
	{
		ImGoingInsane = true;
		this->ball->update();
		elapsed = this->clock.getElapsedTime();
	}
	else if( this->ball->ballin == false )
	{
		tempTime = elapsed.asSeconds();
		if( ImGoingInsane == true )
		{
			this->list->operator+( tempTime );
			ImGoingInsane = false;
		}
	}

	this->DEVmode();




	///////////////////////////////////////////////////// AKTUALIZACJA UI ///////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	this->ui->update( numEnemies(), this->ball->ballin, this->ball->HP, RTC( elapsed.asSeconds() ), this->list->getCurrentScore() );
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	// inicjacja ruchu pi³ki
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) && this->enemiesType.size() > 0 && this->ui->endGame == false ) // zabezpieczenie przed oszukiwaniem
	{
		this->ball->ballin = true;
		this->clock.restart();
		if( this->ball->noCheating == true )
		{
			this->ball->xV = 1.f;
			this->ball->yV = -1.f;
			this->ball->noCheating = false;
		}
	}


	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Q ) && this->DEV == true)   // mo¿liwoœæ usuniêcia wszystkich bloków w trybie DEV
	{
		this->enemiesType.clear();
	}


	//poruszanie graczem
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) && this->paddle->position() > 0 && this->ball->ballin == true ) // zabezpieczenie przed wyjechaniem poza okno
		this->paddle->movement( -1.f );
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) && this->paddle->position() < 672 && this->ball->ballin == true )
		this->paddle->movement( 1.f );


	if( this->ball->ballin == false ) // reset po³o¿enia paletki w przypadku œmierci
	{
		this->paddle->death();
	}


	// zwiêkszanie prêdkoœci pi³ki wraz z zmniejszaniem siê iloœci elementów
	if( this->enemiesType.size() <= 39 && LVL1 == true )
	{
		this->ball->operator++();
		std::cout << "speed:" << this->ball->moveSpeed << std::endl;
		LVL1 = false;
	}
	if( this->enemiesType.size() <= 13 && LVL2 == true )
	{
		this->ball->operator++();
		LVL2 = false;
	}


	// warunek zakoñczenia gry przez utratê ¿yæ
	if( this->ball->HP < 1 )		
	{
		this->ui->endGame = true;
		std::cout << "YOU LOST" << std::endl;
	}


	if( this->enemiesType.size() == 0 )
	{
		this->paddle->death();
		this->ball->death();
		this->WIN = true;
	}
}



void GAME::render()
{
	this->window->draw(sprite_window);
	
	this->ui->render( *this->window, this->enemiesType.size(), this->list->getCurrentScore() );
	
	this->paddle->render( *this->window );
	
	this->ball->render( *this->window );

	for( auto *enemyType : this->enemiesType )
	{
		enemyType->render( *this->window );
		enemyType->renderHitbox( *this->window );
	}




	/////////////////////////////////////////////////// DEBUG INFO /////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//std::cout << "vector size: " << this->enemies.size() << std::endl;

	//std::cout << "do we ballin?: " << this->ball->ballin << std::endl;

	//std::cout << "Paddle position:  [ " << this->paddle->position() << " ].x" << std::endl;

	//if( isrunning )
	//	std::cout << "GAME IS RUNNING" << std::endl;
	//else if( !isrunning )
	//	std::cout << "GAME IS NOT RUNNING" << std::endl;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	this->window->display();
}