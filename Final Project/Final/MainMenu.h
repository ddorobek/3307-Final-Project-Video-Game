/** @class MainMenu.h
* @brief This is the header file for the MainMenu class
* @author Group15
*
* This header file declares the attributes and functions of the MainMenu class.
*/
#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

/** @class MainMenu.h
* @brief Declaration of attributes and functions of MainMenu
* This is the declaration of the attributes and functions of the MainMenu class
*/
class MainMenu {
public:
	/** @fn MainMenu()
	* @brief This function constructs the MainMenu object.
	*
	* This function constructs the MainMenu object and renders a window to display to the user. The user has the option to select the "Start", "Quit", or "?" buttons to start the game, quit the game (close the window), or view the instructions.
	*/
	MainMenu();

	/** @fn bool isStarted(void)
	* @brief This function returns true if the player has clicked Start.
	*
	* This function returns true if the player has clicked on Start. If the player has not clicked on Start, function returns false.
	*/
	bool isStarted();

	/** @fn bool isClosed(void)
	* @brief This function returns true if the player has clicked Quit.
	*
	* This function returns true if the player has clicked on Quit. If the player has not clicked on Quit, function returns false.
	*/
	bool isClosed();

private:
	bool closed = false; /**< determines if main menu has been closed or not */
	bool started = false; /**< determines if game has been started or not */
};
