#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <ctime>
#include <math.h>
#include "Bounce.h"
#include "Special.h"
#include "rocket.h"
#include "pause.h"
#include "Textbox.h"
#include <string.h>
#include <iostream>
#include <sstream>
#include "board.h"
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
int Enemy(int x);
bool distance(float x1, float x2, float y1, float y2);
int checkScore(int score);
int setY(int score, int i);
int menu(sf::RenderWindow& window);
int gameover(sf::RenderWindow& window, int score);
int movePlayer(void);
char nameTemp[10];
char name[10];
char char_array[10];
int main()
{
	int fromMenu = 0;
	special star;
	rocket rock;

	sf::RenderWindow window(sf::VideoMode(640, 1024), "Higher", sf::Style::Close);
	window.setFramerateLimit(60);

	sf::Texture Tbackground;
	Tbackground.loadFromFile("pic/jungle-bck@2x.png");
	sf::Sprite Background;
	Background.setTexture(Tbackground);

	sf::Texture TtreeL, TtreeR;
	TtreeL.loadFromFile("pic/jungle-scroller@2x.png");
	TtreeR.loadFromFile("pic/jungle-scroller@2x.png");
	sf::Sprite treeL, treeR, treeL2, treeR2;
	treeL.setTexture(TtreeL);
	treeL.setTextureRect(sf::IntRect(0, 0, 128, 1024));
	treeL.setOrigin(0, 1024);

	treeR.setTexture(TtreeR);
	treeR.setTextureRect(sf::IntRect(127, 0, 128, 1024));
	treeR.setOrigin(128, 1024);

	treeL2.setTexture(TtreeL);
	treeL2.setTextureRect(sf::IntRect(0, 0, 128, 1024));
	treeL2.setOrigin(0, 1024);

	treeR2.setTexture(TtreeR);
	treeR2.setTextureRect(sf::IntRect(127, 0, 128, 1024));
	treeR2.setOrigin(128, 1024);



	sf::Texture Tplat;
	Tplat.loadFromFile("pic/game-tiles-jungle@2x.png");
	sf::Sprite plat;
	plat.setTexture(Tplat);
	plat.setTextureRect(sf::IntRect(2, 3, 114, 29));

	sf::Texture Tenemy;
	Tenemy.loadFromFile("pic/animation2.png");
	sf::Sprite enemy;
	enemy.setTexture(Tenemy);
	enemy.setTextureRect(sf::IntRect(620, 0, 151, 90));
	enemy.setOrigin(151 / 2 - 30, 45);

	/*sf::RectangleShape player(sf::Vector2f(90, 90));
	player.setFillColor(sf::Color::White);
	player.setOrigin(sf::Vector2f(0, 85));*/
	sf::Texture Tplayer, TplayerLeft, TplayerFire;
	Tplayer.loadFromFile("pic/jungle-right@2x.png");
	TplayerLeft.loadFromFile("pic/jungle-left@2x.png");
	TplayerFire.loadFromFile("pic/Mouse.png");
	sf::Sprite player;
	player.setTexture(Tplayer);
	player.setTextureRect(sf::IntRect(23, 23, 101, 98));

	/*sf::RectangleShape plat(sf::Vector2f(100, 25));
	plat.setFillColor(sf::Color::Yellow);*/

	/*sf::RectangleShape enemy(sf::Vector2f(90, 50));
	enemy.setFillColor(sf::Color::Red);
	enemy.setOrigin(45, 50);*/


	sf::Texture Tbullet;
	Tbullet.loadFromFile("pic/projectile-tiles@2x.png");
	sf::Sprite bullet;
	bullet.setTexture(Tbullet);
	bullet.setTextureRect(sf::IntRect(98, 4, 29, 21));
	/*sf::RectangleShape bullet(sf::Vector2f(10, 10));
	bullet.setFillColor(sf::Color::Blue);*/

	/*sf::RectangleShape bouncer(sf::Vector2f(15, 15));
	bullet.setFillColor(sf::Color::Green);*/
	sf::Texture Tbouncer;
	Tbouncer.loadFromFile("pic/game-tiles-jungle@2x.png");
	sf::Sprite bouncer;
	bouncer.setTexture(Tbouncer);
	bouncer.setTextureRect(sf::IntRect(807, 197, 35, 24));
	bouncer.setOrigin(0, 24);

	sf::Texture Tshoes;
	Tshoes.loadFromFile("pic/game-tiles-jungle@2x.png");
	sf::Sprite shoes;
	shoes.setTexture(Tshoes);
	shoes.setTextureRect(sf::IntRect(601, 409, 57, 42));
	shoes.setOrigin(0, 0);

	sf::Sprite flyingEnemy;
	flyingEnemy.setTexture(Tshoes);
	flyingEnemy.setTextureRect(sf::IntRect(297, 528, 92, 72));
	flyingEnemy.setOrigin(0, 0);

	sf::RectangleShape gameoverBackground(sf::Vector2f(500, 700));
	gameoverBackground.setFillColor(sf::Color::White);

	sf::Font scoreFont;
	scoreFont.loadFromFile("images/LosingGripRegular-YxG4.ttf");

	sf::Text textScore("Score : ", scoreFont, 40);

	//sound
	sf::SoundBuffer bjump;
	bjump.loadFromFile("sound/jump.wav");
	sf::Sound jumpSound;
	jumpSound.setBuffer(bjump);
	jumpSound.setVolume(50);

	sf::SoundBuffer bfeder,bfe;
	bfeder.loadFromFile("sound/feder.wav");
	bfe.loadFromFile("sound/trampoline.wav");
	sf::Sound federSound;
	federSound.setBuffer(bfeder);
	federSound.setVolume(50);

	sf::SoundBuffer bshoot;
	bshoot.loadFromFile("sound/shoot.wav");
	sf::Sound shootSound;
	shootSound.setBuffer(bshoot);
	shootSound.setVolume(25);

	sf::SoundBuffer bEnde;
	bEnde.loadFromFile("sound/monster-crash.wav");
	sf::Sound Ende;
	Ende.setBuffer(bEnde);
	Ende.setVolume(5);
	//backgroud music
	sf::Music bgMusic;
	bgMusic.openFromFile("sound/bgMusic.wav");
	bgMusic.setLoop(true);
	bgMusic.setVolume(3);
	bgMusic.play();

	sf::Sound shoesSound;
	shoesSound.setBuffer(bfeder);
	shoesSound.setVolume(50);

	sf::SoundBuffer bflying;
	bflying.loadFromFile("sound/flying.wav");
	sf::Sound flyingSound;
	flyingSound.setBuffer(bflying);
	flyingSound.setVolume(50);

	// initialize platforms
	sf::Vector2i platformPosition[10];
	sf::Vector2i platformPositionForReturn[10];
	std::uniform_int_distribution<int> x(0, 640 - 114);
	std::uniform_int_distribution<int> y(-25, 800);
	//std::uniform_int_distribution<int> k(-4, 0);
	std::default_random_engine e(time(0));

	sf::Vector2f P;
	// player's positon and down velocity
	float playerX = 620 / 2;
	int playerY = 151;
	float dy = 0;
	float gravity = 10;
	int height = 600;
	int score = 0;
	int i, j, k;
	bool temp = false;
	int diffi;
	bool gameOver = 0;
	bool returnToGame = 0;
	int specialJump = 3;
	int rocketPos;
	bool rocketTemp = 0;
	int allMove[10];
	bool allMoveTemp = 0;
	bool platReturn = 0;
	int bouncerType;
	int tempPlatType;
	int start = 1000;
	int end = 1500;
	file save;
	struct pos {
		int x;
		int y;
		bool built;
		int temp;
		int move;
	};
	pos movePlat;
	pause pauseMenu;
	movePlat.temp = -1;
	movePlat.built = 0;
	movePlat.move = -10;
	sf::Clock enClock;
	sf::Time enTime;

	sf::Clock flyClock;
	sf::Time flyTime;
	int enFrame = 0;
	int flyFrame = 0;
	//enemy
	struct sEnemy {
		sf::Vector2u enemyPos;
		int temp;
		bool built = false;
	}en, bo,fly;

	struct Shoes {
		sf::Vector2u Pos;
		int temp;
		bool built = false;
		bool onPlayer = false;
		int used = 0;
		bool LR = false;
	}Sshoes;

	Bounce Cbouncer;
	// player's bounding box. It should modify according to the image size
	const int PLAYER_LEFT_BOUNDING_BOX = 90;
	const int PLAYER_RIGHT_BOUNDING_BOX = 90;
	const int PLAYER_BOTTOM_BOUNDING_BOX = 90;
	const int LLhight = 50;
	const int LLwidth = 40;
	platformPosition[9] = { 450 , 880 };
	for (i = 1; i < 9; i++) {
		temp = false;
		while (temp != true) {
			platformPosition[i].y = setY(score, i);
			platformPosition[i].x = x(e);
			for (j = 0; j < i; j++) {
				temp = distance(platformPosition[i].x, platformPosition[j].x, platformPosition[i].y, platformPosition[j].y);
				if (temp == false) {
					break;
				}
			}
		}
	}



	treeL.setPosition(0, 1024);
	treeR.setPosition(640, 1024);

	treeL2.setPosition(0, 0);
	treeR2.setPosition(640, 0);
	player.setPosition(620 / 2, 980);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (fromMenu == -1) {
			window.setMouseCursorVisible(true);
			fromMenu = gameover(window, score);
			save.write(char_array, score);
			gravity = 10;
			returnToGame = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			fromMenu = pauseMenu.menu(window, score);
		}
		if (fromMenu == 0) {
			window.setMouseCursorVisible(true);
			allMoveTemp = 0;
			fromMenu = menu(window);
			returnToGame = 1;
		}

		window.setMouseCursorVisible(false);

		window.draw(Background);
		//Animation

		enTime = enClock.getElapsedTime();
		if (enTime.asSeconds() > 0.01f) {

			if (enFrame <= 8) {
				enemy.setTextureRect(sf::IntRect(enFrame * 154, 0, 154, 90));
				enFrame++;
				if (enFrame == 8) {
					enFrame = 0;
				}
			}
			enClock.restart();
		}
		//Time for flying

		

		float vecol;



		//sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		//vecol = (mousePos.x - 640/2) / 12;
		/*if (playerX > -51 && playerX < 692) {
			player.move(vecol, 0);
		}*/
		vecol = movePlayer();
		player.move(vecol, 0);

		P = player.getPosition();
		playerX = P.x;
		if (playerX > 691)
			playerX = -49;
		if (playerX < -49) {
			playerX = 691;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && dy > 0 && specialJump > 0) {
			dy -= 10;
			specialJump--;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			player.setTexture(TplayerFire);
			player.setTextureRect(sf::IntRect(26, 0, 68, 120));
			if (bullet.getPosition().y < 0) {
				shootSound.play();
				bullet.setPosition(P.x + 20, P.y);
			}

		}
		if (vecol > 0) {
			player.setTexture(Tplayer);
			player.setTextureRect(sf::IntRect(23, 23, 101, 98));
			Sshoes.LR = true;
		}
		else if (vecol < 0) {
			player.setTexture(TplayerLeft);
			player.setTextureRect(sf::IntRect(0, 23, 101, 98));
			Sshoes.LR = false;
		}
		

		bullet.move(0, -20);
		window.draw(bullet);
		//set Enemy
		for (i = 0; i < 10 && en.built == false;i++) {
			if (Enemy(platformPosition[i].x)) {
				en.built = (Enemy(platformPosition[i].x) && platformPosition[i].y < 10);
			}
			if (en.built == true) {
				en.enemyPos.x = platformPosition[i].x + 20;
				en.enemyPos.y = platformPosition[i].y + 50;
				en.temp = i;
				break;
			}
		}
		//set shoes
		for (i = 0; i < 10 && Sshoes.built == false && Sshoes.onPlayer == false;i++) {
			if (platformPosition[i].x % 61 == 0 && platformPosition[i].x > 0 && platformPosition[i].y < 10) {
				Sshoes.built = true;
			}
			if (Sshoes.built == true) {
				Sshoes.Pos.x = platformPosition[i].x + 30;
				Sshoes.Pos.y = platformPosition[i].y ;
				Sshoes.temp = i;
				break;
			}
		}
		//set flying
		if (score % 800 == 0 && score > 0 && fly.built == false) {
			fly.enemyPos.x = playerX;
			fly.enemyPos.y = 0;
			fly.built = true;
			flyingSound.play();
		}



		//build bouncer
		for (i = 0; i < 10 && bo.built == false;i++) {
			if (platformPosition[i].x % 2 == 0 && platformPosition[i].y < 20) {
				bo.built = true;
			}
			if (bo.built == true) {
				bo.temp = i;
				//Cbouncer.setBouncerPos(bo.enemyPos.x, bo.enemyPos.y);
				if (playerX >= 300) {
					bouncer.setTextureRect(sf::IntRect(807, 197, 35, 24));
					bouncer.setOrigin(0, 24);
					federSound.setBuffer(bfeder);
					tempPlatType = 45;
					bouncerType = 1;
				}
				else {
					bouncer.setTextureRect(sf::IntRect(373, 188, 77, 35));
					bouncer.setOrigin(0, 35);
					federSound.setBuffer(bfe);
					tempPlatType = 20;
					bouncerType = 2;
				}
				bo.enemyPos.x = platformPosition[i].x + tempPlatType;
				bo.enemyPos.y = platformPosition[i].y;
				break;
			}
		}
		//moving plat
		for (i = 0; i < 10 && movePlat.built == 0 && score < 1000; i++) {

			if (platformPosition[i].x > 0 && platformPosition[i].x < 100 && platformPosition[i].y < 10) {
				movePlat.temp = i;
				movePlat.built = 1;
				break;
			}
		}
		if (movePlat.built == 1) {
			if (platformPosition[movePlat.temp].x < 2) {
				movePlat.move = 4;
			}
			else if (platformPosition[movePlat.temp].x > 640 - 116) {
				movePlat.move = -4;
			}
			platformPosition[movePlat.temp].x += movePlat.move;

		}
		if (movePlat.temp == en.temp) {
			en.enemyPos.x += movePlat.move;
		}

		if (movePlat.temp == Sshoes.temp) {
			Sshoes.Pos.x += movePlat.move;
		}

		if (movePlat.temp == bo.temp) {
			bo.enemyPos.x += movePlat.move;
		}

		//All move plat
		if (score % 1000 == 0 && score > 0) {
			start = score;
			end = start + 500;
		}
		for (i = 0; i < 10 && score > start && score < end && allMoveTemp == 0; i++) {
			if (platformPosition[i].x >= 640 / 2) {
				allMove[i] = 4;
			}
			else if (platformPosition[i].x < 640 / 2) {
				allMove[i] = -4;
			}
			if (i == 9) {
				allMoveTemp = 1;
			}
		}

		for (i = 0; i < 10 && allMoveTemp == 1; i++) {
			if (platformPosition[i].x < 2) {
				allMove[i] = 4;
			}
			else if (platformPosition[i].x > 640 - 116) {
				allMove[i] = -4;
			}
			platformPosition[i].x += allMove[i];
			if (en.temp == i) {
				en.enemyPos.x += allMove[i];
			}
			if (bo.temp == i) {
				bo.enemyPos.x += allMove[i];
			}

			if (Sshoes.temp == i) {
				Sshoes.Pos.x += allMove[i];
			}
		}
		if (score >= end || score < start) {
			allMoveTemp = 0;
		}

	

		if (playerY == height && dy < (-1.62))
		{
			score += 1;
			textScore.setString("Score: " + std::to_string(score));
		}

		// player's jump mechanism
		dy += gravity;
		playerY += dy;

		diffi = checkScore(score);
		if (playerY < height) {
			for (i = 0; i < 10; ++i)
			{
				playerY = height;
				platformPosition[i].y -= dy;
				if (platformPosition[i].y > 1024)
				{
					temp = false;
					while (temp != true) {
						if (score <= 1500) {
							platformPosition[i].y = 0;
							platformPosition[i].x = x(e);
							for (j = 0; j < 10; j++) {

								if (i != j) {
									temp = distance(platformPosition[i].x, platformPosition[j].x, platformPosition[i].y, platformPosition[j].y);
									if (temp == false) {
										break;
									}
								}

							}
						}
						if (score > 1500) {
							if (i % 2 == 0) {
								k = i;
							}
							else {
								break;
							}

							platformPosition[k].y = 0;
							platformPosition[k].x = x(e);
							for (j = 0; j < 10; j++) {
								if (k != j) {
									temp = distance(platformPosition[k].x, platformPosition[j].x, platformPosition[k].y, platformPosition[j].y);
									if (temp == false) {
										break;
									}
								}

							}
						}
						/*if (score > 700) {
							if (i % 3 == 0) {
								k = i;
							}
							else {
								break;
							}
							platformPosition[k].y = 0;
							platformPosition[k].x = x(e);
							for (j = 0; j < 10; j++) {
								if (k != j) {
									temp = distance(platformPosition[k].x, platformPosition[j].x, platformPosition[k].y, platformPosition[j].y);
									if (temp == false) {
										break;
									}
								}

							}
						}*/

					}
				}
				treeL.setPosition(treeL.getPosition().x, treeL.getPosition().y - dy / 5);
				treeR.setPosition(treeR.getPosition().x, treeR.getPosition().y - dy / 5);

				treeL2.setPosition(treeL2.getPosition().x, treeL2.getPosition().y - dy / 5);
				treeR2.setPosition(treeR2.getPosition().x, treeR2.getPosition().y - dy / 5);

				if (treeL.getPosition().y > 1024 * 2) {
					treeL.setPosition(treeL.getPosition().x, 0);
					treeR.setPosition(treeR.getPosition().x, 0);
				}

				if (treeL2.getPosition().y > 1024 * 2) {
					treeL2.setPosition(treeL2.getPosition().x, 0);
					treeR2.setPosition(treeR2.getPosition().x, 0);
				}
				if (en.enemyPos.y > 1024) {
					en.built = false;
				}
				if (bo.enemyPos.y > 1024) {
					bo.built = false;
				}
				if (Sshoes.Pos.y > 1024) {
					Sshoes.built = false;
				}

			}
			en.enemyPos.y -= dy;
			bo.enemyPos.y -= dy;
			Sshoes.Pos.y -= dy;
			fly.enemyPos.y -= dy;
		}

		if (en.built == true) {
			enemy.setPosition(en.enemyPos.x, en.enemyPos.y - 90);
			window.draw(enemy);

		}
		if (bo.built == true) {
			bouncer.setPosition(bo.enemyPos.x, bo.enemyPos.y);
			window.draw(bouncer);
		}

		if (score % 50 == 0) {

		}

		for (i = 0; i < 10 && platReturn == 0; i++) {
			platformPositionForReturn[i].x = platformPosition[i].x;
			platformPositionForReturn[i].y = platformPosition[i].y;
			if (i == 9) {
				platReturn = 1;
			}
		}
		if (returnToGame == 1) {
			playerX = 620 / 2;
			playerY = 151;
			dy = 0;
			gravity = 0.2;
			score = 0;
			temp = false;
			gameOver = 0;
			returnToGame = 0;
			specialJump = 3;
			en.built = false;
			bo.built = false;
			Sshoes.built = false;
			Sshoes.onPlayer = false;
			Sshoes.used = 0;
			for (i = 0; i < 10; i++) {
				platformPosition[i].x = platformPositionForReturn[i].x;
				platformPosition[i].y = platformPositionForReturn[i].y;
			}
		}


		// detect jump on the platform
		for (size_t i = 0; i < 10 && gravity != 3; ++i)
		{
			if ((playerX + player.getTextureRect().width > platformPosition[i].x) && (playerX < platformPosition[i].x + 114)        // player's horizontal range can touch the platform
				&& (playerY + player.getTextureRect().height > platformPosition[i].y) && (playerY + player.getTextureRect().height - 1 < platformPosition[i].y + 29)  // player's vertical   range can touch the platform
				&& (dy > 0) && !gameOver) // player is falling
			{
				if (Sshoes.onPlayer == false) {
					jumpSound.play();
					dy = -12;
				}
				else if (Sshoes.onPlayer == true) {
					shoesSound.play();
					dy = -20;
					Sshoes.used++;
				}
				
			}

		}
		if (Sshoes.used >= 3) {
			Sshoes.onPlayer = false;
			Sshoes.used = 0;
		}

		// set and draw platforms

		for (size_t i = 0; i < 10; ++i)
		{
			plat.setPosition(platformPosition[i].x, platformPosition[i].y);
			window.draw(plat);
		}
		if (Sshoes.built == true && Sshoes.onPlayer == false) {
			shoes.setPosition(Sshoes.Pos.x, Sshoes.Pos.y);
			window.draw(shoes);
		}
		player.setPosition(playerX, playerY);
		if (player.getGlobalBounds().intersects(enemy.getGlobalBounds()) && gravity != 3) {
			if (dy > 0) {
				en.built = false;
				if (specialJump < 3) {
					specialJump++;
				}
				enemy.setPosition(1000, 0);
				dy = -20;
				score += 50;
				Ende.play();
			}
			else if (en.built == true) {
				printf("Hit enemy\n");
				en.built = false;
				gravity = 3;
				//gameOver = 1;
				//fromMenu = -1;
			}
			//dy = -30;
		}
		if (player.getPosition().y > 1024) {
			fromMenu = -1;
			gameOver = 1;
			gravity = 0.2;
		}
		/*if (player.getGlobalBounds().intersects(bouncer.getGlobalBounds()) && dy > 0) {
			dy = -20;
		}*/
		if ((player.getPosition().x + player.getTextureRect().width > bouncer.getPosition().x)
			&& (player.getPosition().x < bouncer.getPosition().x + bouncer.getTextureRect().width)
			&& (player.getPosition().y + 97 < bouncer.getPosition().y /*+ 24bouncer.getTextureRect().height*/)
			&& (player.getPosition().y + 98 > bouncer.getPosition().y - bouncer.getTextureRect().height) && dy > 0 && gravity != 3 && bo.built == 1)
		{
			
			federSound.play();
			dy = -20;
			
			
			if (bouncerType == 1) {
				bouncer.setTextureRect(sf::IntRect(807, 231, 35, 54));
				bouncer.setOrigin(0, 54);
			}
			else if (bouncerType == 2) {
				bouncer.setTextureRect(sf::IntRect(296, 188, 77, 35));
				bouncer.setOrigin(0, 35);
			}
		}
		if (bullet.getGlobalBounds().intersects(enemy.getGlobalBounds()) && en.built == true) {
			en.built = false;
			if (specialJump < 3) {
				specialJump++;
			}
			Ende.play();
			score += 30;
		}
		if (bullet.getGlobalBounds().intersects(flyingEnemy.getGlobalBounds()) && fly.built == true) {
			fly.built = false;
			if (specialJump < 3) {
				specialJump++;
			}
			Ende.play();
			score += 30;
		}

		if (shoes.getGlobalBounds().intersects(player.getGlobalBounds()) && Sshoes.built == true) {
			Sshoes.onPlayer = true;
			Sshoes.built = false;
		}
		//
		for (i = 0; i < 10 && rock.bulit == 0; i++) {
			if (platformPosition[i].x % 160 == 0) {
				rocketPos = platformPosition[i].x;
				rocketTemp = true;
				break;
			}
		}
		if (rocketTemp == true) {
			//rocketTemp = rock.makeRocket(window, rocketPos);

		}
		window.draw(player);
		if (Sshoes.onPlayer == true) {
			if (Sshoes.LR == false) {
				shoes.setScale(1,1);
				shoes.setPosition(playerX + 30, playerY + 80);
				window.draw(shoes);
			}
			else if (Sshoes.LR == true) {
				shoes.setScale(-1, 1);
				shoes.setPosition(playerX +70 , playerY + 80);
				window.draw(shoes);
			}
			
		}


		if(flyingEnemy.getGlobalBounds().intersects(player.getGlobalBounds()) && fly.built == true){
			printf("Hit enemy\n");
			fly.built = false;
			gravity = 3;
		}
		if (fly.built == true) {
			fly.enemyPos.y += 5;
			flyingEnemy.setPosition(fly.enemyPos.x , fly.enemyPos.y );
			window.draw(flyingEnemy);
		}
		if (fly.enemyPos.y > 1024) {
			fly.built = false;
		}
		if (fly.built == false) {
			flyingSound.stop();
		}
		window.draw(treeL);
		window.draw(treeR);
		window.draw(treeL2);
		window.draw(treeR2);
		window.draw(textScore);
		star.draw(specialJump, window);
		window.display();
		window.clear();
	}
}

