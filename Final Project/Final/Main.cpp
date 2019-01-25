/*Group 15
This is a topdown shooting game set in the dream of the user.
The user controls a player to defeat the enemies of his subconsious
The player can use weapons and interact with a shop for upgrades
*/
#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <time.h>

#include "Boss.h"
#include "Player.h"
#include "MainMenu.h"
#include "ShopMenu.h"
#include "Gun.h"
#include "Bullet.h"
#include "Enemy.h"
#include "GameWon.h"
#include "GameOver.h"

using namespace sf;
int waves = 11; // Global variable for waves, keeps track of the wave number
/** @fn void waveFunction()
* @brief - A function to keep track of waves and spawn enemies and the boss.
* @param enemyArray - a vector list that contains all of the current enemies on screen
* @param enemy1 - Enemy object for the first enemy type
* @param enemy2 - Enemy object for the second enemy type
* @param enemy3 - Enemy object for the third enmey type
* @param time1 - timer for the respawn of enemy1 types
* @param time2 - timer for the respawn of enemy2 types
* @param time3 - timer for the respawn of enemy3 types
* @param waveCountdown - int countdown for when the wave will start
* @param tunnels - a vector list containing all of the tunnels (spawn points) for the enemies
* @param healthText - a Text variable to display the players health
* @param currencyText - a Text variable to display the players currency
* @param wave - a Text variable to display the current wave
* @param waveMsg - a Text variable to display the wave message for each wave's story
* @param player - a Player object to represent the player (user)
* @param waves - an int variable to represent the current wave
* @param numEnemies - an int variable to keep track of the total number of enemies for each round
* @param bossNum - an int variable to keep track of whether or not the boss is spawned
* @param num1 - an int variable to keep track of the number of enemies of type 1
* @param num2 -  an int variable to keep track of the number of enemies of type 2
* @param num3 -  an int variable to keep track of the number of enemies of type 3
* The waveFunction will use the waves variable to keep track of what wave the game is currently on. For each wave a certain amount of enemies are spawned and a certain amount of each type is spawned.
* The enemies are spawned randomly to tunnels around the map and each type is spawned at a different rate.
* At the end of each wave there is a wave message to be displayed to the screen.
* When the game reaches wave 10, the boss will be spawned by setting bossNum to 1 and it will be despawned if it is defeated by setting bossNum to -1
*/
void waveFunction(vector<Enemy> &enemyArray, Enemy &enemy1, Enemy &enemy2, Enemy &enemy3, Clock &time1, Clock &time2, Clock &time3, int &waveCountdown, vector<RectangleShape> &tunnels, Text &healthText, Text &currencyText, Text &wave, Text &waveMsg, Player &player, int &waves, int &numEnemies, int &bossNum, int &num1, int &num2, int &num3);

/** @fn void playerControls()
* @brief - A function to handle player mouse position for shooting and also player input for moving
* @param counter - an int counter used for switching sprite animations
* @param mousePosWindow - a Vector2f variable to represent the postion of the mouse on the window
* @param player - a Player variable for the player (user)
* The player is able to aim in 360 degrees with the mouse position and the sprite should reflect what direction the player is aiming.
* The player will also be able to move up, down, left, and right with the keys wasd.
*/
void playerControls(int &counter, Vector2f &mousePosWindow, Player &player);

/** @fn void playerShoot()
* @brief - a function to handle all the different shooting types that the player can have
* @param player - a Player variable for the player (user)
* @param fireRate - an int variable to change the fire rate of weapons
* @param playerCenter - a Vector2f variable to determine the center of the player on the window
* @param aimDirNorm - the normalized Vector2f variable of aimDir
* @param aimDir - a Vector2f variable for the direction of the player aim
* @param mousePosWindow - a Vector2f variable to represent the postion of the mouse on the window
* The player will have different shooting mechanics for the different weapon types that exist.
* Each shooting mechanic is different, especially the shotgun mechanic which is unlike any other gun type.
*/
void playerShoot(Player &player, int &fireRate, Vector2f &playerCenter, Vector2f &aimDirNorm, Vector2f &aimDir, Vector2f &mousePosWindow);

/** @fn void bossShoot()
* @brief - a function to handle the shooting for the boss
* @param playerCenter - a Vector2f variable to determine the center of the player on the window
* @param bossPos - a Vector2f variable for the postion of the boss on the window
* @param playerNorm - a Vector2f variable for the normalized vector of the player position
* @param bossAimDir - a Vector 2f variable for the normalized vector of the boss aim
* @param bossRate - an int variable for the fire rate of the boss weapon
* @param bossNum - an int variable to see if the boss is spawned or not
* @param boss - a Boss variable to represent the boss
* The boss only has one shooting method, it shoots like how a player shoots a shotgun, but there are less bullets and the bullet sizes are larger
*/
void bossShoot(Vector2f &playerCenter, Vector2f &bossPos, Vector2f &playerNorm, Vector2f &bossAimDir, int &bossRate, int &bossNum, Boss &boss);

/** @fn void bulletCollisions()
* @brief - a function to handle bullet collisions between player, enemies, and the boss
* @param player - a Player variable for the player (user)
* @param enemyArray - - a vector list that contains all of the current enemies on screen
* @param boss - a Boss variable to represent the boss
* @param healthText - a Text variable to display the players health
* @param currencyText - a Text variable to display the players currency
* @param bossNum - an int variable to see if the boss is spawned or not
* @param window - the variable of the game window
* This function will handle player bullets hitting enemies and the boss (if it is spawned) and it also handles bullet collision if the boss bullets hit the player.
*/
void bulletCollisions(Player &player, vector<Enemy> &enemyArray, Boss &boss, Text &healthText, Text &currencyText, int &bossNum, RenderWindow &window);

/** @fn void playerCollisions()
* @brief - a function to handle collisions between player, enemies and the boss
* @param player - a Player variable for the player (user)
* @param boss - a Boss variable to represent the boss
* @param healthText - a Text variable to display the players health
* @param bossNum - an int variable to see if the boss is spawned or not
* @param clock - a Clock variable used as an invincibility timer if the player collides with an enemy
* @param clock2 - a Clock variable used as an invincibility timer if the player collides with the boss
* @param enemyArray - a vector list that contains all of the current enemies on screen
* This function will check the global bounds of the player with the bounds of the enemies or the boss to see if there is a collision.
* If there is a collision then the player uses health and a invincibility timer starts so that the player is not damaged again right away.
*/
void playerCollisions(Player &player, Boss &boss, Text &healthText, int &bossNum, Clock &clock, Clock &clock2, vector<Enemy> &enemyArray);


/** @fn main
* @brief This function runs the main class.
*
* This function is reponsible for carrying out the program and fulfilling the responsibilites of the main class
*/

