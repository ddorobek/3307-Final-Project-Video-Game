/** @class Enemy
 * @brief This is the heder file for the Enemy class
 * @author Group 15
 * This header file declares the attributes and functions of the Enemy class
 */

#pragma once
#include "Entity.h"
 /** @class Enemy
  *  @brief Declaration of the attributes and functions of the Enemy class
  * This is the declaration of the attributes and functions of the Enemy class
  */
class Enemy : public Entity {
public:

	float movementSpeed; /**< determines the movement speed of the enemy */
	int attackDamage; /**< determines the attack damage the enemy deals to the player */
	int counterWalking = 0; /**< tracks the movement of the enemy sprite */
	int health; /**< determines how much heatlh the enemy has */
	int enemyType; /**< determines the type of enemey to be created */

	Clock timer; /**< used for sprite walking animations */
	Time walk; /**< used for sprite walking animations */

	/**@fn Enemy(int type)
	 * @brief This function constructs the Enemy object
	 * @param type - type of enemy character to be created
	 * This function constructs an Enemy object and determines its variables based on what enemy type is passed as the parameter
	 */
	Enemy(int type);

	/** @fn void update()
	 * @brief This function updates the enemys current position
	 * The update function gets the current position of the enemy and sets its position to the new position
	 */
	void update();

	/** @fn void updateMovement(Vector2f playerCenter)
	 * @brief This function updates the enemy position closer to the player's position.
	 * @param playerCenter - the current position of the player.
	 * This function gets the position of the player as a parameter and then updates the enemy position so it is closer to the players current position
	 */
	void updateMovement(Vector2f playerCenter);

	/** @fn int getAttackDamage()
	 * @brief This function returns the enemy attack damage
	 * @return attackDamage - the amount of damage the enemy can deal to the player
	 * This function gets the attack damage of the enemy and returns it
	 */
	int getAttackDamage();
};
