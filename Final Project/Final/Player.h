/** @class Player
* @brief This is the header file for the Player class
* @author Group 15
* This header file declares the mehtods and variables of the Player class
*/
#pragma once

#include "Entity.h"
#include "Gun.h"
/** @class Player
*  @brief Declaration of the attributes and functions of the Player class
* This is the declaration of variables and functions for the Player class
*/
class Player : public Entity
{
public:

	int movementSpeed = 0; /**< the players movemenbt speed */
	Gun weapon;	/**< the players weapon */
	int currency; /**< the amount of currency the player has */
	int playerHP; /**< the amount of health the player has */

	/** @fn Player(Gun G)
	* @brief This is the function that contructs a Player object
	* @param G - gun type the player will use
	* Player constructor takes Gun G as a parameter
	*/
	Player(Gun G);

	/** @fn void setGun(Gun G)
	 * @brief This function sets the gun of the player
	 * @param G - type of gun
	 * This function sets the players gun to whatver gun type is passed as the parameter
	 */
	void setGun(Gun G);

	/** @fn void update()
	 * @brief This function updates the players position
	 * This function gets the current position of the player and sets its position as the new position
	 */
	void update();
};
