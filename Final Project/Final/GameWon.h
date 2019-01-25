/** @class GameWon
* @brief This is the header file for the GameWon class.
* @author Group15
*
* This header file declares the attributes and functions of the GameWon class.
*/
#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

/** @class GameWon
*  @brief Declaration of the attributes and functions of the GameWon class
* This is the declaration of the attributes and functions of the GameWon class
*/
class GameWon {
public:
	/** @fn GameWon()
	* @brief This function constructs the GameWon object.
	*
	* This function constructs the GameWon object and renders a window to display to the user. The user has the option to select the "Exit" button to exit the game.
	*/
	GameWon();

	/** @fn bool isClosed()
	* @brief This function returns true if the player has clicked Exit.
	*
	* This function returns true if the player has clicked on Exit. If the player has not clicked on Exit, function returns false.
	*/
	bool isClosed();

	/** @fn bool isStarted()
	* @brief This function returns true if the player has won the game and the window is rendered.
	* @return
	* This function returns true if the player has won the game and the window is rendered. Otherwise, it returns false.
	*/
	bool isStarted();

private:
	bool closed = false; /**< determines if game has been exited or not */
	bool started = false; /**< determines if window has been rendered */
};
