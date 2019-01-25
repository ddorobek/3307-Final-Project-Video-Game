/** @class ShopMenu
* @brief The ShopMenu class creates a window for when the player presses space to access the shop.
* @author
*
* The ShopMenu class creates a window of when the player presses space to access the shop. The shop features a button to purchase health. 
* The shop also features three buttons which each contain one of five randomly generated guns available to purchase. There is also a button to leave the shop.
*/
#include "ShopMenu.h"
#include "Gun.h"
#include <stdio.h>

using namespace sf;

/** @fn ShopMenu::ShopMenu(Player &player1)
* @brief This function constructs the ShopMenu object.
* @param player1 - the player object passed from main to update health and player gun.
* This function constructs the ShopMenu object and renders a window to display to the user. The user will be able to purchase health and three random guns (out of five). 
* The user also has the option to leave the shop.
*/
ShopMenu::ShopMenu(Player &player1) {

	//Open window and set frame rate to 60
	sf::RenderWindow window(VideoMode(1280, 720), "Game: Shop", Style::Default);
	window.setFramerateLimit(60);
	Event event;
	Vector2f mousePosWindow;

	//Loads font to display text
	Font font;
	if (!font.loadFromFile("lcdsolid.ttf")) {
		//didn't load properly
		std::cout << "Font did not load properly." << std::endl;
	}

	//Sets text and position to display on screen when the player attempts to purchase a gun with insufficient funds or when they attempt to purchase health with max health. 
	Text insFundsText;
	insFundsText.setFont(font);
	insFundsText.setString("");
	insFundsText.setCharacterSize(48);
	insFundsText.setFillColor(Color::White);
	insFundsText.setPosition(0, 0);

	//Sets text and position for player's health to display on screen 
	Text health;
	health.setFont(font);
	health.setString(to_string(player1.playerHP));
	health.setCharacterSize(64);
	health.setFillColor(Color::White);
	health.setPosition(960, 58);

	//Sets text and position for player's currency to display on screen 
	Text curr;
	curr.setFont(font);
	curr.setString(to_string(player1.currency));
	curr.setCharacterSize(64);
	curr.setFillColor(Color::White);
	curr.setPosition(1152, 58);

	//Sets text and position for player's purchase to display on screen 
	Text gunPurchasedText;
	gunPurchasedText.setFont(font);
	gunPurchasedText.setString("");
	gunPurchasedText.setCharacterSize(48);
	gunPurchasedText.setFillColor(Color::White);
	gunPurchasedText.setPosition(60, 564);
	
	//Create overlay texture and sprite for background image.
	sf::Texture bgTexture;
	sf::Sprite bgSprite;
	sf::Image bgImage;
	bgImage.loadFromFile("merchant.png");
	bgTexture.loadFromImage(bgImage);
	bgSprite.setTexture(bgTexture);
	bgSprite.setTextureRect(IntRect(0, 0, 495, 700));
	bgSprite.setPosition(10.0f, 0.0f);

	//Create overlay texture and sprite for player's current health.
	sf::Texture playerHealthTexture;
	sf::Sprite playerHealthSprite;
	sf::Image playerHealthImage;
	playerHealthImage.loadFromFile("heart-full.png");
	playerHealthTexture.loadFromImage(playerHealthImage);
	playerHealthSprite.setTexture(playerHealthTexture);
	playerHealthSprite.setTextureRect(IntRect(0, 0, 64, 64));
	playerHealthSprite.setPosition(896.0f, 60.0f);

	//Create overlay texture and sprite for player's currency.
	sf::Texture currencyTexture;
	sf::Sprite currencySprite;
	sf::Image currencyImage;
	currencyImage.loadFromFile("coin-64x64.png");
	currencyTexture.loadFromImage(currencyImage);
	currencySprite.setTexture(currencyTexture);
	currencySprite.setTextureRect(IntRect(0, 0, 64, 64));
	currencySprite.setPosition(1088.0f, 60.0f);
	
	//Create overlay texture and sprite for image to purchase health.
	sf::Texture healthTexture; 
	sf::Sprite healthSprite;
	sf::Image healthImage;
	healthImage.loadFromFile("buy-health-360x80.png");
	healthTexture.loadFromImage(healthImage);
	healthSprite.setTexture(healthTexture);
	healthSprite.setTextureRect(IntRect(0, 0, 360, 80));
	healthSprite.setPosition(900.0f / 2.0f, 60.0f);

	//Generate first random gun
	const char* gun1String = generateRandom();

	//Create random gun texture and sprite for first random gun image.
	sf::Texture gun1Texture; 
	sf::Sprite gun1Sprite;
	sf::Image gun1Image;
	gun1Image.loadFromFile(gun1String);
	gun1Texture.loadFromImage(gun1Image);
	gun1Sprite.setTexture(gun1Texture);
	gun1Sprite.setTextureRect(IntRect(0, 0, 360, 80));
	gun1Sprite.setPosition(900.0f / 2.0f, 190.0f);
	
	//Generate second random gun
	const char* gun2String = generateRandom(); 
	
	//Create random gun texture and sprite for second random gun image.
	sf::Texture gun2Texture; 
	sf::Sprite gun2Sprite;
	sf::Image gun2Image;
	gun2Image.loadFromFile(gun2String);
	gun2Texture.loadFromImage(gun2Image);
	gun2Sprite.setTexture(gun2Texture);
	gun2Sprite.setTextureRect(IntRect(0, 0, 360, 80));
	gun2Sprite.setPosition(900.0f / 2.0f, 320.0f);

	//Generate third random gun
	const char* gun3String = generateRandom();

	//Create random gun texture and sprite for third random gun image.
	sf::Texture gun3Texture;
	sf::Sprite gun3Sprite;
	sf::Image gun3Image;
	gun3Image.loadFromFile(gun3String);
	gun3Texture.loadFromImage(gun3Image);
	gun3Sprite.setTexture(gun3Texture);
	gun3Sprite.setTextureRect(IntRect(0, 0, 360, 80));
	gun3Sprite.setPosition(900.0f / 2.0f, 450.0f);

	//Create overlay texture and sprite for Leave Shop image.
	sf::Texture leaveTexture; 
	sf::Sprite leaveSprite;
	sf::Image leaveImage;
	leaveImage.loadFromFile("leave-shop-360x80.png");
	leaveTexture.loadFromImage(leaveImage);
	leaveSprite.setTexture(leaveTexture);
	leaveSprite.setTextureRect(IntRect(0, 0, 360, 80));
	leaveSprite.setPosition(900.0f / 2.0f, 580.0f);

	while (window.isOpen()) {
		while (window.pollEvent(event))	{

			//Set mouse coordinates to mousePosWindow
			mousePosWindow = Vector2f(Mouse::getPosition(window));
			
			if (Mouse::isButtonPressed(Mouse::Left)) {

				//If an insuffient funds text was displayed to the user, clear the text when they left click again.
				if (insFundsText.getString() != "") {
					insFundsText.setString("");
				}

				//If a gun purchased text was displayed to the user, clear the text when they left click again.
				if (gunPurchasedText.getString() != "") {
					gunPurchasedText.setString("");
				}

				//If user clicked on the Buy Health button, add health if player has enough currency and is not at max health capacity.
				if (healthSprite.getGlobalBounds().contains(mousePosWindow)) {
					purchaseHealth(player1, curr, health, insFundsText, gunPurchasedText);
				}

				//If the player selects first gun slot to purchase, call purchaseGuns() to determine if they have enough currency and update player's gun if they do.
				if (gun1Sprite.getGlobalBounds().contains(mousePosWindow)) {
					purchaseGuns(player1, gun1String, curr, insFundsText, gunPurchasedText);
				}

				//If the player selects second gun slot to purchase, call purchaseGuns() to determine if they have enough currency and update player's gun if they do.
				if (gun2Sprite.getGlobalBounds().contains(mousePosWindow)) {
					purchaseGuns(player1, gun2String, curr, insFundsText, gunPurchasedText);
				}

				//If the player selects third gun slot to purchase, call purchaseGuns() to determine if they have enough currency and update player's gun if they do.
				if (gun3Sprite.getGlobalBounds().contains(mousePosWindow)) {
					purchaseGuns(player1, gun3String, curr, insFundsText, gunPurchasedText);
				}

				//If user clicked on the Leave Shop image, set closed to true and close window to go back to game
				if (leaveSprite.getGlobalBounds().contains(mousePosWindow)) {
					closed = true;
					window.close();
				}
			}
		}

		//Clear the window.
		window.clear();

		//Draw background image
		window.draw(bgSprite);

		//Draw all created text in the window.
		window.draw(curr);
		window.draw(health);
		window.draw(insFundsText);	

		//Draw all created sprites in the window.
		window.draw(playerHealthSprite);
		window.draw(currencySprite);
		window.draw(gun1Sprite);
		window.draw(gun2Sprite);
		window.draw(gun3Sprite);
		window.draw(healthSprite);
		window.draw(leaveSprite);
		window.draw(gunPurchasedText);

		//Display the window.
		window.display();
	}
}

