/** @class Player
 * @brief The Player class creates a new player object and initalizes its attributes
 * @author: Group 15
 * The Player class contains functions that update the player position and sets the players gun type
 */
#include "Player.h"
#include "Gun.h"

using namespace sf;

/** @fn Player::Player(Gun G)
 * @brief This is the function that contructs a Player object
 * Player constructor takes Gun G as a parameter
 */
Player::Player(Gun G)
{
	currency = 0; ///< sets players initial currency
	playerHP = 10;  ///< sets players initial playerHP 
	this->weapon = G; ///< gives the player the weapon G
	rect.setSize(Vector2f(64, 64)); ///< the size of the rectangle is set its position the sprite position and the colour of rect is set 
	rect.setPosition(100.f, 100.f);
	sprite.setPosition(100.f, 100.f);
	rect.setFillColor(Color::Transparent);


}

/** @fn void Player::update()
 * @brief This function updates the players position
 * This function gets the current position of the player and sets its position as the new position
 */
void Player::update()
{
	rect.setPosition(sprite.getPosition());
}

/** @fn void Player::setGun(Gun G)
 * @brief This function sets the gun of the player
 * This function sets the players gun to whatver gun type is passed as the parameter
 */
void Player::setGun(Gun G)
{
	this->weapon = G;
}
