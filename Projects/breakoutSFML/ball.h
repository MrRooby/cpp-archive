 #pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Ball
{
private:

	sf::Sprite sprite_ball;
	sf::Texture texture_ball;
	sf::CircleShape hitbox_ball;
	
	const float ball_scale = 4.f;

	const float start_y = 470.f;
	const float start_x = 385.f;

	void initTexture();
	void initSprite();

public:

	Ball();
	~Ball();

	bool devMODE    = false;
	bool ballin     = false;
	bool noCheating = false;

	int moveSpeed = 3;

	float xV = 1.f;
	float yV = -1.f;

	int HP = 4;
	 
	const sf::CircleShape getHitbox() const;

	void operator++();

	void death();

	void update();
	void render( sf::RenderTarget& target );
};