/** @class MainMenu 
* @brief The MainMenu class creates a start screen for the player to start the game.
* @author 
*
* This class creates a window for the start screen of the game. The player has the option to start the game, quit the game, or view the instructions of the game.
*/
#include "MainMenu.h"
using namespace sf;

/** @fn MainMenu::MainMenu()
* @brief This function constructs the MainMenu object.
*
* This function constructs the MainMenu object and renders a window to display to the user. The user has the option to select the "Start", "Quit", or "?" buttons to start the game, quit the game (close the window), or view the instructions.
*/
MainMenu::MainMenu() {
	//Open window and set frame rate to 60
	sf::RenderWindow window(VideoMode(1280, 720), "R.E.M. - Main Menu", Style::Default);
	window.setFramerateLimit(60);
	Event event;
	Vector2f mousePosWindow;
	
	//Create overlay texture and sprite for window background.
	sf::Texture bgTexture;
	sf::Sprite bgSprite;
	sf::Image bgImage;
	bgImage.loadFromFile("main-menu-1280x720.png");
	bgTexture.loadFromImage(bgImage);
	bgSprite.setTexture(bgTexture);
	bgSprite.setTextureRect(IntRect(0, 0, 1280, 720));
	bgSprite.setPosition(0.0f, 0.0f);

	//Create overlay texture and sprite for Start image.
	sf::Texture startTexture; 
	sf::Sprite startSprite;
	sf::Image startImage;
	startImage.loadFromFile("start-480x135.png");
	startTexture.loadFromImage(startImage);
	startSprite.setTexture(startTexture);
	startSprite.setTextureRect(IntRect(0, 0, 480, 135));
	startSprite.setPosition(800.0f / 2.0f, 210);

	//Create overlay texture and sprite for Quit image.
	sf::Texture quitTexture; 
	sf::Sprite quitSprite;
	sf::Image quitImage;
	quitImage.loadFromFile("quit-480x135.png");
	quitTexture.loadFromImage(quitImage);
	quitSprite.setTexture(quitTexture);
	quitSprite.setTextureRect(IntRect(0, 0, 480, 135));
	quitSprite.setPosition(800.0f / 2.0f, 375.0f);

	//Create overlay texture and sprite for Instructions image.
	sf::Texture helpTexture;
	sf::Sprite helpSprite;
	sf::Image helpImage;
	helpImage.loadFromFile("help-135x135.png");
	helpTexture.loadFromImage(helpImage);
	helpSprite.setTexture(helpTexture);
	helpSprite.setTextureRect(IntRect(0, 0, 135, 135));
	helpSprite.setPosition(1085, 525);

	//Loads font to display text
	Font font;
	if (!font.loadFromFile("lcdsolid.ttf"))
	{
		//didn't load properly
		std::cout << "Font did not load properly." << std::endl;
	}

	//Sets text and position for instructions to display on screen 
	Text helpText;
	helpText.setFont(font);
	helpText.setString("");
	helpText.setCharacterSize(48);
	helpText.setFillColor(Color::White);
	helpText.setPosition(0, 0);

	while (window.isOpen()) {
		while (window.pollEvent(event))	{

			//If user clicks the "x" icon to close the window at the top right of the screen, window is closed which terminates game.
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			//Set mouse coordinates to mousePosWindow
			mousePosWindow = Vector2f(Mouse::getPosition(window));
		}

		if (Mouse::isButtonPressed(Mouse::Left)) {

			//If user clicked on the Start button, set started to true and close window to start game.
			if (startSprite.getGlobalBounds().contains(mousePosWindow)) {
				started = true;
				window.close();
			}

			//If user clicked on the Quit button, set closed to true and close window to quit game.
			if (quitSprite.getGlobalBounds().contains(mousePosWindow)) {
				closed = true;
				window.close();
			}
			
			//If user clicked on the Instructions button, set helpText to instructions.
			if (helpSprite.getGlobalBounds().contains(mousePosWindow)) {
				helpText.setString("Instructions: \nW: Up \nA: Left \nS: Down \nD: Right \n\nClick: Shoot \nSpace: Shop \n\n\n\n\n\n\n*Shop can only be accessed in between waves.");
			}

			//If user clicks outside of the Instructions button, set helpText to a blank string to hide instructions.
			if (!helpSprite.getGlobalBounds().contains(mousePosWindow)) {
				helpText.setString("");
			}
			
		}

		//Clear the window.
		window.clear();

		//Draw all created sprites in the window.
		window.draw(bgSprite);
		window.draw(startSprite);
		window.draw(quitSprite);
		window.draw(helpSprite);
		window.draw(helpText);
		
		//Display the window.
		window.display();

	}
	
	
}

/** @fn bool MainMenu::isStarted()
* @brief This function returns true if the player has clicked Start.
*
* This function returns true if the player has clicked on Start. If the player has not clicked on Start, function returns false.
*/
bool MainMenu::isStarted() {
	if (started == true) return true;
	return false;
}

/** @fn bool MainMenu::isClosed()
* @brief This function returns true if the player has clicked Quit.
*
* This function returns true if the player has clicked on Quit. If the player has not clicked on Quit, function returns false.
*/
bool MainMenu::isClosed() {
	if (closed == true) return true;
	return false;
}