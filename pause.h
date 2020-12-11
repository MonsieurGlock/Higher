#pragma once
#include <SFML/Graphics.hpp>

class pause {
private:


public:
	int menu(sf::RenderWindow& window , int score) {

		sf::Font menuFont;
		menuFont.loadFromFile("images/LosingGripRegular-YxG4.ttf");

		sf::Texture Tbackground;
		Tbackground.loadFromFile("pic/jungle-bck@2x.png");
		sf::Sprite Background;
		Background.setTexture(Tbackground);

		sf::Text start("Continue", menuFont, 60);
		start.setOrigin(start.getGlobalBounds().width / 2, start.getGlobalBounds().height / 2);
		start.setPosition(640 / 2, 1024 * 2 / 4);

		sf::Text board("Menu", menuFont, 60);
		board.setOrigin(board.getGlobalBounds().width / 2, board.getGlobalBounds().height / 2);
		board.setPosition(640 / 2, 1024 * 3 / 4);

		sf::Text scoreText("SCORE : ", menuFont, 60);
		scoreText.setOrigin(scoreText.getGlobalBounds().width / 2, scoreText.getGlobalBounds().height / 2);
		scoreText.setPosition(640 / 2, 1024 * 1 / 4);
		scoreText.setFillColor(sf::Color::White);

		sf::Text pause("PAUSE", menuFont, 70);
		pause.setOrigin(pause.getGlobalBounds().width / 2, 0);
		pause.setPosition(640 / 2, 60 );
		pause.setFillColor(sf::Color::Black);

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
			scoreText.setString("Score: " + std::to_string(score));
			if (start.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
				start.setFillColor(sf::Color::Red);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					break;
				}
			}
			else if (board.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
				board.setFillColor(sf::Color::Red);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					return 0;
				}
			}

			else {
				start.setFillColor(sf::Color::White);
				board.setFillColor(sf::Color::White);
			}
			window.draw(Background);
			window.draw(start);
			window.draw(board);
			window.draw(scoreText);
			window.draw(pause);
			window.draw(top);
			window.draw(treeL);
			window.draw(treeR);
			window.display();
			window.clear();

		}

	}



};