int Enemy(int x) {
	if (x % 13 == 0) {
		return true;
	}
	else { return false; }

}

bool distance(float x1, float x2, float y1, float y2) {
	float d;
	d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	if (d >= 100) {
		return true;
	}
	else {
		return false;
	}
}

int checkScore(int score) {
	if (score <= 700) {
		return 10;
	}
	if (score > 700 && score <= 1400) {
		return 6;
	}
	if (score > 1400) {
		return 4;
	}
}

bool collistion(sf::Vector2i A, sf::Vector2i B, int sizeAx, int sizeAy, int sizeBx, int sizeBy) {
	if ((A.x + sizeAx > B.x) && (A.x < B.x + sizeBx)
		&& (A.y + sizeAy > B.y) && (A.y < B.y + sizeBy))
	{
		return true;
	}
	else {
		return false;
	}
}

int setY(int score, int i) {
	int x;
	if (score <= 400) {
		x = ((i + 1) * 102) - 20;
		return x;

	}
	if (score > 400 && score <= 700) {
		if (i % 2 == 0) {
			return i;
		}
	}
}

/*struct pos makePlat(sf::Vector2i Position) {
	temp = false;
	while (temp != true && i < diffi) {
		if (score > 400 && score <= 700) {
			k = setY(score, i);
		}
		else if (score <= 400) {
			k = i;
		}
		platformPosition[k].y = 1;
		platformPosition[k].x = x(e);
		for (j = 0; j < 10; j++) {

			if (i != j) {
				temp = distance(platformPosition[k].x, platformPosition[j].x, platformPosition[k].y, platformPosition[j].y);
				if (temp == false) {
					break;
				}
			}

		}
	}
}*/

