/** @class Enemy
 * @brief The Enemy class creates a new Enemy object that will move towards the player and attempt to deal damage
 * @author Group 15
 *
 * The Enemy class creates an enemy object based on its enemy type, determing its attributes, contains functions that update the enemy position and update the enemy position towards the player
 * The Enemy class also returns the enemys attack damage that will be dealt to the player
 */
#include "Enemy.h"

using namespace sf;

/**@fn Enemy::Enemy(int type) 
 * @brief This function constructs the Enemy object
 * @param type - type of enemy character to be created
 * This function constructs an Enemy object and determines its variables based on what enemy type is passed as the parameter
 */
Enemy::Enemy(int type) {

	enemyType = type;

	//enemy type 1
	if (type == 1) {
		sprite.setTextureRect(IntRect(0, 0, 32, 48));
		rect.setSize(Vector2f(32, 48));

		//declare enemy attributes
		movementSpeed = 3;
		attackDamage = 1;
		health = 3;
	}

	//enemy type 2
	if (type == 2) {
		sprite.setTextureRect(IntRect(0, 0, 96, 96));
		rect.setSize(Vector2f(96, 96));

		//declare enemy attributes
		movementSpeed = 1.5;
		attackDamage = 5;
		health = 16;
	}

	//enemy type 3
	if (type == 3) {
		sprite.setTextureRect(IntRect(0, 0, 80, 80));
		rect.setSize(Vector2f(80, 80));

		//declare enemy attributes
		movementSpeed = 1.2;
		attackDamage = 3;
		health = 8;
	}

	rect.setPosition(400, 200);
	rect.setFillColor(Color::Blue);
}

/** @fn void Enemy::update() 
 * @brief This function updates the enemys current position
 * The update function gets the current position of the enemy and sets its position to the new position
 */
void Enemy::update() {
	sprite.setPosition(rect.getPosition());
}

/** @fn void Enemy::updateMovement(Vector2f playerCenter)
 * @brief This function updates the enemy position closer to the players position
 * This function gets the position of the player as a parameter and then updates the enemy position so it is closer to the players current position
 * Each enemy type has a different movement style
 */
void Enemy::updateMovement(Vector2f playerCenter) {

	//players position
	int px = playerCenter.x;
	int py = playerCenter.y;

	//enemy position
	int ex = rect.getPosition().x;
	int ey = rect.getPosition().y;

	walk = timer.getElapsedTime(); //tracks the enemy sprite movement animations

	//enemy type 1 movement style
	if (enemyType == 1) {
		if (px < ex) { //left
			rect.move(-movementSpeed, 0);
			sprite.setTextureRect(IntRect(counterWalking * 32, 48 * 1, 32, 48));
		}
		if (px > ex) { //right
			rect.move(movementSpeed, 0);
			sprite.setTextureRect(IntRect(counterWalking * 32, 48 * 2, 32, 48));
		}
		if (py > ey) { //up
			rect.move(0, movementSpeed);
			sprite.setTextureRect(IntRect(counterWalking * 32, 0, 32, 48));
		}
		if (py < ey) { //down
			rect.move(0, -movementSpeed);
			sprite.setTextureRect(IntRect(counterWalking * 32, 48 * 3, 32, 48));
		}
	}

	//enemy type 2 movement style
	if (enemyType == 2) {
		if (px < ex) { //left
			rect.move(-movementSpeed, 0);
			sprite.setTextureRect(IntRect(counterWalking * 96, 96 * 1, 96, 96));
		}
		if (px > ex) { //right
			rect.move(movementSpeed, 0);
			sprite.setTextureRect(IntRect(counterWalking * 96, 96 * 2, 96, 96));
		}
		if (py > ey) { //move up only if lined up with player
			if (px == ex) {
				rect.move(0, movementSpeed);
				sprite.setTextureRect(IntRect(counterWalking * 96, 0, 96, 96));
			}
		}
		if (py < ey) { //move down only if lined up with player
			if (px == ex) {
				rect.move(0, -movementSpeed);
				sprite.setTextureRect(IntRect(counterWalking * 96, 96 * 3, 96, 96));
			}
		}
	}

	//enemy type 3 movement style
	if (enemyType == 3) {
		if (px < ex + 3) { //left
			rect.move(-movementSpeed, 0);
			sprite.setTextureRect(IntRect(counterWalking * 80, 80 * 1, 80, 80));
		}
		if (px > ex + 3) { //right
			rect.move(movementSpeed, 0);
			sprite.setTextureRect(IntRect(counterWalking * 80, 80 * 2, 80, 80));
		}
		if (py > ey + 3) { //up
			rect.move(0, movementSpeed);
			sprite.setTextureRect(IntRect(counterWalking * 80, 80 * 0, 80, 80));
		}
		if (py < ey + 3) { //down
			rect.move(0, -movementSpeed);
			sprite.setTextureRect(IntRect(counterWalking * 80, 80 * 3, 80, 80));
		}
	}


	//uses the timer so sprite animations are clear while moving
	if (walk.asSeconds() > 0.3)
	{
		timer.restart();
		counterWalking++;
	}

	if (counterWalking == 4) {
		counterWalking = 0;
	}


}
/** @fn Enemy::getAttackDamage() 
 * @brief This function returns the enemy attack damage
 * @return attackDamage - the amount of damage the enemy can deal to the player
 * This function gets the attack damage of the enemy and returns it
 */
int Enemy::getAttackDamage() {
	return attackDamage;
}
