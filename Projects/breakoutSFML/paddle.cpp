#include "paddle.h"


Paddle::Paddle()
{
	this->initTexture();
	this->initSprite();
}

Paddle::~Paddle()
{
}

const sf::RectangleShape Paddle::getHitboxLEFT() const
{
	return this->hitbox_paddle_LEFT;
}


const sf::RectangleShape Paddle::getHitboxRIGHT() const
{
	return this->hitbox_paddle_RIGHT;
}


void Paddle::death()
{
	this->sprite_paddle.setPosition( 336.f, fixedHight );

	this->hitbox_paddle_RIGHT.setPosition( 401.f, fixedHight );
	this->hitbox_paddle_LEFT.setPosition( 336.f, fixedHight );
}

void Paddle::movement( float paddle_x )
{
	float speed = moveSpeed * paddle_x;
	this->sprite_paddle.move( speed, NULL );

	this->hitbox_paddle_LEFT.move( speed, NULL );
	this->hitbox_paddle_RIGHT.move( speed, NULL );
}

float Paddle::position()
{
	return this->sprite_paddle.getPosition().x;
}



//FUNKCJE GRACZA
void Paddle::update()
{
	
}

void Paddle::initTexture()
{
	//³adujemy texturê z pliku
	this->texture_paddle.loadFromFile( "assets/paddle.png" );
}


void Paddle::initSprite()
{
	// Ustawiamy texturê dla spritea
	this->sprite_paddle.setTexture( this->texture_paddle );

	// Ustawienie wielkoœci i pozycji na ekranie sprite'a gracza
	this->sprite_paddle.scale( paddleScale, paddleScale);
	this->sprite_paddle.setPosition( 336.f, fixedHight );

	// Ustawianie niewidzialnego Hitboxa gracza w celu ³atwego wykrycia kolizji
	// Jest skalowany na wymiar textury gracza

	// Hitbox:
	float hitboxWIDTH = this->texture_paddle.getSize().x / 3;

	// - Odbijaj¹cy na lewo
	this->hitbox_paddle_LEFT.setSize( sf::Vector2f( ( this->texture_paddle.getSize().x * paddleScale ) / 2, ( this->texture_paddle.getSize().y * paddleScale ) / 4 ) );
	this->hitbox_paddle_LEFT.setPosition( 336.f, fixedHight);
	this->hitbox_paddle_LEFT.setFillColor( sf::Color::Green );

	// - Odbijaj¹cy na prawo
	this->hitbox_paddle_RIGHT.setSize( sf::Vector2f( ( this->texture_paddle.getSize().x * paddleScale ) / 2, ( this->texture_paddle.getSize().y * paddleScale ) / 4 ) );
	this->hitbox_paddle_RIGHT.setPosition( 400.f, fixedHight );
	this->hitbox_paddle_RIGHT.setFillColor( sf::Color::Yellow );
}


void Paddle::render( sf::RenderTarget& target )
{
	target.draw( this->sprite_paddle );

	if( devMODE == true )
	{
		target.draw( this->hitbox_paddle_LEFT );
		target.draw( this->hitbox_paddle_RIGHT );
	}
}