int menu(sf::RenderWindow& window) {

	sf::Font menuFont;
	menuFont.loadFromFile("images/LosingGripRegular-YxG4.ttf");

	sf::Font gameFont;
	gameFont.loadFromFile("images/AlloyInk-nRLyO.ttf");

	sf::Texture Tbackground;
	Tbackground.loadFromFile("pic/jungle-bck@2x.png");
	sf::Sprite Background;
	Background.setTexture(Tbackground);

	sf::Texture Ttop;
	Ttop.loadFromFile("pic/Top.png");
	sf::Sprite top;
	top.setTexture(Ttop);

	/*sf::Texture Tdoodle;
	Tdoodle.loadFromFile("pic/jungle-right@2x");
	sf::Sprite Background;
	Background.setTexture(Tbackground);*/

	sf::Text start("Start", menuFont, 60);
	start.setOrigin(start.getGlobalBounds().width / 2, start.getGlobalBounds().height / 2);
	start.setPosition(640 / 2, 1024 * 1 / 4);

	sf::Text board("Leader Board", menuFont, 60);
	board.setOrigin(board.getGlobalBounds().width / 2, board.getGlobalBounds().height / 2);
	board.setPosition(640 / 2, 1024 / 2);

	sf::Text exis("Exit", menuFont, 60);
	exis.setOrigin(exis.getGlobalBounds().width / 2, exis.getGlobalBounds().height / 2);
	exis.setPosition(640 / 2, 1024 * 3 / 4);

	sf::Text game("HIGHER", gameFont, 70);
	game.setOrigin(game.getGlobalBounds().width / 2, 0);
	game.setPosition(640 / 2, 60);
	game.setFillColor(sf::Color::Black);

	sf::Texture TtreeL, TtreeR;
	TtreeL.loadFromFile("pic/jungle-scroller@2x.png");
	TtreeR.loadFromFile("pic/jungle-scroller@2x.png");
	sf::Sprite treeL, treeR;
	treeL.setTexture(TtreeL);
	treeL.setTextureRect(sf::IntRect(0, 0, 128, 1024));
	treeL.setOrigin(0, 1024);

	treeR.setTexture(TtreeR);
	treeR.setTextureRect(sf::IntRect(127, 0, 128, 1024));
	treeR.setOrigin(128, 1024);

	treeL.setPosition(0, 1024);
	treeR.setPosition(640, 1024);

	sf::Texture Tplat;
	Tplat.loadFromFile("pic/game-tiles-jungle@2x.png");
	sf::Sprite plat;
	plat.setTexture(Tplat);
	plat.setTextureRect(sf::IntRect(2, 3, 114, 29));

	//Textbox
	Textbox textbox1(40, sf::Color::White, false, sf::Color::Black, 3);
	textbox1.setFont(menuFont);
	textbox1.setPosition({ 640 / 2 - 33,270 + 40 });
	textbox1.setLimit(true, 5);
	textbox1.setSelected(true);
	///
	string nameliveinput;
	file leader;
	//input and save into file
	char name[20];

	sf::Texture Tenemy;
	Tenemy.loadFromFile("pic/animation2.png");
	sf::Sprite enemy;
	enemy.setTexture(Tenemy);
	enemy.setTextureRect(sf::IntRect(620, 0, 151, 90));
	enemy.setOrigin(151 / 2 - 30, 45);
	enemy.setPosition(500,200);

	/*sf::RectangleShape player(sf::Vector2f(90, 90));
	player.setFillColor(sf::Color::White);
	player.setOrigin(sf::Vector2f(0, 85));*/
	sf::Texture Tplayer, TplayerLeft, TplayerFire;
	Tplayer.loadFromFile("pic/jungle-right@2x.png");
	TplayerLeft.loadFromFile("pic/jungle-left@2x.png");
	TplayerFire.loadFromFile("pic/Mouse.png");
	sf::Sprite player;
	player.setTexture(Tplayer);
	player.setTextureRect(sf::IntRect(23, 23, 101, 98));

	float gravity = 0.3;
	float dy=0;
	int playerX = 50;
	float playerY = 500;

	sf::SoundBuffer bjump;
	bjump.loadFromFile("sound/jump.wav");
	sf::Sound jumpSound;
	jumpSound.setBuffer(bjump);
	jumpSound.setVolume(50);
	
	sf::Clock enClock;
	sf::Time enTime;
	int enFrame = 0;
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::TextEntered) {

				textbox1.typeOn(event);

			}

		}
		enTime = enClock.getElapsedTime();
		if (enTime.asSeconds() > 0.01f) {

			if (enFrame <= 8) {
				enemy.setTextureRect(sf::IntRect(enFrame * 154, 0, 154, 90));
				enFrame++;
				if (enFrame == 8) {
					enFrame = 0;
				}
			}
			enClock.restart();
		}
		string s = textbox1.getText();
		strcpy(char_array, s.c_str());
		//printf("%s\n", char_array);

		if (start.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			start.setFillColor(sf::Color::Red);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				printf("%s",nameTemp);
				return 1;
			}
		}
		else if (board.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			board.setFillColor(sf::Color::Red);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				leader.read(window);
				//return 2;
			}
		}
		else if (exis.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			exis.setFillColor(sf::Color::Red);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				window.close();
			}

		}
		else {
			start.setFillColor(sf::Color::White);
			board.setFillColor(sf::Color::White);
			exis.setFillColor(sf::Color::White);
		}

		dy += gravity;
		playerY += dy;

		player.setPosition(playerX, playerY);
		plat.setPosition(playerX, 800);
		if (player.getGlobalBounds().intersects(plat.getGlobalBounds()) && dy > 0) {
			jumpSound.play();
			dy -= 20;
		}

		window.draw(player);
		window.draw(Background);
		window.draw(player);
		window.draw(plat);
		window.draw(start);
		window.draw(enemy);
		textbox1.drawTo(window);
		window.draw(board);
		window.draw(exis);
		window.draw(game);
		window.draw(treeL);
		window.draw(treeR);
		window.draw(top);
		window.display();
		window.clear();

	}

}

