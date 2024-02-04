#include "ball.h"


Ball::Ball()
{
	this->initTexture();
	this->initSprite();
}



Ball::~Ball()
{
}



///////////////////////////////////////////////////// FUNKCJE ////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


const sf::CircleShape Ball::getHitbox() const
{
	return this->hitbox_ball;
}



void Ball::operator++()
{
	this->moveSpeed++;
}



void Ball::death()
{
	this->sprite_ball.setPosition( start_x, start_y );
	this->hitbox_ball.setPosition( start_x, start_y );
	this->ballin = false;
}



void Ball::update()
{
	// ruch pi³ki po ekranie
	this->sprite_ball.move( moveSpeed * xV, moveSpeed * yV );
	this->hitbox_ball.move( moveSpeed * xV, moveSpeed * yV );

	// sprawdzanie kolizji ze œcian¹
	if( this->sprite_ball.getPosition().x <= 0 )
	{
		xV = -xV;
	}
	if( this->sprite_ball.getPosition().x >= 780  )
	{
		xV = -xV;
	}
	if( this->sprite_ball.getPosition().y <= 0 )
	{
		yV = -yV;
	}
	if( this->sprite_ball.getPosition().y >= 570 )
	{
		// utrata punktu ¿ycia
		HP--;
		std::cout << "HEALTH POINT LOST!   HP: " << HP << std::endl;
		
		ballin = false;
		yV = 0.f;
		xV = 0.f;
		this->sprite_ball.setPosition( start_x, start_y );
		this->hitbox_ball.setPosition( start_x, start_y );
		noCheating = true;
	}
}
 


void Ball::initTexture()
{
	//³adujemy texturê z pliku
	this->texture_ball.loadFromFile( "assets/ball.png" );
}



void Ball::initSprite()
{
	//ustawiamy texturê dla spritea
	this->sprite_ball.setTexture( this->texture_ball );

	//ustawienie wielkoœci i pozycji na ekranie, gracza
	this->sprite_ball.scale( ball_scale, ball_scale );
	this->sprite_ball.setPosition( start_x, start_y );
	
	// ustawianie niewidzialnego Hitboxa gracza w celu ³atwego wykrycia kolizji
	// hitbox jest skalowany na wymiar textury gracza
	this->hitbox_ball.setRadius( this->texture_ball.getSize().y * ball_scale/2 );
	this->hitbox_ball.setPosition( start_x, start_y );
	this->hitbox_ball.setFillColor( sf::Color::White );
}



void Ball::render( sf::RenderTarget& target )
{
 	target.draw( this->sprite_ball );

	if( devMODE == true )
	{
		target.draw( this->hitbox_ball );
	}
}