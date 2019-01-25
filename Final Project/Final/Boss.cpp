/** @class Boss
 * @brief The Boss class creates a new Boss object that will move towards the player and attempt to deal damage with a gun
 * @author Group 15
 *
 * The Enemy class creates an boss object, initalizes its attributes, contains functions that update the boss position and update the boss position towards the player
 * The Boss class also returns the enemys attack damage that will be dealt to the player, and sets the type of gun the Boss will use
 */
#include "Boss.h"

using namespace sf;

/**@fn Boss::Boss(int type, Gun g) 
 * @brief This function constructs the Boss object
 * @param type - type of Boss character to be created
 * @param g - type of gun object the boss has
 * This function constructs a Boss object and determines its variables based on Boss type passed as the parameter
 * This function also determines what type of gun the boss will be using
 */
Boss::Boss(int type, Gun g) {

	this->gun = g;
	rect.setSize(Vector2f(96 * 4, 48 * 4));
	rect.setPosition(400, 200);
	rect.setFillColor(Color::Blue);
	sprite.setTextureRect(IntRect(0, 0, 96, 48));
	sprite.setScale(4.f, 4.f);

	enemyType = type;

	//enemy type 1
	if (type == 1) {
		movementSpeed = 1;
		attackDamage = 1;
		health = 150;
	}
}

/** @fn void Boss::update()
 * @brief This function updates the boss current position
 * The update function gets the current position of the boss and sets its position to the new position
 */
void Boss::update() {
	sprite.setPosition(rect.getPosition());
}

/** @fn void Boss::updateMovement(Vector2f playerCenter)
 * @brief This function updates the boss position closer to the players position
 * @param playerCenter - the current position of the player
 * This function gets the position of the player as a parameter and then updates the boss position so it moves closer to the players current position
 */
void Boss::updateMovement(Vector2f playerCenter) {

	//players position
	int px = playerCenter.x;
	int py = playerCenter.y;

	//boss position
	int ex = rect.getPosition().x + 48 * 4;
	int ey = rect.getPosition().y + 24 * 4;

	walk = timer.getElapsedTime(); //tracks the boss sprite movement animations

	//enemy type 1 movement style
	if (enemyType == 1) {
		if (px < ex) {  //left
			rect.move(-movementSpeed, 0);
			sprite.setTextureRect(IntRect(counterWalking * 96, 48 * 1, 96, 48));
		}
		if (px > ex) {  //right
			rect.move(movementSpeed, 0);
			sprite.setTextureRect(IntRect(counterWalking * 96, 48 * 2, 96, 48));
		}
		if (py > ey) { // down
			rect.move(0, movementSpeed);
			sprite.setTextureRect(IntRect(counterWalking * 96, 0, 96, 48));
		}
		if (py < ey) {  //up
			rect.move(0, -movementSpeed);
			sprite.setTextureRect(IntRect(counterWalking * 96, 48 * 3, 96, 48));
		}
	}

	//uses the timer so sprite animations are clear while moving
	if (walk.asSeconds() > 0.5)
	{
		timer.restart();
		counterWalking++;
	}


	if (counterWalking == 2) {
		counterWalking = 0;
	}
}

/** @fn int Boss::getAttackDamage() 
 * @brief This function returns the boss attack damage
 * @return attackDamage - the amount of damage the boss can deal to the player
 * This function gets the attack damage of the boss and returns it
 */
int Boss::getAttackDamage() {
	return attackDamage;
}

/** @fn void Boss::setGun(Gun g)
 * @brief This function sets the gun of the boss
 * @param g - type of gun object boss will use
 * This function sets the boss gun variable to whatever gun type is passed as the parameter
 */
void Boss::setGun(Gun g)
{
	this->gun = g;
}
