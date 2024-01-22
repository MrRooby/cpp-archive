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

	const float start_y = 470.f;		// sta³e zmienne wyjœciowej pozycji pi³ki
	const float start_x = 385.f;		//

	void initTexture();
	void initSprite();

public:

	Ball();
	~Ball();

	bool devMODE    = false;
	bool ballin     = false;			// zmienna jest u¿ywana przy resecie pozycji w wyniku œmierci
	bool noCheating = false;			// zmienna zapobiega resetowaniu pozycji pi³ki za ka¿dym naciœniêciem spacji

	int moveSpeed = 4;

	float xV = 1.f;						// zmienne u¿ywane do okreœlenia kierunku poruszania siê pi³ki
	float yV = -1.f;					// wyjœciowo tak jak w oryginale pi³ka porusza siê w prawy, górny róg

	int HP = 3;
	 
	const sf::CircleShape getHitbox() const;

	void operator++();

	void death();

	void update();
	void render( sf::RenderTarget& target );
};