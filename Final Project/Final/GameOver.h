/** @class GameOver
* @brief This is the header file for the GameOver class.
* @author
*
* This header file declares the attributes and functions of the GameOver class.
*/
#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

/** @class GameOver
*  @brief Declaration of the attributes and functions of the GameOver class
* This is the declaration of the attributes and functions of the GameOver class
*/
class GameOver {
public:
	/** @fn GameOver()
	* @brief This function constructs the GameOver object.
	*
	* This function constructs the GameOver object and renders a window to display to the user. The user has the option to select the "Exit" button to exit the game.
	*/
	GameOver();

	/** @fn bool isClosed()
	* @brief This function returns true if the player has clicked Exit.
	* @return
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