int main()
{
	//creates a main menu
	MainMenu menu;
	while (!menu.isStarted())
	{
		if (menu.isClosed())
		{
			return 0;
		}
	}

	//initialize window
	RenderWindow window(VideoMode(1280, 720), "R.E.M.", Style::Default);
	window.setFramerateLimit(60);

	//define sprite and texture for the background
	Sprite background;
	Texture texturefloor;

	//loading background image from resourses, an error is generated if the file cannot be loaded
	if (!texturefloor.loadFromFile("HDfloor.png", IntRect(0, 0, 1280, 720))) //IntRect (xpos, ypos, size, size)
	{
		perror("Erorr loading file");
	}

	//sets the image resource to background texture
	background.setTexture(texturefloor);

	//define variables used to hold the users character graphic
	Image image;
	Texture texture;
	Sprite sprite;

	//declare counters, fireRate: controls user bullet discharge, bossRate: controls boss bullet discharge
	//counter: used for player sprite rotation, waveCountdown: used to count down time until next wave
	int fireRate = 0;
	int bossRate = 0;
	int counter = 0;
	int waveCountdown = 659;

	//defining clocks
	Clock clock;
	Clock clock2;
	Clock won;
	Clock intro;
	Clock time1;
	Clock time2;
	Clock time3;

	//defining text's
	Text healthText;
	Text introText;
	Text currencyText;
	Text gunText;
	Text wave;
	Text waveMsg;

	//creating player object and giving it a newly created gun object
	Gun start("Pistol");
	Player player(start);

	//creating boss object and giving it a newly created gun object
	Gun bossWeapon("Boss");
	Boss boss(1, bossWeapon);

	int numEnemies = 3; // The initial number of enemies is set to 3
	int bossNum = 0; // The boss spawner is initially set to 0

	//defining arrays for enemies and tunnel spawn points
	vector<Enemy> enemyArray;
	vector<RectangleShape> tunnels;

	//defining variables which will be used to track the users character and users input
	Vector2f mousePosWindow;
	Vector2f playerCenter;
	Vector2f playerNorm;
	Vector2f aimDir;
	Vector2f aimDirNorm;
	Vector2f bossAimDir;

	// create tunnels for enemeies to spawn in. Each tunnel will have a set position and will be pushed to a tunnels list
	RectangleShape tunnel1(Vector2f(30, 30));
	tunnel1.setPosition(window.getSize().x / 4, 120);
	tunnel1.setFillColor(Color::Black);
	tunnels.push_back(tunnel1);

	RectangleShape tunnel2(Vector2f(30, 30));
	tunnel2.setPosition(window.getSize().x / 2 + window.getSize().x / 4, 120);
	tunnel2.setFillColor(Color::Black);
	tunnels.push_back(tunnel2);

	RectangleShape tunnel3(Vector2f(30, 30));
	tunnel3.setPosition(100, window.getSize().y / 2);
	tunnel3.setFillColor(Color::Black);
	tunnels.push_back(tunnel3);

	RectangleShape tunnel4(Vector2f(30, 30));
	tunnel4.setPosition(window.getSize().x - 100, window.getSize().y / 2);
	tunnel4.setFillColor(Color::Black);
	tunnels.push_back(tunnel4);

	RectangleShape tunnel5(Vector2f(30, 30));
	tunnel5.setPosition(window.getSize().x / 4, window.getSize().y - 120);
	tunnel5.setFillColor(Color::Black);
	tunnels.push_back(tunnel5);

	RectangleShape tunnel6(Vector2f(30, 30));
	tunnel6.setPosition(window.getSize().x / 2 + window.getSize().x / 4, window.getSize().y - 120);
	tunnel6.setFillColor(Color::Black);
	tunnels.push_back(tunnel6);


	//defining font variable and loading arial font in from resource
	Font font;
	if (!font.loadFromFile("lcdsolid.ttf"))
	{
		perror("Error loading font.");
	}

	//initialize intro graphic
	introText.setFont(font);
	introText.setString(" In a small town somewhere in midwest U.S.A. lived a young boy \n named Simon. Simon's family are devout Christians and enforce \n Christian values. Every Sunday, Simon goes to Church to learn \n about God... Recently Simon learned about the Devil. He has \n been traumatized ever since. Every night, Simon goes to bed \n having nightmares about Hell... \n\n\n This is one of those nights.");
	introText.setCharacterSize(32);
	introText.setFillColor(Color::White);
	introText.setPosition(10, 10);

	//initializes currency text
	currencyText.setFont(font);
	currencyText.setString(to_string(player.currency));
	currencyText.setCharacterSize(32);
	currencyText.setFillColor(Color::White);
	currencyText.setPosition(138, 10);

	//initialize health text
	healthText.setFont(font);
	healthText.setString(to_string(player.playerHP));
	healthText.setCharacterSize(32);
	healthText.setFillColor(Color::White);
	healthText.setPosition(42, 10);

	//initialize gun text
	gunText.setFont(font);
	gunText.setString("Gun: " + player.weapon.name);
	gunText.setCharacterSize(32);
	gunText.setFillColor(Color::White);
	gunText.setPosition(996, 10);

	//initializes wave text
	wave.setFont(font);
	wave.setString("Wave: " + to_string(waves));
	wave.setCharacterSize(32);
	wave.setFillColor(Color::White);
	wave.setPosition(202, 10);

	//initializes story dialogue between waves
	waveMsg.setFont(font);
	waveMsg.setCharacterSize(32);
	waveMsg.setFillColor(Color::White);
	waveMsg.setPosition(36, 344);

	//Create overlay texture and sprite for player's current health.
	Texture playerHealthTexture;
	Sprite playerHealthSprite;
	Image playerHealthImage;
	playerHealthImage.loadFromFile("heart-full.png");
	playerHealthTexture.loadFromImage(playerHealthImage);
	playerHealthSprite.setTexture(playerHealthTexture);
	playerHealthSprite.setTextureRect(IntRect(0, 0, 64, 64));
	playerHealthSprite.setScale(0.5, 0.5);
	playerHealthSprite.setPosition(10.0f, 10.0f);

	//Create overlay texture and sprite for player's currency.
	Texture currencyTexture;
	Sprite currencySprite;
	Image currencyImage;
	currencyImage.loadFromFile("coin-64x64.png");
	currencyTexture.loadFromImage(currencyImage);
	currencySprite.setTexture(currencyTexture);
	currencySprite.setTextureRect(IntRect(0, 0, 64, 64));
	currencySprite.setScale(0.5, 0.5);
	currencySprite.setPosition(106.0f, 10.0f);

	//load player images
	image.loadFromFile("walk.png");
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 64, 64));
	sprite.setPosition(500, 500);
	player.sprite = sprite;

	//load and initialize boss graphic
	Image imageB;
	Texture textureB;
	imageB.loadFromFile("Boss1.png");
	textureB.loadFromImage(imageB);
	boss.sprite.setTexture(textureB);

	//create an enemy type 1 and load its sprite and set its spawn number
	Enemy enemy1(1);
	int num1 = 0;
	Image image1;
	Texture texture1;
	image1.loadFromFile("bat.png");
	texture1.loadFromImage(image1);
	enemy1.sprite.setTexture(texture1);

	//create an enemy type 2 and load its sprite and set its spawn number
	int num2 = 0;
	Enemy enemy2(2);
	Image image2;
	Texture texture2;
	image2.loadFromFile("dragon.png");
	texture2.loadFromImage(image2);
	enemy2.sprite.setTexture(texture2);

	//create an enemy type 3 and load its sprite and set its spawn number
	int num3 = 0;
	Enemy enemy3(3);
	Image image3;
	Texture texture3;
	image3.loadFromFile("goat.png");
	texture3.loadFromImage(image3);
	enemy3.sprite.setTexture(texture3);



	//opens window for game
	Event event;
	while (window.isOpen())
	{
		window.clear();
		//Open shop if player presses space and the current state is a wave intermission
		if (Keyboard::isKeyPressed(Keyboard::Space) && waves <= 0) {
			window.setVisible(false);
			ShopMenu shopMenu(player); // open the shop menu
			while (!shopMenu.isClosed());
			window.setVisible(true);
			currencyText.setString(to_string(player.currency));
			healthText.setString(to_string(player.playerHP));
			gunText.setString("Gun: " + player.weapon.name);
		}

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		//if statement for if the player is dead
		if (player.playerHP <= 0) {
			window.setVisible(false);
			GameOver gameOver; // transition to the game over screen
			while (!gameOver.isStarted())
			{
				if (gameOver.isClosed())
				{
					return 0;
				}
			}
			window.setVisible(true);
		}

		// only run the rest of the game if the game is not in wave 11, which is its intro state
		if (waves != 11)
		{
			// call the waveFunction to run wave logic to spawn enemies
			waveFunction(enemyArray, enemy1, enemy2, enemy3, time1, time2, time3, waveCountdown, tunnels, healthText, currencyText, wave, waveMsg, player, waves, numEnemies, bossNum, num1, num2, num3);


			//get position of key points (player and mouse) for player shooting
			playerCenter = Vector2f(player.sprite.getPosition().x + 32, player.sprite.getPosition().y + 32);
			mousePosWindow = Vector2f(Mouse::getPosition(window));
			aimDir = mousePosWindow - playerCenter;
			aimDirNorm = aimDir / (float)(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));

			//gets the position of key points (player and mouse) for boss shooting
			Vector2f bossPos = Vector2f(boss.rect.getPosition().x + 48 * 4, boss.rect.getPosition().y + 24 * 4);
			bossAimDir = playerCenter - bossPos;
			playerNorm = bossAimDir / (float)(sqrt(pow(bossAimDir.x, 2) + pow(bossAimDir.y, 2)));

			// call the playerControls function to handle player movement and aiming
			playerControls(counter, mousePosWindow, player);

			// call the playerShoot function to handle the player shooting
			playerShoot(player, fireRate, playerCenter, aimDirNorm, aimDir, mousePosWindow);

			// call the bossShoot function to handle the boss shooting
			bossShoot(playerCenter, bossPos, playerNorm, bossAimDir, bossRate, bossNum, boss);

			// call the bulletCollisions function to check for collisions with enemies and boss
			bulletCollisions(player, enemyArray, boss, healthText, currencyText, bossNum, window);
			
			// call the playerCollisions function to check for collisions between the player, boss and enemies
			playerCollisions(player, boss, healthText, bossNum, clock, clock2, enemyArray);
		}
		// If waves is 11 then the game should be in its intro state
		if (waves == 11)
		{
			Time introTimer = intro.getElapsedTime(); // start the timer for this state

			//load in the background image
			Image bgImage;
			Texture bgTexture;
			Sprite bgSprite;
			bgImage.loadFromFile("story-bg-1280x720.png");
			bgTexture.loadFromImage(bgImage);
			bgSprite.setTexture(bgTexture);
			bgSprite.setTextureRect(IntRect(0, 0, 1280, 720));
			bgSprite.setPosition(0, 0);

			window.draw(bgSprite); // draw the background
			window.draw(introText); // draw the intro text

			// draw the intro text for 23 seconds, and when this time elapses, set waves to 0 which is the intial wave number
			if (introTimer.asSeconds() > 23)
			{
				waves = 0;
			}
		}
		// else draw everything else because the game is not in its intro state
		else
		{
			//updates the players logical location (it's rectangle)
			player.update();

			//draws background
			window.draw(background);

			//iterate through the tunnels list to draw the tunnels
			for (int i = 0; i < tunnels.size(); i++) {
				window.draw(tunnels[i]);
			}

			//draw the sprite for the player
			window.draw(player.sprite);

			// if the boss is spawned the update and draw the boss
			if (bossNum == 1)
			{
				boss.update();
				boss.updateMovement(playerCenter);
				window.draw(boss.sprite);
			}

			// if bossNum is -1 then the boss is dead 
			if (bossNum == -1)
			{
				//erase all of the boss' bullets that are on the screen
				for (int i = 0; i < boss.gun.bullets.size(); i++)
				{
					boss.gun.bullets.erase(boss.gun.bullets.begin() + i);
				}
				// set and draw the final wave message
				waveMsg.setPosition(84, 344);
				waveMsg.setString("I killed him Lord, I did it for you. Bring me salvation.");
				window.draw(waveMsg);

				Time winTimer = won.getElapsedTime(); // start the win timer so that the message is shown for 6 seconds
				if (winTimer.asSeconds() > 10)
				{
					window.setVisible(false);
					GameWon win; // go to the game won screen after 6 seconds
					while (!win.isStarted())
					{
						if (win.isClosed())
						{
							return 0;
						}
					}
					window.setVisible(true);
				}


			}

			// Draw all the text for the screen, player HUD
			window.draw(currencyText);
			window.draw(healthText);
			window.draw(gunText);
			window.draw(playerHealthSprite);
			window.draw(currencySprite);
			window.draw(wave);

			//draw the wave message for wave intermissions
			if (waves < 1)
			{
				window.draw(waveMsg);
			}

			//updates position of all bullets and draws the graphic to screen
			for (int i = 0; i < player.weapon.bullets.size(); i++) {
				player.weapon.bullets[i].update();
				window.draw(player.weapon.bullets[i].shape);
			}

			//updates postion of all boss bullets and draws the graphic to screen
			for (int i = 0; i < boss.gun.bullets.size(); i++) {
				boss.gun.bullets[i].update();
				window.draw(boss.gun.bullets[i].shape);
			}

			//updates postion of all enemies and draws them to screen
			for (int i = 0; i < enemyArray.size(); i++) {
				enemyArray[i].update();
				enemyArray[i].updateMovement(playerCenter);
				window.draw(enemyArray[i].sprite);
			}

		}

		window.display();
	}

	return 0;
}
/** @fn void waveFunction()
* @brief - A function to keep track of waves and spawn enemies and the boss.
* @param enemyArray - a vector list that contains all of the current enemies on screen
* @param enemy1 - Enemy object for the first enemy type
* @param enemy2 - Enemy object for the second enemy type
* @param enemy3 - Enemy object for the third enmey type
* @param time1 - timer for the respawn of enemy1 types
* @param time2 - timer for the respawn of enemy2 types
* @param time3 - timer for the respawn of enemy3 types
* @param waveCountdown - int countdown for when the wave will start
* @param tunnels - a vector list containing all of the tunnels (spawn points) for the enemies
* @param healthText - a Text variable to display the players health
* @param currencyText - a Text variable to display the players currency
* @param wave - a Text variable to display the current wave
* @param waveMsg - a Text variable to display the wave message for each wave's story
* @param player - a Player object to represent the player (user)
* @param waves - an int variable to represent the current wave
* @param numEnemies - an int variable to keep track of the total number of enemies for each round
* @param bossNum - an int variable to keep track of whether or not the boss is spawned
* @param num1 - an int variable to keep track of the number of enemies of type 1
* @param num2 -  an int variable to keep track of the number of enemies of type 2
* @param num3 -  an int variable to keep track of the number of enemies of type 3
* The waveFunction will use the waves variable to keep track of what wave the game is currently on. For each wave a certain amount of enemies are spawned and a certain amount of each type is spawned.
* The enemies are spawned randomly to tunnels around the map and each type is spawned at a different rate.
* At the end of each wave there is a wave message to be displayed to the screen.
* When the game reaches wave 10, the boss will be spawned by setting bossNum to 1 and it will be despawned if it is defeated by setting bossNum to -1
*/
void waveFunction(vector<Enemy> &enemyArray, Enemy &enemy1, Enemy &enemy2, Enemy &enemy3, Clock &time1, Clock &time2, Clock &time3, int &waveCountdown, vector<RectangleShape> &tunnels, Text &healthText, Text &currencyText, Text &wave, Text &waveMsg, Player &player, int &waves, int &numEnemies, int &bossNum, int &num1, int &num2, int &num3)
{
	int enemyPos; //an int for spanwning the enemies at a random tunnel

	// If the waves is less than 1 (will happen at the beginning and inbetween waves)
	if (waves < 1) {
		waveCountdown--;
		wave.setString("Next wave in: " + to_string(waveCountdown / 60));
		if (waveCountdown == 0) { 
			waves = waves * (-1);
			waves++;
		}
	}

	// Code block for spawning in enemies for wave 1
	if (waves == 1)
	{
		wave.setString("Wave: " + to_string(waves)); // Set the wave string
		waveMsg.setString("Why does this keep happening to me? I don't want to be here."); // Set the messge for the beginning of the wave
		
		// Spawn the number of enemies of type 1 for the current wave
		if (num1 < 1)
		{
			enemyPos = rand() % tunnels.size();  // Random spawning for tunnels
			enemy1.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy1);
			num1++;
		}

		// Spawn the number of enemies of type 2 for the current wave
		if (num2 < 1)
		{
			enemyPos = rand() % tunnels.size();  // Random spawning for tunnels
			enemy2.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy2);
			num2++;
		}

		// Spawn the number of enemies of type 3 for the current wave
		if (num3 < 1)
		{
			enemyPos = rand() % tunnels.size(); // Random spawning for tunnels
			enemy3.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy3);
			num3++;
		}

		// If all of the enemies in the wave have been defeated and the correct number of enemies for the current wave have spawned then
		if (enemyArray.size() == 0 && numEnemies == (num1 + num2 + num3))
		{
			
			waveCountdown = 659;  // Count down variable for the waveMsg string to be displayed
			waves = waves * (-1);  // Flip the wave number to be able to have an intermission between waves

			numEnemies += 2;  // Increase the total number of enemies to spawnw for the next round

			//If the playerHP is not full then increase it
			if (player.playerHP < 10)
			{
				player.playerHP++;
				healthText.setString(to_string(player.playerHP));
			}

			// Reset the current amount of enemies spawned in
			num1 = 0;
			num2 = 0;
			num3 = 0;
		}
	}

	// Code block for spawning in enemies for wave 2
	if (waves == 2)
	{
		wave.setString("Wave: " + to_string(waves)); // Set the wave string
		waveMsg.setPosition(240, 344);
		waveMsg.setString("Where are you God? Why have you left me?"); // Set the message for the beginning of the wave
		Time spawn1 = time1.getElapsedTime();
		Time spawn2 = time1.getElapsedTime();
		Time spawn3 = time1.getElapsedTime();
		// Spawn the number of enemies of type 1 for the current wave
		if (num1 < 2 && spawn1.asSeconds() > 2)
		{
			time1.restart();
			enemyPos = rand() % tunnels.size();  // Random spawning for tunnels
			enemy1.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy1);
			num1++;
		}

		// Spawn the number of enemies of type 2 for the current wave
		if (num2 < 2 && spawn2.asSeconds() > 1)
		{
			time2.restart();
			enemyPos = rand() % tunnels.size();  // Random spawning for tunnels
			enemy2.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy2);
			num2++;
		}

		// Spawn the number of enemies of type 3 for the current wave
		if (num3 < 1 && spawn3.asSeconds() > 2)
		{
			time3.restart();
			enemyPos = rand() % tunnels.size(); // Random spawning for tunnels
			enemy3.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy3);
			num3++;
		}

		// If all of the enemies in the wave have been defeated and the correct number of enemies for the current wave have spawned then
		if (enemyArray.size() == 0 && numEnemies == (num1 + num2 + num3))
		{

			waveCountdown = 659;  // Count down variable for the waveMsg string to be displayed
			waves = waves * (-1);  // Flip the wave number to be able to have an intermission between waves

			numEnemies += 2;  // Increase the total number of enemies to spawnw for the next round

			//If the playerHP is not full then increase it
			if (player.playerHP < 10)
			{
				player.playerHP++;
				healthText.setString(to_string(player.playerHP));
			}

			// Reset the current amount of enemies spawned in
			num1 = 0;
			num2 = 0;
			num3 = 0;
		}
	}

	// Code block for spawning in enemies for wave 3
	if (waves == 3)
	{
		wave.setString("Wave: " + to_string(waves)); // Set the wave string
		waveMsg.setPosition(390, 344);
		waveMsg.setString("How do I get out of here?"); // Set the message for the beginning of the wave

		Time spawn1 = time1.getElapsedTime();
		Time spawn2 = time1.getElapsedTime();
		Time spawn3 = time1.getElapsedTime();
		// Spawn the number of enemies of type 1 for the current wave
		if (num1 < 2 && spawn1.asSeconds() > 2)
		{
			time1.restart();
			enemyPos = rand() % tunnels.size();  // Random spawning for tunnels
			enemy1.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy1);
			num1++;
		}

		// Spawn the number of enemies of type 2 for the current wave
		if (num2 < 3 && spawn2.asSeconds() > 1)
		{
			time2.restart();
			enemyPos = rand() % tunnels.size();  // Random spawning for tunnels
			enemy2.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy2);
			num2++;
		}

		// Spawn the number of enemies of type 3 for the current wave
		if (num3 < 2 && spawn3.asSeconds() > 2)
		{
			time3.restart();
			enemyPos = rand() % tunnels.size(); // Random spawning for tunnels
			enemy3.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy3);
			num3++;
		}

		// If all of the enemies in the wave have been defeated and the correct number of enemies for the current wave have spawned then
		if (enemyArray.size() == 0 && numEnemies == (num1 + num2 + num3))
		{

			waveCountdown = 659;  // Count down variable for the waveMsg string to be displayed
			waves = waves * (-1);  // Flip the wave number to be able to have an intermission between waves

			numEnemies += 2;  // Increase the total number of enemies to spawnw for the next round

			//If the playerHP is not full then increase it
			if (player.playerHP < 10)
			{
				player.playerHP++;
				healthText.setString(to_string(player.playerHP));
			}

			// Reset the current amount of enemies spawned in
			num1 = 0;
			num2 = 0;
			num3 = 0;
		}
	}

	// Code block for spawning in enemies for wave 4
	if (waves == 4)
	{
		wave.setString("Wave: " + to_string(waves)); // Set the wave string
		waveMsg.setPosition(225, 344); 
		waveMsg.setString("This is all a dream. None of this is real."); // Set the message for the beginning of the wave

		Time spawn1 = time1.getElapsedTime();
		Time spawn2 = time1.getElapsedTime();
		Time spawn3 = time1.getElapsedTime();
		// Spawn the number of enemies of type 1 for the current wave
		if (num1 < 3 && spawn1.asSeconds() > 2)
		{
			time1.restart();
			enemyPos = rand() % tunnels.size();  // Random spawning for tunnels
			enemy1.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy1);
			num1++;
		}

		// Spawn the number of enemies of type 2 for the current wave
		if (num2 < 3 && spawn2.asSeconds() > 1)
		{
			time2.restart();
			enemyPos = rand() % tunnels.size();  // Random spawning for tunnels
			enemy2.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy2);
			num2++;
		}

		// Spawn the number of enemies of type 3 for the current wave
		if (num3 < 3 && spawn3.asSeconds() > 2)
		{
			time3.restart();
			enemyPos = rand() % tunnels.size(); // Random spawning for tunnels
			enemy3.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy3);
			num3++;
		}

		// If all of the enemies in the wave have been defeated and the correct number of enemies for the current wave have spawned then
		if (enemyArray.size() == 0 && numEnemies == (num1 + num2 + num3))
		{

			waveCountdown = 659;  // Count down variable for the waveMsg string to be displayed
			waves = waves * (-1);  // Flip the wave number to be able to have an intermission between waves

			numEnemies += 2;  // Increase the total number of enemies to spawnw for the next round

			//If the playerHP is not full then increase it
			if (player.playerHP < 10)
			{
				player.playerHP++;
				healthText.setString(to_string(player.playerHP));
			}

			// Reset the current amount of enemies spawned in
			num1 = 0;
			num2 = 0;
			num3 = 0;
		}
	}

	// Code block for spawning in enemies for wave 5
	if (waves == 5)
	{
		wave.setString("Wave: " + to_string(waves)); // Set the wave string
		waveMsg.setPosition(254, 344);
		waveMsg.setString("Just wake up. Nothing is real. Wake up."); // Set the message for the beginning of the wave

		Time spawn1 = time1.getElapsedTime();
		Time spawn2 = time1.getElapsedTime();
		Time spawn3 = time1.getElapsedTime();
		// Spawn the number of enemies of type 1 for the current wave
		if (num1 < 4 && spawn1.asSeconds() > 2)
		{
			time1.restart();
			enemyPos = rand() % tunnels.size();  // Random spawning for tunnels
			enemy1.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy1);
			num1++;
		}

		// Spawn the number of enemies of type 2 for the current wave
		if (num2 < 4 && spawn2.asSeconds() > 1)
		{
			time2.restart();
			enemyPos = rand() % tunnels.size();  // Random spawning for tunnels
			enemy2.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy2);
			num2++;
		}

		// Spawn the number of enemies of type 3 for the current wave
		if (num3 < 3 && spawn3.asSeconds() > 2)
		{
			time3.restart();
			enemyPos = rand() % tunnels.size(); // Random spawning for tunnels
			enemy3.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy3);
			num3++;
		}

		// If all of the enemies in the wave have been defeated and the correct number of enemies for the current wave have spawned then
		if (enemyArray.size() == 0 && numEnemies == (num1 + num2 + num3))
		{

			waveCountdown = 659;  // Count down variable for the waveMsg string to be displayed
			waves = waves * (-1);  // Flip the wave number to be able to have an intermission between waves

			numEnemies += 2;  // Increase the total number of enemies to spawnw for the next round

			//If the playerHP is not full then increase it
			if (player.playerHP < 10)
			{
				player.playerHP++;
				healthText.setString(to_string(player.playerHP));
			}

			// Reset the current amount of enemies spawned in
			num1 = 0;
			num2 = 0;
			num3 = 0;
		}
	}

	// Code block for spawning in enemies for wave 6
	if (waves == 6)
	{
		wave.setString("Wave: " + to_string(waves)); // Set the wave text
		waveMsg.setPosition(94, 344);
		waveMsg.setString("I can hear something coming. I need to get out of here."); // Set the message for the beginning of the wave

		Time spawn1 = time1.getElapsedTime();
		Time spawn2 = time1.getElapsedTime();
		Time spawn3 = time1.getElapsedTime();
		// Spawn the number of enemies of type 1 for the current wave
		if (num1 < 4 && spawn1.asSeconds() > 2)
		{
			time1.restart();
			enemyPos = rand() % tunnels.size();  // Random spawning for tunnels
			enemy1.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy1);
			num1++;
		}

		// Spawn the number of enemies of type 2 for the current wave
		if (num2 < 4 && spawn2.asSeconds() > 1)
		{
			time2.restart();
			enemyPos = rand() % tunnels.size();  // Random spawning for tunnels
			enemy2.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy2);
			num2++;
		}

		// Spawn the number of enemies of type 3 for the current wave
		if (num3 < 5 && spawn3.asSeconds() > 2)
		{
			time3.restart();
			enemyPos = rand() % tunnels.size(); // Random spawning for tunnels
			enemy3.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy3);
			num3++;
		}

		// If all of the enemies in the wave have been defeated and the correct number of enemies for the current wave have spawned then
		if (enemyArray.size() == 0 && numEnemies == (num1 + num2 + num3))
		{

			waveCountdown = 659;  // Count down variable for the waveMsg string to be displayed
			waves = waves * (-1);  // Flip the wave number to be able to have an intermission between waves

			numEnemies += 2;  // Increase the total number of enemies to spawnw for the next round

			//If the playerHP is not full then increase it
			if (player.playerHP < 10)
			{
				player.playerHP++;
				healthText.setString(to_string(player.playerHP));
			}

			// Reset the current amount of enemies spawned in
			num1 = 0;
			num2 = 0;
			num3 = 0;
		}
	}

	// Code block for spawning in enemies for wave 7
	if (waves == 7)
	{
		wave.setString("Wave: " + to_string(waves)); // Set the wave string
		waveMsg.setPosition(64, 344);
		waveMsg.setString("I don't want to keep killing. The Lord says I cannot kill."); // Set the messge for the beginning of the wave

		Time spawn1 = time1.getElapsedTime();
		Time spawn2 = time1.getElapsedTime();
		Time spawn3 = time1.getElapsedTime();
		// Spawn the number of enemies of type 1 for the current wave
		if (num1 < 5 && spawn1.asSeconds() > 2)
		{
			time1.restart();
			enemyPos = rand() % tunnels.size();  // Random spawning for tunnels
			enemy1.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy1);
			num1++;
		}

		// Spawn the number of enemies of type 2 for the current wave
		if (num2 < 5 && spawn2.asSeconds() > 1)
		{
			time2.restart();
			enemyPos = rand() % tunnels.size();  // Random spawning for tunnels
			enemy2.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy2);
			num2++;
		}

		// Spawn the number of enemies of type 3 for the current wave
		if (num3 < 5 && spawn3.asSeconds() > 2)
		{
			time3.restart();
			enemyPos = rand() % tunnels.size(); // Random spawning for tunnels
			enemy3.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy3);
			num3++;
		}

		// If all of the enemies in the wave have been defeated and the correct number of enemies for the current wave have spawned then
		if (enemyArray.size() == 0 && numEnemies == (num1 + num2 + num3))
		{

			waveCountdown = 659;  // Count down variable for the waveMsg string to be displayed
			waves = waves * (-1);  // Flip the wave number to be able to have an intermission between waves

			numEnemies += 2;  // Increase the total number of enemies to spawnw for the next round

			//If the playerHP is not full then increase it
			if (player.playerHP < 10)
			{
				player.playerHP++;
				healthText.setString(to_string(player.playerHP));
			}

			// Reset the current amount of enemies spawned in
			num1 = 0;
			num2 = 0;
			num3 = 0;
		}
	}

	// Code block for spawning in enemies for wave 8
	if (waves == 8)
	{
		wave.setString("Wave: " + to_string(waves)); // Set the wave string
		waveMsg.setPosition(300, 344);
		waveMsg.setString("How am I going to pay for my sins?"); // Set the messge for the beginning of the wave

		Time spawn1 = time1.getElapsedTime();
		Time spawn2 = time1.getElapsedTime();
		Time spawn3 = time1.getElapsedTime();
		// Spawn the number of enemies of type 1 for the current wave
		if (num1 < 5 && spawn1.asSeconds() > 2)
		{
			time1.restart();
			enemyPos = rand() % tunnels.size();  // Random spawning for tunnels
			enemy1.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy1);
			num1++;
		}

		// Spawn the number of enemies of type 2 for the current wave
		if (num2 < 7 && spawn2.asSeconds() > 1)
		{
			time2.restart();
			enemyPos = rand() % tunnels.size();  // Random spawning for tunnels
			enemy2.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy2);
			num2++;
		}

		// Spawn the number of enemies of type 3 for the current wave
		if (num3 < 5 && spawn3.asSeconds() > 2)
		{
			time3.restart();
			enemyPos = rand() % tunnels.size(); // Random spawning for tunnels
			enemy3.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy3);
			num3++;
		}

		// If all of the enemies in the wave have been defeated and the correct number of enemies for the current wave have spawned then
		if (enemyArray.size() == 0 && numEnemies == (num1 + num2 + num3))
		{

			waveCountdown = 659;  // Count down variable for the waveMsg string to be displayed
			waves = waves * (-1);  // Flip the wave number to be able to have an intermission between waves

			numEnemies += 2;  // Increase the total number of enemies to spawnw for the next round

			//If the playerHP is not full then increase it
			if (player.playerHP < 10)
			{
				player.playerHP++;
				healthText.setString(to_string(player.playerHP));
			}

			// Reset the current amount of enemies spawned in
			num1 = 0;
			num2 = 0;
			num3 = 0;
		}
	}

	// Code block for spawning in enemies for wave 9
	if (waves == 9)
	{
		wave.setString("Wave: " + to_string(waves)); // Set the wave string
		waveMsg.setPosition(284, 344);
		waveMsg.setString("He is coming, I need to destroy him!"); // Set the messge for the beginning of the wave

		Time spawn1 = time1.getElapsedTime();
		Time spawn2 = time1.getElapsedTime();
		Time spawn3 = time1.getElapsedTime();
		// Spawn the number of enemies of type 1 for the current wave
		if (num1 < 6 && spawn1.asSeconds() > 2)
		{
			time1.restart();
			enemyPos = rand() % tunnels.size();  // Random spawning for tunnels
			enemy1.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy1);
			num1++;
		}

		// Spawn the number of enemies of type 2 for the current wave
		if (num2 < 7 && spawn2.asSeconds() > 1)
		{
			time2.restart();
			enemyPos = rand() % tunnels.size();  // Random spawning for tunnels
			enemy2.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy2);
			num2++;
		}

		// Spawn the number of enemies of type 3 for the current wave
		if (num3 < 6 && spawn3.asSeconds() > 2)
		{
			time3.restart();
			enemyPos = rand() % tunnels.size(); // Random spawning for tunnels
			enemy3.rect.setPosition(tunnels[enemyPos].getPosition());
			enemyArray.push_back(enemy3);
			num3++;
		}

		// If all of the enemies in the wave have been defeated and the correct number of enemies for the current wave have spawned then
		if (enemyArray.size() == 0 && numEnemies == (num1 + num2 + num3))
		{

			waveCountdown = 659;  // Count down variable for the waveMsg string to be displayed
			waves = waves * (-1);  // Flip the wave number to be able to have an intermission between waves

			numEnemies += 2;  // Increase the total number of enemies to spawnw for the next round

			//If the playerHP is not full then increase it
			if (player.playerHP < 10)
			{
				player.playerHP++;
				healthText.setString(to_string(player.playerHP));
			}

			// Reset the current amount of enemies spawned in
			num1 = 0;
			num2 = 0;
			num3 = 0;
		}
	}
	
	// Code block for the boss wave
	if (waves == 10)
	{
		if (bossNum == 0 || bossNum == 1) // If the boss has spawned or if he is not spawned then set the bossNum to 1
		{
			bossNum = 1;
		}
		if(bossNum == -1)  // If the boss is dead then set the bossNum to -1
		{
			bossNum == -1;
		}
		
	}
}