/** @fn void ShopMenu::purchaseHealth(Player &player1, Text &currency, Text &health, Text &insFunds, Text &gunPurchasedText)
* @brief This function determines whether the player has enough currency to purchase health and updates player's health if they do.
* @param player1 - address of player object to update gun.
* @param currency - address of currency text to update player's currency
* @param health - address of health text to update player's health
* @param insFunds - address of 'insufficient funds' text to display to the user if they do not have enough currency to purchase health.
* @param gunPurchasedText - address of 'gun purchased' text to display to the user if they successfully purchase a weapon.
* This function determines whether the player has enough currency to purchase health. If they do, player's health is incremented.
* If the player does not have enough currency, an 'insufficient funds' message will be displayed on the screen.
* If the player's health is already at max capacity, a 'player has max health' message will be displayed on the screen. 
*/
void ShopMenu::purchaseHealth(Player &player1, Text &currency, Text &health, Text &insFunds, Text &gunPurchasedText) {
	//If user clicked on Buy Health, add 1 health point to player health if they are under the maximum capacity
	if (player1.playerHP < 10 && player1.currency > 0) {
		player1.playerHP += 1;
		player1.currency -= 1;
		health.setString(to_string(player1.playerHP));
		currency.setString(to_string(player1.currency));
		gunPurchasedText.setString("Health \npurchased.");
	}

	//If user does not have enough currency to purchase health, display insufficient funds message
	else if (player1.currency <= 0) {
		insFunds.setString("Player has \ninsufficient \nfunds!");
		insFunds.setPosition(60, 60);
	}

	//If user already has full health, display max health message
	else if (player1.playerHP == 10) {
		insFunds.setString("Player has \nmax health!");
		insFunds.setPosition(60, 60);
	}
}