int gameover(sf::RenderWindow& window, int score) {
	sf::Font menuFont;
	menuFont.loadFromFile("images/LosingGripRegular-YxG4.ttf");

	sf::Font headFont;
	headFont.loadFromFile("images/AlloyInk-nRLyO.ttf");

	sf::Texture Tbackground;
	Tbackground.loadFromFile("pic/jungle-bck@2x.png");
	sf::Sprite Background;
	Background.setTexture(Tbackground);

	sf::Text scoreText("SCORE : ", menuFont, 70);
	scoreText.setOrigin(scoreText.getGlobalBounds().width / 2, scoreText.getGlobalBounds().height / 2);
	scoreText.setPosition(640 / 2, 1024 * 2 / 4);
	scoreText.setFillColor(sf::Color::White);

	sf::Text back("MENU", menuFont, 70);
	back.setOrigin(back.getGlobalBounds().width / 2, back.getGlobalBounds().height / 2);
	back.setPosition(640 / 2, 1024 * 3 / 4);
	back.setFillColor(sf::Color::White);

	sf::Text over("GAME OVER", headFont, 70);
	over.setOrigin(over.getGlobalBounds().width / 2, over.getGlobalBounds().height / 2);
	over.setPosition(640 / 2, 1024 * 1 / 4);
	over.setFillColor(sf::Color::Black);

	sf::Texture Ttop;
	Ttop.loadFromFile("pic/Top.png");
	sf::Sprite top;
	top.setTexture(Ttop);

	sf::Texture TtreeL;
	sf::Texture TtreeR;
	TtreeL.loadFromFile("pic/jungle-scroller@2x.png");
	TtreeR.loadFromFile("pic/jungle-scroller@2x.png");
	sf::Sprite treeL, treeR;
	treeL.setTexture(TtreeL);
	treeL.setTextureRect(sf::IntRect(0, 0, 128, 1024));
	treeL.setOrigin(0, 1024);

	treeR.setTexture(TtreeR);
	treeR.setTextureRect(sf::IntRect(127, 0, 128, 1024));
	treeR.setOrigin(128, 1024);

	treeL.setPosition(0, 1024);
	treeR.setPosition(640, 1024);

	sf::Texture Tplayer;
	sf::Texture TplayerLeft;
	sf::Texture TplayerFire;
	Tplayer.loadFromFile("pic/jungle-right@2x.png");
	TplayerLeft.loadFromFile("pic/jungle-left@2x.png");
	TplayerFire.loadFromFile("pic/Mouse.png");
	sf::Sprite player;
	player.setTexture(Tplayer);
	player.setTextureRect(sf::IntRect(23, 23, 101, 98));
	player.setPosition(50 , 500);

	sf::Texture starT[3];
	starT[0].loadFromFile("pic/stars1@2x.png");
	starT[1].loadFromFile("pic/stars2@2x.png");
	starT[2].loadFromFile("pic/stars3@2x.png");
	sf::Sprite star;

	sf::Clock enClock;
	sf::Time enTime;
	int enFrame = 0;

	sf::SoundBuffer bflying;
	bflying.loadFromFile("sound/pada.wav");
	sf::Sound flyingSound;
	flyingSound.setBuffer(bflying);
	flyingSound.setVolume(50);
	flyingSound.play();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		scoreText.setString("Score: " + std::to_string(score));

		if (back.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
			back.setFillColor(sf::Color::Red);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				return 0;
			}
		}
		else {
			back.setFillColor(sf::Color::White);
		}
		enTime = enClock.getElapsedTime();
		if (enTime.asSeconds() > 0.3f) {

			if (enFrame <= 2) {
				star.setTexture(starT[enFrame]);
				enFrame++;
				if (enFrame == 2) {
					enFrame = 0;
				}
			}
			enClock.restart();
		}
		star.setPosition(45 , 470);

		window.draw(Background);
		window.draw(scoreText);
		window.draw(player);
		window.draw(star);
		window.draw(over);
		window.draw(back);
		window.draw(top);
		window.draw(treeL);
		window.draw(treeR);;
		window.display();
		window.clear();
	}

}

int movePlayer(void) {
	int speed = 6;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		speed = 14;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		return speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		return -speed;
	}
}