/** @fn void playerControls()
* @brief - A function to handle player mouse position for shooting and also player input for moving
* @param counter - an int counter used for switching sprite animations
* @param mousePosWindow - a Vector2f variable to represent the postion of the mouse on the window
* @param player - a Player variable for the player (user)
* The player is able to aim in 360 degrees with the mouse position and the sprite should reflect what direction the player is aiming.
* The player will also be able to move up, down, left, and right with the keys wasd.
*/
void playerControls(int &counter, Vector2f &mousePosWindow, Player &player)
{

	// Use trigonometry to rotate the sprite
	float dx = abs(player.sprite.getPosition().x - mousePosWindow.x); // calculate the x of the triangle between the player and the mouse
	float dy = abs(player.sprite.getPosition().y - mousePosWindow.y); // calculate the y of the triangle between the player and the mouse

	float theta = (atan2(dy, dx)) * 180 / 3.14159265;  // calculate the theta of that triangle and convert it

	if (theta < 30 && mousePosWindow.x < player.sprite.getPosition().x) // left turning
	{
		player.sprite.setTextureRect(IntRect(0, 64, 64, 64));
	}
	if (theta < 30 && mousePosWindow.x > player.sprite.getPosition().x) // right turning
	{
		player.sprite.setTextureRect(IntRect(0, 64 * 3, 64, 64));
	}
	if (theta > 30 && mousePosWindow.y > player.sprite.getPosition().y) // bottom turning
	{
		player.sprite.setTextureRect(IntRect(0, 64 * 2, 64, 64));
	}
	if (theta > 30 && mousePosWindow.y < player.sprite.getPosition().y) // top turning
	{
		player.sprite.setTextureRect(IntRect(0, 0, 64, 64));
	}

	// handle player movement and out of bounds
	if (Keyboard::isKeyPressed(Keyboard::A) && player.sprite.getPosition().x > 10) { // if the player goes left and check out of bounds
		player.sprite.move(-5.f, 0);
		player.sprite.setTextureRect(IntRect(counter * 64, 64, 64, 64)); // use counter to switch sprite positions
	}
	if (Keyboard::isKeyPressed(Keyboard::D) && player.sprite.getPosition().x < 1280 - 60) { // if the player goes to the right and check out of bounds
		player.sprite.move(5.f, 0);
		player.sprite.setTextureRect(IntRect(counter * 64, 64 * 3, 64, 64)); // use counter to switch sprite positions
	}
	if (Keyboard::isKeyPressed(Keyboard::W) && player.sprite.getPosition().y > 32) { // if the player goes up and check out of bounds
		player.sprite.move(0, -5.f);
		player.sprite.setTextureRect(IntRect(counter * 64, 0, 64, 64)); // use counter to swtich sprite positions
	}
	if (Keyboard::isKeyPressed(Keyboard::S) && player.sprite.getPosition().y < 720 - 90) { // if the player goes down and check out of bounds
		player.sprite.move(0, 5.f);
		player.sprite.setTextureRect(IntRect(counter * 64, 64 * 2, 64, 64)); // use counter to switch sprite positions
	}

	counter++;
	// counter for sprite switching acting like a timer between animations
	if (counter == 8)
	{
		counter = 0;
	}

}