/** @fn void ShopMenu::purchaseGuns(Player &player1, const char* gunString, Text &currency, Text &insFunds, Text &gunPurchasedText)
* @brief This function determines whether the player has enough currency to purchase a gun and updates player's gun if they do.
* @param player1 - address of player object to update gun.
* @param gunString - string of gun image available to purchase.
* @param currency - address of currency text to update player's currency
* @param insFunds - address of 'insufficient funds' text to display to the user if they do not have enough currency to purchase gun.
* @param gunPurchasedText - address of 'gun purchased' text to display to the user if they successfully purchase a weapon.
* This function determines whether the player has enough currency to purchase a gun. If they do, player's gun is updated. 
* Otherwise, an 'insufficient funds' message will be displayed on the screen.
*/
void ShopMenu::purchaseGuns(Player &player1, const char* gunString, Text &currency, Text &insFunds, Text &gunPurchasedText) {
	//If user clicked on the first random gun image, udpate player's gun if they have enough currency and update player's currency displayed on screen
	if (player1.currency >= getGunCost(gunString)) {
		player1.currency -= getGunCost(gunString);
		Gun playerGun = Gun(getGunName(gunString));
		player1.setGun(playerGun);
		currency.setString(to_string(player1.currency));
		gunPurchasedText.setString(playerGun.name + " \npurchased.");
	}

	//If user does not have enough currency to purchase gun, display insufficient funds message
	else if (player1.currency < getGunCost(gunString)) {
		insFunds.setString("Player has \ninsufficient \nfunds!");
		insFunds.setPosition(60, 60);
	}
}

/** @fn bool ShopMenu::isClosed()
* @brief This function returns true if the player has clicked "Leave Shop".
* This function returns true if the player has clicked on "Leave SHop". Otherwise, function returns false.
*/
bool ShopMenu::isClosed() {
	if (closed == true) return true;
	return false;
}

/** @fn const char* ShopMenu::generateRandom()
* @brief This function generates a random string for the image of one of five guns for the player to purchase from the shop.
* @return string for image of random generated gun.
* This function generates the string for the image of one of five random guns for the player to purchase from the shop.
* With this string, the window can load the button image for the randomly generated gun.
*/
const char* ShopMenu::generateRandom() {

	//Generates random number
	int randNum = rand();
	float random = float((randNum % 5) + 1);
	int gunNum = int(random);

	//Set gun filepath and return it
	if (gunNum == 1) return "buy-pistol-360x80.png";
	if (gunNum == 2) return "buy-smg-360x80.png";
	if (gunNum == 3) return "buy-shotgun-360x80.png";
	if (gunNum == 4) return "buy-rifle-360x80.png";
	if (gunNum == 5) return "buy-launcher-360x80.png";
	else return "";

}

/** @fn const char* ShopMenu::getGunName(const char* gunFile)
* @brief This function generates and returns a string for the name of the gun that was passed in the gunFile parameter.
* @param gunFile - string for image file generated by generateRandom().
* @return string for name of gun corresponding to gunFile.
* This function generates the string for the image of one of five random guns for the player to purchase from the shop.
* With this string, the window can load the button image for the randomly generated gun.
*/
const char* ShopMenu::getGunName(const char* gunFile) {
	if (gunFile == "buy-pistol-360x80.png") return "Pistol";
	if (gunFile == "buy-smg-360x80.png") return "Smg";
	if (gunFile == "buy-shotgun-360x80.png") return "Shotgun";
	if (gunFile == "buy-rifle-360x80.png") return "Rifle";
	if (gunFile == "buy-launcher-360x80.png") return "Launcher";
	else return "";
}

/** @fn int ShopMenu::getGunCost(const char* gunFile)
* @brief This function generates and returns an int for the cost of the gun that was passed in the gunFile parameter.
* @param gunFile - string for image file generated by generateRandom().
* @return int for cost of gun corresponding to gunFile.
* This function generates the int for the cost of one of five random guns for the player to purchase from the shop.
* With this int, the guns are priced correctly when being displayed in the shop.
*/
int ShopMenu::getGunCost(const char* gunFile) {
	if (gunFile == "buy-pistol-360x80.png") return 5;
	if (gunFile == "buy-smg-360x80.png") return 8;
	if (gunFile == "buy-shotgun-360x80.png") return 10;
	if (gunFile == "buy-rifle-360x80.png") return 12;
	if (gunFile == "buy-launcher-360x80.png") return 20;
	else return 0;
}
