/** @class GameWon
* @brief The GameWon class creates a screen for when the player has won the game.
* @author
*
* The GameWon class creates a window of the screen when the player successfully completes the game. The screen informs the player that they have won and gives them the option to exit the game.
*/

#include "GameWon.h"
using namespace sf;

/** @fn GameWon::GameWon()
* @brief This function constructs the GameWon object.
*
* This function constructs the GameWon object and renders a window to display to the user. The user will be informed they have won the game and the game creators will be displayed. The user will have the option to exit the game.
*/
GameWon::GameWon() {
	//Open window and set frame rate to 60
	sf::RenderWindow window(VideoMode(1280, 720), "R.E.M. - You Win", Style::Default);
	window.setFramerateLimit(60);
	Event event;
	Vector2f mousePosWindow;
	
	//Create overlay texture and sprite for window background.
	sf::Texture bgTexture;
	sf::Sprite bgSprite;
	sf::Image bgImage;
	bgImage.loadFromFile("won-1280x720.png");
	bgTexture.loadFromImage(bgImage);
	bgSprite.setTexture(bgTexture);
	bgSprite.setTextureRect(IntRect(0, 0, 1280, 720));
	bgSprite.setPosition(0.0f, 0.0f);

	//Create overlay texture and sprite for Exit image.
	sf::Texture quitTexture; 
	sf::Sprite quitSprite;
	sf::Image quitImage;
	quitImage.loadFromFile("exit-480x135.png");
	quitTexture.loadFromImage(quitImage);
	quitSprite.setTexture(quitTexture);
	quitSprite.setTextureRect(IntRect(0, 0, 480, 135));
	quitSprite.setPosition(800.0f / 2.0f, 292.5f);

	//Loads font to display text
	Font font;
	if (!font.loadFromFile("lcdsolid.ttf"))
	{
		//didn't load properly
		std::cout << "Font did not load properly." << std::endl;
	}

	//Sets text and position for thanking the player to display on screen 
	Text overText;
	overText.setFont(font);
	overText.setString("Thanks for playing!");
	overText.setCharacterSize(48);
	overText.setFillColor(Color::Black);
	overText.setPosition(24, 24);

	//Sets text and position for the credits to display on screen 
	Text creditsText;
	creditsText.setFont(font);
	creditsText.setString("Creators: Claudiu Cretu, Damien Dorobek, John Fischer, Brayden Horth, Jordan Nesbitt");
	creditsText.setCharacterSize(24);
	creditsText.setFillColor(Color::Black);
	creditsText.setPosition(12, 684);
	
	while (window.isOpen()) {
		while (window.pollEvent(event)) {

			//If user clicks the "x" icon to close the window at the top right of the screen, window is closed which terminates game.
			if (event.type == sf::Event::Closed) {
				closed = true;
				window.close();
			}

			//Set mouse coordinates to mousePosWindow
			mousePosWindow = Vector2f(Mouse::getPosition(window));
		}

		if (Mouse::isButtonPressed(Mouse::Left)) {

			//If user clicked on the quit button, set closed to true and close window to end game.
			if (quitSprite.getGlobalBounds().contains(mousePosWindow)) {
				closed = true;
				window.close();
			}
		}

		//Clear the window.
		window.clear();

		//Draw all created sprites in the window.
		window.draw(bgSprite);
		window.draw(quitSprite);
		window.draw(overText);
		window.draw(creditsText);

		//Display the window.
		window.display();
	}
	
	
}

/** @fn bool GameWon::isClosed()
* @brief This function returns true if the player has clicked Quit.
*
* This function returns true if the player has clicked on Quit. If the player has not clicked on Quit, function returns false.
*/
bool GameWon::isClosed() {
	if (closed == true) return true;
	return false;
}

/** @fn bool GameWon::isStarted()
* @brief This function returns true if the player has won the game and the window is rendered.
*
* This function returns true if the player has won the game (completed 10 waves) and the window is rendered. Otherwise, it returns false.
*/
bool GameWon::isStarted() {
	if (started == true) return true;
	return false;
}