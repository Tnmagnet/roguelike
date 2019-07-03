#include <iostream>
#include<.\SFML\Graphics.hpp>
#include<.\SFML\Graphics\Texture.hpp>
#include<.\SFML\Graphics\Sprite.hpp>
#include<.\SFML\Window\Keyboard.hpp>
#include"Hero.h"
using namespace std;
using namespace sf;
Hero::Hero() {
	texRun[0].loadFromFile("./picture/hero/IndividualSprites/adventurer-run-00.png");
	texRun[1].loadFromFile("./picture/hero/IndividualSprites/adventurer-run-01.png");
	texRun[2].loadFromFile("./picture/hero/IndividualSprites/adventurer-run-02.png");
	texRun[3].loadFromFile("./picture/hero/IndividualSprites/adventurer-run-03.png");
	texRun[4].loadFromFile("./picture/hero/IndividualSprites/adventurer-run-04.png");
	texJump[0].loadFromFile("./picture/hero/IndividualSprites/adventurer-jump-00.png");
	texJump[1].loadFromFile("./picture/hero/IndividualSprites/adventurer-jump-01.png");
	texJump[2].loadFromFile("./picture/hero/IndividualSprites/adventurer-jump-02.png");
	texJump[3].loadFromFile("./picture/hero/IndividualSprites/adventurer-jump-03.png");
	texStand[0].loadFromFile("./picture/hero/IndividualSprites/adventurer-idle-2-00.png");
	texStand[1].loadFromFile("./picture/hero/IndividualSprites/adventurer-idle-2-01.png");
	texStand[2].loadFromFile("./picture/hero/IndividualSprites/adventurer-idle-2-02.png");

}
void Hero::stand() {
	static int standCount = 0;
	if (curDirection)
	{
		//setScale(enlargeRate, enlargeRate);
		setTexture(texStand[standCount/10]);
		standCount++;
	}
	else {
		//setScale(-1*enlargeRate, enlargeRate);
		setTexture(texStand[standCount/10]);
		standCount++;
	}
	standCount %= 30;
}
void Hero::run(int direction) {
	const float speed = 4.0;
	static int runCount=0;
	if (direction == curDirection) {
		//setScale(-5.0f, 5.0f);
		move(direction * speed, 0);
	}
	else if (direction != curDirection) {
		setScale((direction * enlargeRate), enlargeRate);
		if (direction == 1) {
			move(-1*55*enlargeRate, 0);
			move(speed, 0);
		}
		else {
			move(50*enlargeRate, 0); 
			move(-1 * speed, 0);
		}
		curDirection = direction;
	}
	if (isJump == 1) {
		return;
	}
	else {
		setTexture(texRun[runCount/6]);
		runCount = (runCount + 1) % 30;
	}
}
void Hero::jump(bool x) {
	static float speedY = 0;
	static int texCount = 0;
	const float acc = 1;
	if (x == 1) {
		if (isJump == 0) {
			isJump = 1;
			speedY = -20;
			setTexture(texJump[0]);
			texCount = 1;
		}
	}
	else if (x == 0) {
		if (isJump == 0) {
			return;
		}
		else {
			speedY += acc;
			if (getPosition().y >= 450) {
				float posX = getPosition().x;
				setPosition(posX, 450);
				speedY = 0;
				isJump = 0;
				setTexture(texRun[0]);
			}
			else {
				setTexture(texJump[texCount/20]);
				texCount++;
				texCount = texCount % 80;
			}
		}
	}
	move(0.0, speedY);
}
void Hero::attack(){

}
void Hero::keyListen() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		run(-1);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		run(1);
	}
	else {
		stand();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
		jump(1);
	}
	jump(0);
	if (Keyboard::isKeyPressed(Keyboard::J)) {
		attack();
	}
}