/** @fn void playerShoot()
* @brief - a function to handle all the different shooting types that the player can have
* @param player - a Player variable for the player (user)
* @param fireRate - an int variable to change the fire rate of weapons
* @param playerCenter - a Vector2f variable to determine the center of the player on the window
* @param aimDirNorm - the normalized Vector2f variable of aimDir
* @param aimDir - a Vector2f variable for the direction of the player aim
* @param mousePosWindow - a Vector2f variable to represent the postion of the mouse on the window
* The player will have different shooting mechanics for the different weapon types that exist.
* Each shooting mechanic is different, especially the shotgun mechanic which is unlike any other gun type.
*/
void playerShoot(Player &player, int &fireRate, Vector2f &playerCenter, Vector2f &aimDirNorm, Vector2f &aimDir, Vector2f &mousePosWindow)
{
	//shooting when mouse button is pressed and fire rate is reached 0
	if (Mouse::isButtonPressed(Mouse::Left) && fireRate == 0) {

		// pistol shooting type
		if (player.weapon.name == "Pistol") 
		{
			player.weapon.shoot(playerCenter, aimDirNorm);
			fireRate = 50;
		}
		// smg shooting type
		if (player.weapon.name == "Smg")
		{
			player.weapon.shoot(playerCenter, aimDirNorm);
			fireRate = 10;
		}
		// shotgun shooting type
		if (player.weapon.name == "Shotgun")
		{
			//initilize varibles which hold the line which runs
						//perpenticular to the line that runs from the mouse to player
			double xDiff = mousePosWindow.x - playerCenter.x;
			double yDiff = mousePosWindow.y - playerCenter.y;
			double perpX = yDiff * (-1);
			double perpY = xDiff;

			//shoots the middle bullet
			player.weapon.shoot(playerCenter, aimDirNorm);

			//adds the perpendicular line to the mouse's postion
			Vector2f newMousePos = mousePosWindow + Vector2f(perpX / 8, perpY / 8);

			//updates aim direction math for bullet direction
			aimDir = newMousePos - playerCenter;
			aimDirNorm = aimDir / (float)(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));

			//shoots the middle-right bullet
			player.weapon.shoot(playerCenter, aimDirNorm);

			//adds the perpendicular line to the mouse's postion
			newMousePos = mousePosWindow - Vector2f(perpX / 8, perpY / 8);

			//updates aim direction math for bullet direction
			aimDir = newMousePos - playerCenter;
			aimDirNorm = aimDir / (float)(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));

			//shoots middle-left bullet
			player.weapon.shoot(playerCenter, aimDirNorm);

			//adds the perpendicular line to the mouse's postion
			newMousePos = mousePosWindow + Vector2f(perpX / 4, perpY / 4);

			//updates aim direction math for bullet direction
			aimDir = newMousePos - playerCenter;
			aimDirNorm = aimDir / (float)(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));

			//shoots right bullet
			player.weapon.shoot(playerCenter, aimDirNorm);

			//adds the perpendicular line to the mouse's postion
			newMousePos = mousePosWindow - Vector2f(perpX / 4, perpY / 4);

			//updates aim direction math for bullet direction
			aimDir = newMousePos - playerCenter;
			aimDirNorm = aimDir / (float)(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2)));

			//shoots left bullet
			player.weapon.shoot(playerCenter, aimDirNorm);

			//lock shooting ability for 50 ticks
			fireRate = 50;
		}
		// rifle shooting type
		if (player.weapon.name == "Rifle")
		{
			player.weapon.shoot(playerCenter, aimDirNorm);
			fireRate = 20;
		}
		// launcher shooting type
		if (player.weapon.name == "Launcher")
		{
			player.weapon.shoot(playerCenter, aimDirNorm);
			fireRate = 50;
		}

	}

	// if statement to decrease the fire rate after it has been set. This will act as a timer inbetween shots
	if (fireRate > 0)
	{
		fireRate--;
	}
}


