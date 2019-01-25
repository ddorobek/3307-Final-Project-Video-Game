/** @header Entity
* @brief This is the header file for the Entity class
* @author Group 15
* This header files declares the methods and variables of the Entity class
*/

#pragma once
#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <list>
#include <functional>
#include <math.h> //idk
#include <cmath>
#include <deque>
//#include <unistd.h>

using namespace std;
using namespace sf;

/** @class Entity
 * This is the declaration of variables and functions for the Entity class
 */
class Entity
{
public:

	RectangleShape rect; /**< determines shape of the entity */
	Sprite sprite; /**< determines the sprite for the entity */
	Text text; /**< determines the text for the entity */

	/** @fn Entity()
	 * @brief This function contructs an Entity object
	 * The function constructs a Entity object and initializes the attributes
	 */
	Entity();
};
