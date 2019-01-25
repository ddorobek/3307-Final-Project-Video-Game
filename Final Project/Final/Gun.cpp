/** @class Gun.cpp
* @brief The Gun class intializes all of the gun types and shooting 
* @authors - Group 15
*
* This class contains different types of guns, their attributes and also a function to shoot guns in which bullets are pushed onto a bullets array
*/

#include "Gun.h"
#include "Bullet.h"
#include <stdlib.h>

/** @fn Gun::Gun()
* @brief Gun Constructor  
*/
Gun::Gun()
{

}

/** @fn Gun::Gun(string type) 
* @brief Gun Constructor
* The constructor initializes the different types of guns to be used 
*/
Gun::Gun(string type)
{
	this->name = type; ///< Set the gun name to the type parameter

	/**
	* If the type is Pistol then inialize bullet values for a pistol gun
	*/
	if (name == "Pistol")
	{
		b.rad = 5.f;
		b.currVelocity = Vector2f(0.f, 0.f);
		b.maxSpeed = 10.f;
		b.shape.setRadius(5.f);
		b.shape.setFillColor(Color::Red);
		damage = 1;
	}
	/**
	* If the type is Smg then inialize bullet values for a Smg gun
	*/
	if (name == "Smg")
	{
		b.rad = 5.f;
		b.currVelocity = Vector2f(0.f, 0.f);
		b.maxSpeed = 12.f;
		b.shape.setRadius(5.f);
		b.shape.setFillColor(Color::Blue);
		damage = 1;
	}
	/**
	* If the type is Rifle then inialize bullet values for a Rifle gun
	*/
	if (name == "Rifle")
	{
		b.rad = 5.f;
		b.currVelocity = Vector2f(0.f, 0.f);
		b.maxSpeed = 15.f;
		b.shape.setRadius(5.f);
		b.shape.setFillColor(Color::Green);
		damage = 3;
	}
	/**
	* If the type is Shotgun then inialize values bullet for a Shotgun gun
	*/
	if (name == "Shotgun")
	{
		b.rad = 2.f;
		b.currVelocity = Vector2f(0.f, 0.f);
		b.maxSpeed = 12.f;
		b.shape.setRadius(2.f);
		b.shape.setFillColor(Color::Yellow);
		damage = 1;
	}
	/**
	* If the type is Launcher then inialize bullet values for a Launcher gun
	*/
	if (name == "Launcher")
	{
		b.rad = 10.f;
		b.currVelocity = Vector2f(0.f, 0.f);
		b.maxSpeed = 10.f;
		b.shape.setRadius(10.f);
		b.shape.setFillColor(Color::Cyan);
		damage = 7;
	}
	/**
	* If the type is Boss then inialize bullet values for a Boss Gun
	*/
	if (name == "Boss")
	{
		b.rad = 10.f;
		b.currVelocity = Vector2f(0.f, 0.f);
		b.maxSpeed = 4.f;
		b.shape.setRadius(10.f);
		b.shape.setFillColor(Color::Cyan);
		damage = 1;
	}
}


/** @fn void Gun::shoot(Vector2f playerCenter, Vector2f aimDirNorm)
* @brief Shoot function 
* @param playerCenter - A vector for the center of the player
* @param aimDirNorm - A vector for the direciton of the aim
* This function sets the position and velocity of bullets that are to be shot, it also pushes the bullets into the vector list bullets
*/
void Gun::shoot(Vector2f playerCenter, Vector2f aimDirNorm)
{
	b.shape.setPosition(playerCenter);
	b.currVelocity = aimDirNorm * b.maxSpeed;

	bullets.push_back(Bullet(b));
}