/** @fn void bossShoot()
* @brief - a function to handle the shooting for the boss
* @param playerCenter - a Vector2f variable to determine the center of the player on the window
* @param bossPos - a Vector2f variable for the postion of the boss on the window
* @param playerNorm - a Vector2f variable for the normalized vector of the player position
* @param bossAimDir - a Vector 2f variable for the normalized vector of the boss aim
* @param bossRate - an int variable for the fire rate of the boss weapon
* @param bossNum - an int variable to see if the boss is spawned or not
* @param boss - a Boss variable to represent the boss
* The boss only has one shooting method, it shoots like how a player shoots a shotgun, but there are less bullets and the bullet sizes are larger
*/
void bossShoot(Vector2f &playerCenter, Vector2f &bossPos, Vector2f &playerNorm, Vector2f &bossAimDir, int &bossRate, int &bossNum, Boss &boss)
{
	// if the boss has spawned and the fire rate is 0
	// This shooting mechanic is the same as the player shotgun, see shotgun in playerShoot for more details
	if (bossNum == 1 && bossRate == 0)
	{
		double xDiff = playerCenter.x - bossPos.x;
		double yDiff = playerCenter.y - bossPos.y;

		double perpX = yDiff * (-1);
		double perpY = xDiff;

		boss.gun.shoot(bossPos, playerNorm);


		Vector2f  newPlayerCenter = playerCenter + Vector2f(perpX / 4, perpY / 4);

		bossAimDir = newPlayerCenter - bossPos;
		playerNorm = bossAimDir / (float)(sqrt(pow(bossAimDir.x, 2) + pow(bossAimDir.y, 2)));

		boss.gun.shoot(bossPos, playerNorm);

		newPlayerCenter = playerCenter - Vector2f(perpX / 4, perpY / 4);

		bossAimDir = newPlayerCenter - bossPos;
		playerNorm = bossAimDir / (float)(sqrt(pow(bossAimDir.x, 2) + pow(bossAimDir.y, 2)));

		boss.gun.shoot(bossPos, playerNorm);


		bossRate = 50;
	}

	// if statement to decrease the fire rate after it has been set. This will act as a timer inbetween shots
	if (bossRate > 0)
	{
		bossRate--;

	}

}


