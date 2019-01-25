/** @class Gun.h
* @brief This is the header file for the Gun class
* @author Group15
* This header file declares the methods and variables of the Gun class
*/

#pragma once
#include <string>
#include <vector>
#include "Bullet.h"

using namespace std; 

/** @class Gun.h
* @brief Declaration of the attributes and functions of the Gun class
* This is the declaration of variables and functions for the Gun class
*/
class Gun
{
public:
	/** @fn Gun()
	*  @brief Gun Constructor
	* This is the default constructor for the gun
	*/
	Gun();

	/** @fn Gun(string type) 
	* @brief Gun Constructor
	* @param type - The type of the gun, the type will be a string
	* The constructor initializes the different types of guns to be used
	*/
	Gun(string type);	

	/** @fn void shoot(Vector2f playerCenter, Vector2f aimDirNorm)
	* @brief Shoot function
	* @param playerCenter - A vector for the center of the player
	* @param aimDirNorm - A vector for the direciton of the aim
	*  This function sets the position and velocity of bullets that are to be shot, it also pushes the bullets into the vector list bullets
	*/
	void shoot(Vector2f playerCenter, Vector2f aimDirNorm);


	Bullet b; ///< bullet type, each bullet will be different for specific guns
	string name; ///< name of the current gun
	vector<Bullet> bullets; ///< vector list of the bullets for a gun
	int damage; ///< damage of a gun type
};
