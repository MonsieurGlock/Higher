#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
using namespace std;
class file {

public:
	int max = 0;

	void read(sf::RenderWindow& window) {
	
		
		struct data {
			string name;
			int score;
		};

		data player[50];
		int i = 0;
		for (i = 0; i < 50; i++) {
			player[i].score = 0;
		}
		char name[10];
		string nameTemp;
		int j;
		int num = 0;
		int temp;
		FILE* f = fopen("name.txt", "r");
		while (fscanf(f, "%d %s",&temp , name) >= 0) {
			if (temp < 0) {
				break;
			}
			player[num].name = name;
			player[num].score = temp;
			num++;
		}
		fclose(f);

		for (i = 0; i < num; i++) {
			printf("%d ", player[i].score);
		}
		printf("\n");
		for (i = 0; i <= num -2; i++) {
			for (j = 0; j <= num - i - 2; j++ ) {
				if (player[j].score < player[j + 1].score) {

					temp = player[j].score;
					player[j].score = player[j+1].score;
					player[j + 1].score = temp;

					nameTemp = player[j].name;
					player[j].name = player[j + 1].name;
					player[j + 1].name = nameTemp;

				}
			}
		}
		for (i = 0; i < num; i++) {
			printf("%d ", player[i].score);
		}
		for (i = 0; i < num; i++) {
			cout << player[i].name << " " << endl;
		}

		sf::Font menuFont;
		menuFont.loadFromFile("images/LosingGripRegular-YxG4.ttf");
		sf::Font handFont;
		handFont.loadFromFile("images/AlloyInk-nRLyO.ttf");
		sf::Texture Tbackground;
		Tbackground.loadFromFile("pic/jungle-bck@2x.png");
		sf::Sprite Background;
		Background.setTexture(Tbackground);

		int up = 50;
		//Head
		sf::Text head("TOP 5 SCORES", handFont, 50);
		head.setOrigin(head.getGlobalBounds().width / 2, head.getGlobalBounds().height / 2);
		head.setPosition(640 / 2, (1024 / 7) - up);
		head.setFillColor(sf::Color::Black);

		int x = 60;

		int fontSize = 50;
		//name text
		sf::Text name1("SCORE : ", menuFont, fontSize);
		name1.setOrigin(0, name1.getGlobalBounds().height / 2);
		name1.setPosition(640 / 3 - x, (1024 * 2 / 7) - up);
		name1.setFillColor(sf::Color::White);

		sf::Text name2("SCORE : ", menuFont, fontSize);
		name2.setOrigin(0, name2.getGlobalBounds().height / 2);
		name2.setPosition(640 / 3 - x, (1024 * 3 / 7) - up);
		name2.setFillColor(sf::Color::White);

		sf::Text name3("SCORE : ", menuFont, fontSize);
		name3.setOrigin(0, name3.getGlobalBounds().height / 2);
		name3.setPosition(640 / 3 - x, (1024 * 4 / 7) - up);
		name3.setFillColor(sf::Color::White);

		sf::Text name4("SCORE : ", menuFont, fontSize);
		name4.setOrigin(0, name4.getGlobalBounds().height / 2);
		name4.setPosition(640 / 3 - x, (1024 * 5 / 7) - up);
		name4.setFillColor(sf::Color::White);

		sf::Text name5("SCORE : ", menuFont, fontSize);
		name5.setOrigin(0, name5.getGlobalBounds().height / 2);
		name5.setPosition(640 / 3 - x, (1024 * 6 / 7) - up);
		name5.setFillColor(sf::Color::White);

		int setScore = 400;
		//score
		sf::Text score1("SCORE : ", menuFont, fontSize);
		score1.setOrigin(0, score1.getGlobalBounds().height / 2);
		score1.setPosition(setScore, (1024 * 2 / 7) - up);
		score1.setFillColor(sf::Color::White);

		sf::Text score2("SCORE : ", menuFont, fontSize);
		score2.setOrigin(0, score2.getGlobalBounds().height / 2);
		score2.setPosition(setScore, (1024 * 3 / 7) - up);
		score2.setFillColor(sf::Color::White);

		sf::Text score3("SCORE : ", menuFont, fontSize);
		score3.setOrigin(0, score3.getGlobalBounds().height / 2);
		score3.setPosition(setScore, (1024 * 4 / 7) - up);
		score3.setFillColor(sf::Color::White);

		sf::Text score4("SCORE : ", menuFont, fontSize);
		score4.setOrigin(0, score4.getGlobalBounds().height / 2);
		score4.setPosition(setScore, (1024 * 5 / 7) - up);
		score4.setFillColor(sf::Color::White);

		sf::Text score5("SCORE : ", menuFont, fontSize);
		score5.setOrigin(0, score5.getGlobalBounds().height / 2);
		score5.setPosition(setScore, (1024 * 6 / 7) - up);
		score5.setFillColor(sf::Color::White);

		sf::Text back("Back", menuFont, fontSize);
		back.setOrigin(back.getGlobalBounds().width/2, back.getGlobalBounds().height/2);
		back.setPosition(640/2, 1024 - back.getGlobalBounds().height - 80);
		back.setFillColor(sf::Color::White);

		sf::Texture Ttop;
		Ttop.loadFromFile("pic/Top.png");
		sf::Sprite top;
		top.setTexture(Ttop);

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


		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			window.setMouseCursorVisible(true);
			name1.setString(player[0].name);
			name2.setString(player[1].name);
			name3.setString(player[2].name);
			name4.setString(player[3].name);
			name5.setString(player[4].name);

			score1.setString(std::to_string(player[0].score));
			score2.setString(std::to_string(player[1].score));
			score3.setString(std::to_string(player[2].score));
			score4.setString(std::to_string(player[3].score));
			score5.setString(std::to_string(player[4].score));
			
			if (back.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
				back.setFillColor(sf::Color::Red);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					break;
				}
			}
			else {
				back.setFillColor(sf::Color::White);
			}

			window.draw(Background);
			window.draw(name1);
			window.draw(name2);
			window.draw(name3);
			window.draw(name4);
			window.draw(name5);
			
			window.draw(score1);
			window.draw(score2);
			window.draw(score3);
			window.draw(score4);
			window.draw(score5);

			window.draw(back);

			window.draw(head);
			window.draw(top);
			window.draw(treeL);
			window.draw(treeR);
			window.display();
			window.clear();

		}


	}





	void write(char m[10],int score) {
		printf("%s",m);
		FILE* f = fopen("name.txt", "a");
		if (m[0] == '\0') {
			fprintf(f, "%d Unknown\n", score);
		}
		else {
			fprintf(f, "%d %s\n", score, m);
		}
		
		fclose(f);

	}

private:
};