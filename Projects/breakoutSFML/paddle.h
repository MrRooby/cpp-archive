#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Paddle
{
private:

	sf::Sprite sprite_paddle;
	sf::Texture texture_paddle;
	sf::RectangleShape hitbox_paddle_LEFT;
	sf::RectangleShape hitbox_paddle_RIGHT;

	const float fixedHight = 510.f;
	const float moveSpeed = 7.f;
	const float paddleScale = 4.f;

	void initTexture();
	void initSprite();

public:

	Paddle();
	~Paddle();

	bool devMODE = false;

	const sf::RectangleShape getHitboxLEFT() const;
	const sf::RectangleShape getHitboxRIGHT() const;
	
	void death();
	void movement( float paddle_x );
	float position();

	void update();
	void render( sf::RenderTarget& target );

};