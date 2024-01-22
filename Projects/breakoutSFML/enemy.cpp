#include "enemy.h"


Enemy::Enemy()
{
}



Enemy::~Enemy()
{
}



const sf::RectangleShape Enemy::getHitbox() const
{
	return this->hitbox_enemy;
}



void Enemy::initHitbox()
{
	this->hitbox_enemy.setSize( sf::Vector2f( hitboxSize * enemyScale, hitboxSize * enemyScale ) );
	this->hitbox_enemy.setFillColor( sf::Color::Red );
}



void Enemy::renderHitbox( sf::RenderTarget& target )
{
	if( devMODE == true )
	{
		target.draw( this->hitbox_enemy );
	}
}



EnemyType::EnemyType( int x, int y )
{
	this->initTexture();
	this->initSprite();

	this->initHitbox();

	this->hitbox_enemy.setPosition( x, y );

	this->sprite_enemy.setPosition( x, y );
}



EnemyType::~EnemyType() {}



int EnemyType::getRandomValue()
{
	std::random_device rd;
	std::mt19937 gen( rd() );
	std::uniform_int_distribution<int> distribution( 1, 3 );
		return distribution( gen );
}



void EnemyType::initTexture()
{
	switch( getRandomValue() )
	{
	case 1:

		this->texture_enemy.loadFromFile( yellow );
		break;

	case 2:

		this->texture_enemy.loadFromFile( blue );
		break;

	case 3:

		this->texture_enemy.loadFromFile( purple );
		break;
	}
}



void EnemyType::initSprite()
{
	this->sprite_enemy.setTexture( this->texture_enemy );
	this->sprite_enemy.scale( enemyScale, enemyScale );

	this->hitbox_enemy.setSize( sf::Vector2f( this->texture_enemy.getSize().x * enemyScale, this->texture_enemy.getSize().y * enemyScale ) );
	this->hitbox_enemy.setFillColor( sf::Color::Red );
}


void EnemyType::render( sf::RenderTarget& target )
{
	target.draw( this->sprite_enemy );
}
