
output: Bullet.o Enemy.o Entity.o Gun.o Main.o Player.o MainMenu.o ShopMenu.o GameOver.o GameWon.o Boss.o
	g++ Bullet.o Enemy.o Entity.o Gun.o Main.o Player.o MainMenu.o ShopMenu.o GameOver.o GameWon.o Boss.o -o game -lsfml-graphics -lsfml-window -lsfml-system

Bullet.o: Bullet.cpp Bullet.h
	g++ -c Bullet.cpp

Enemy.o: Enemy.cpp Enemy.h
	g++ -c Enemy.cpp

Entity.o: Entity.cpp Entity.h
	g++ -c Entity.cpp

Gun.o: Gun.cpp Gun.h
	g++ -c Gun.cpp

Main.o: Main.cpp 
	g++ -c Main.cpp

MainMenu.o: MainMenu.cpp MainMenu.h
	g++ -c MainMenu.cpp

ShopMenu.o: ShopMenu.cpp ShopMenu.h
	g++ -c ShopMenu.cpp

Player.o: Player.cpp Player.h
	g++ -c Player.cpp

GameOver.o: GameOver.cpp GameOver.h
	g++ -c GameOver.cpp

GameWon.o: GameWon.cpp GameWon.h
	g++ -c GameWon.cpp

Boss.o: Boss.cpp Boss.h
	g++ -c Boss.cpp

clean:
	rm *.o game
