/** @class Boss.h
 * @brief This is the header file for the Boss class
 * @author Group 15
 * This header file declares the attributes and functions of the Boss class
 */
#pragma once
#include "Entity.h"
#include "time.h"
#include "Gun.h"

 /** @class Boss
  * @brief Declaration of the attributes and functions of the Boss class
  * This is the declaration of the attributes and functions of the Boss class
  */
class Boss : public Entity {
public:
	int movementSpeed; /**< determines the movement speed of the boss */
	int attackDamage; /**< determines the attack damage the enemy deals to the boss */
	int counterWalking = 0; /**< tracks the movement of the boss sprite */
	int health; /**< determines how much heatlh the boss has */
	int enemyType;/**< determines the type of boss */
	Clock timer; /**< used for boss sprite walking animations */
	Time walk; /**< used for boss sprite walking animations */
	Gun gun; /**< boss is given a Gun object */

	/**@fn Boss(int type, Gun g)
	 * @brief This function constructs the Boss object
	 * @param type - type of Boss character to be created
	 * @param g - type of gun object the boss has
	 * This function constructs a Boss object and determines its variables based on Boss type passed as the parameter
	  * This function also determines what type of gun the boss will be using
	 */
	Boss(int type, Gun g);

	/** @fn void update()
	 * @brief This function updates the boss current position
	 * The update function gets the current position of the boss and sets its position to the new position
	 */
	void update();

	/** @fn void updateMovement(Vector2f playerCenter)
	 * @brief This function updates the boss position closer to the players position
	 * @param playerCenter - the current position of the player
	 * This function gets the position of the player as a parameter and then updates the boss position so it moves closer to the players current position
	 */
	void updateMovement(Vector2f playerCenter);

	/** @fn int getAttackDamage()
	 * @brief This function returns the boss attack damage
	 * @return attackDamage - the amount of damage the boss can deal to the player
	 * This function gets the attack damage of the boss and returns it
	 */
	int getAttackDamage();

	/** @fn void setGun(Gun g)
	 * @brief This function sets the gun of the boss
	 * @param g - type of gun object boss will use
	 * This function sets the boss gun variable to whatever gun type is passed as the parameter
	 */
	void setGun(Gun g);
};