/** @fn void bulletCollisions()
* @brief - a function to handle bullet collisions between player, enemies, and the boss
* @param player - a Player variable for the player (user)
* @param enemyArray - - a vector list that contains all of the current enemies on screen
* @param boss - a Boss variable to represent the boss
* @param healthText - a Text variable to display the players health
* @param currencyText - a Text variable to display the players currency
* @param bossNum - an int variable to see if the boss is spawned or not
* @param window - the variable of the game window
* This function will handle player bullets hitting enemies and the boss (if it is spawned) and it also handles bullet collision if the boss bullets hit the player.
*/
void bulletCollisions(Player &player, vector<Enemy> &enemyArray, Boss &boss, Text &healthText, Text &currencyText, int &bossNum, RenderWindow &window)
{
	// for loop to increment over all the player bullets
	for (size_t i = 0; i < player.weapon.bullets.size(); i++) {
		player.weapon.bullets[i].shape.move(player.weapon.bullets[i].currVelocity); // move the bullets

		// if statement to check if the bullets have gone outside of the window, if they have gone outside of the window then erase them. If we do not erase these bullets then the bullets list will increase to a level where the game will crash.
		if (player.weapon.bullets[i].shape.getPosition().x < 0 || player.weapon.bullets[i].shape.getPosition().x > window.getSize().x || player.weapon.bullets[i].shape.getPosition().y < 0 || player.weapon.bullets[i].shape.getPosition().y > window.getSize().y) {
			player.weapon.bullets.erase(player.weapon.bullets.begin() + i);
		}
		else // Else the bullets are within the bounds of the window
		{
			// If the boss is spawned then check for bullet collision with the boss
			if (bossNum == 1)
			{
				// if a bullet intersects with the boss
				if (player.weapon.bullets[i].shape.getGlobalBounds().intersects(boss.rect.getGlobalBounds()))
				{
					player.weapon.bullets.erase(player.weapon.bullets.begin() + i); // erase the bullet
					boss.health = boss.health - player.weapon.damage; // decrease the boss health

					// if the boss health is lower or equal to 0, then the boss is dead. Set bossNum to -1 to represent that the boss has died.
					if (boss.health <= 0)
					{
						bossNum = -1;
					}
				}
			}

			// for loop to iterate over all of the enemies on the screen
			for (int k = 0; k < enemyArray.size(); k++)
			{
				// If a players bullet intersects with an enemy
				if (player.weapon.bullets[i].shape.getGlobalBounds().intersects(enemyArray[k].rect.getGlobalBounds()))
				{
					player.weapon.bullets.erase(player.weapon.bullets.begin() + i); // erase the bullet
					enemyArray[k].health = enemyArray[k].health - player.weapon.damage; // decrease the health of the enemy

					// if the enemy is dead
					if (enemyArray[k].health <= 0)
					{
						enemyArray.erase(enemyArray.begin() + k); // erase the enemy for the enemyArray list
						player.currency++;  // increase the players currency
						currencyText.setString(to_string(player.currency));  // update the currency string to be displayed onto the screen
					}

					break; // break the current loop
				}

			}
		}
	}

	// If the boss is spawned then check for the boss's bullet collision
	if (bossNum == 1)
	{
		// iterate over the boss's bullets
		for (size_t i = 0; i < boss.gun.bullets.size(); i++) {
			boss.gun.bullets[i].shape.move(boss.gun.bullets[i].currVelocity); // move the bullets

			// if the boss's bullets go out of the bounds of the window then erase them.
			if (boss.gun.bullets[i].shape.getPosition().x < 0 || boss.gun.bullets[i].shape.getPosition().x > window.getSize().x || boss.gun.bullets[i].shape.getPosition().y < 0 || boss.gun.bullets[i].shape.getPosition().y > window.getSize().y) {
				boss.gun.bullets.erase(boss.gun.bullets.begin() + i);

			}
			else // else the boss's bullets are within the bounds of the window
			{
				// if a bullet has intersected with the player then
				if (boss.gun.bullets[i].shape.getGlobalBounds().intersects(player.rect.getGlobalBounds()))
				{
					boss.gun.bullets.erase(boss.gun.bullets.begin() + i); // erase the bullet
					player.playerHP = player.playerHP - boss.getAttackDamage(); // decrease the player HP
					healthText.setString(to_string(player.playerHP)); // update the player health text to be displayed
				}


			}
		}

	}

}


