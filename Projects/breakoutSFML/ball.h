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

	const float start_y = 470.f;		// sta�e zmienne wyj�ciowej pozycji pi�ki
	const float start_x = 385.f;		//

	void initTexture();
	void initSprite();

public:

	Ball();
	~Ball();

	bool devMODE    = false;
	bool ballin     = false;			// zmienna jest u�ywana przy resecie pozycji w wyniku �mierci
	bool noCheating = false;			// zmienna zapobiega resetowaniu pozycji pi�ki za ka�dym naci�ni�ciem spacji

	int moveSpeed = 4;

	float xV = 1.f;						// zmienne u�ywane do okre�lenia kierunku poruszania si� pi�ki
	float yV = -1.f;					// wyj�ciowo tak jak w oryginale pi�ka porusza si� w prawy, g�rny r�g

	int HP = 3;
	 
	const sf::CircleShape getHitbox() const;

	void operator++();

	void death();

	void update();
	void render( sf::RenderTarget& target );
};