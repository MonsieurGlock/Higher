#pragma once
#include <SFML/Graphics.hpp>

class rocket {
public:

	bool bulit = 0;
	bool temp = 0;
	int m;
	sf::Vector2i rocketPos;
	bool makeRocket(sf::RenderWindow& window, int platPos) {
		
		sf::Texture Trocket;
		Trocket.loadFromFile("pic/jetpack@2x.png");
		sf::Sprite rocket;
		rocket.setTexture(Trocket);
		rocket.setTextureRect(sf::IntRect(134, 133, 52, 122));
		

		if (bulit == 0) {
			rocketPos = { platPos , 0 };
			rocket.setPosition(platPos, 0);
			m = 0;
			bulit = 1;
		}
		if (bulit == 1) {

			rocketPos.y += 10;
			rocket.setPosition(rocketPos.x , rocketPos.y);

			window.draw(rocket);
			
		}
		if (rocketPos.y > 1080) {
			printf("Over");
			bulit = 0;
			return false;
		}
		else { return true; }
		


		/*if (cal(platPos) == true && bulit == 0) {
			rocket.setPosition(platPos , 0);
			bulit = true;
		}
		
		if (bulit == true) {
			rocket.move(0 , 10);
			window.draw(rocket);
		}
		if(rocket.getPosition().y >1080){
			bulit = false;
		}*/

	}

	void Mo(sf::RenderWindow& window) {
		if (bulit == true) {
			
		}
	}





private:
};