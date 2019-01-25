/** @class Bullet
 * @brief This is the header file for the Bullet class
 * This header file declares the methods and variables of the Bullet class
 * @author: Group 15
 */

#pragma once
#include "Entity.h"

 /** @class Bullet
  * @brief Declaration of attributes and functions in Bullet
  * This is the declaration of variables and functions for the Bullet class
  */

class Bullet : public Entity
{
public:
	/** @fn Bullet()
	 * @brief This function contructs a Bullet object
	 * The function constructs a Bullet object and initializes the attributes of the bullet the player will shoot
	 */
	Bullet();

	/** @fn void update()
	 * @brief This function updates the position of the bullet
	 * The Update function gets the current position of the bullet and sets its position to the new position
	 */
	void update();

	CircleShape shape; /**< determines the shape of the bullet */
	Vector2f currVelocity; /**< determins the velocity/movement speed of the bullet */
	float maxSpeed; /**< determines the maximum speed of the bullet */
	float rad; /**< determines the radius size of the bullet */

};
