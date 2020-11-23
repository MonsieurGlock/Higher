#pragma once
#include <SFML/Graphics.hpp>

class Bounce {
public:
	Bounce() {
		bouncer.setSize(sf::Vector2f (15.1 , 15.1));
		status.bouncerBuilt = 0;
	}

	int setBouncerPos(int x ,int y){
		status.bouncerPos.x = x;
		status.bouncerPos.y = y;
		status.bouncerBuilt = true;
		
	}

	bool HitBoouncer(int playerX , int playerY , float dy) {

		if ((playerX + 90 > bouncer.getPosition().x) && (playerX < bouncer.getPosition().x + 15.1)        // player's horizontal range can touch the platform
			&& (playerY + 90> bouncer.getPosition().y) && (playerY < bouncer.getPosition().y + 15.1) && (dy > 0)) {
			return 1;
		}
	}

	void moveB(int en) {
		
		if (bouncer.getPosition().y > 900) {
			status.bouncerBuilt = 0;
			printf("Delete bouncer\n");
		}
	}

	void draw(sf::RenderWindow &window) {
		//bouncer.setPosition(status.bouncerPos.x, status.bouncerPos.y);
		window.draw(bouncer);
	}

private:
	sf::RectangleShape bouncer;
	struct bo {
		sf::Vector2f bouncerPos;
		bool bouncerBuilt;
	}status;
	float dy=0;

};