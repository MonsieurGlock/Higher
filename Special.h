#pragma once
#include <SFML/Graphics.hpp>

class special {
public:


	void draw(int x, sf::RenderWindow& window) {
		sf::Texture Tstar;
		Tstar.loadFromFile("pic/stars1@2x.png");
		sf::Sprite star1, star2, star3;
		star1.setTexture(Tstar);
		star1.setTextureRect(sf::IntRect(26, 3, 26, 24));
		star1.setPosition(614,0);

		star2.setTexture(Tstar);
		star2.setTextureRect(sf::IntRect(26, 3, 26, 24));
		star2.setPosition(588, 0);

		star3.setTexture(Tstar);
		star3.setTextureRect(sf::IntRect(26, 3, 26, 24));
		star3.setPosition(562, 0);
		if (x == 3) {
			window.draw(star1);
			window.draw(star2);
			window.draw(star3);
		}
		else if (x == 2) {
			window.draw(star1);
			window.draw(star2);
		}
		else if (x == 1) {
			window.draw(star1);
		}
	}

	
};