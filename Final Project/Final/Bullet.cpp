/** @class Bullet
 * @brief The Bullet class initializes the different bullet types that used by the players gun
 * This class contains a function that updates the current position of the moving bullet
 * @author: Group 15
 */
#include "Bullet.h"

using namespace sf;

/** @fn Bullet::Bullet()
 * @brief This function contructs a Bullet object
 * The function constructs a Bullet object and initializes the attributes of the bullet the player will shoot
 */
Bullet::Bullet()
{

}

/** @fn void Bullet::update()
 * @brief This function updates the position of the bullet
 * The Update function gets the current position of the bullet and sets its position to the new position
 */
void Bullet::update()
{
	rect.setPosition(shape.getPosition());
}
