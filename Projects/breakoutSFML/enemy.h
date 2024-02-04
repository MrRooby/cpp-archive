#pragma once

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <random>



class Enemy
{
protected:

	sf::RectangleShape hitbox_enemy; 
	const float enemyScale = 2.f;
	void initHitbox();

	const int hitboxSize = 27;

public:

	Enemy();
	~Enemy();

	bool devMODE = false;

	const sf::RectangleShape getHitbox() const;

	void renderHitbox( sf::RenderTarget& target );
};



class EnemyType :public Enemy
{
private:

	const std::string yellow = "assets/tab_yellow.png";
	const std::string blue = "assets/tab_blue.png";
	const std::string purple = "assets/tab_purple.png";

	sf::Sprite sprite_enemy;
	sf::Texture texture_enemy;

	void initSprite();
	void initTexture();

public:

	EnemyType( int x, int y );
	~EnemyType();

	int getRandomValue();

	void render( sf::RenderTarget& target );
};