/** @fn void playerCollisions()
* @brief - a function to handle collisions between player, enemies and the boss
* @param player - a Player variable for the player (user)
* @param boss - a Boss variable to represent the boss
* @param healthText - a Text variable to display the players health
* @param bossNum - an int variable to see if the boss is spawned or not
* @param clock - a Clock variable used as an invincibility timer if the player collides with an enemy
* @param clock2 - a Clock variable used as an invincibility timer if the player collides with the boss
* @param enemyArray - a vector list that contains all of the current enemies on screen
* This function will check the global bounds of the player with the bounds of the enemies or the boss to see if there is a collision.
* If there is a collision then the player uses health and a invincibility timer starts so that the player is not damaged again right away.
*/
void playerCollisions(Player &player, Boss &boss, Text &healthText, int &bossNum, Clock &clock, Clock &clock2, vector<Enemy> &enemyArray)
{
	Time inv = clock.getElapsedTime(); // timer for invincibility if the player interacts with an enemy
	//iterate through all of the enemies
	for (int k = 0; k < enemyArray.size(); k++)
	{
		// if an enemy collides with the player
		if (enemyArray[k].rect.getGlobalBounds().intersects(player.rect.getGlobalBounds()))
		{
			// wait 0.5 seconds
			if (inv.asSeconds() >= 0.5)
			{
				clock.restart(); // restart the clock for other collisions
				player.playerHP = player.playerHP - enemyArray[k].getAttackDamage(); // decrease player health

				healthText.setString(to_string(player.playerHP)); // update the health text to be displayed to the screen
				break; // break the loop
			}

		}

	}

	Time inv2 = clock2.getElapsedTime();  // timer for invincibility if the player interacts with the boss
	if (bossNum == 1) // if the boss is spawned
	{
		// check for collision with the boss and the player
		if (boss.rect.getGlobalBounds().intersects(player.rect.getGlobalBounds()))
		{
			// wait 0.5 seconds
			if (inv2.asSeconds() >= 0.5)
			{
				clock2.restart();  // restart the clock for other collisions
				player.playerHP = player.playerHP - boss.getAttackDamage();  // decrease player health
				healthText.setString(to_string(player.playerHP)); // update the health text to be displayed to the screen
			}
		}

	}

}
