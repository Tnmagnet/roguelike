#pragma once
#include <iostream>
#include<.\SFML\Graphics.hpp>
#include<.\SFML\Graphics\Texture.hpp>
#include<.\SFML\Graphics\Sprite.hpp>
using namespace std;
using namespace sf;
class Hero :public Sprite {
	Texture texRun[5];
	Texture texJump[4];
	Texture texStand[3];
	Texture texAttack[5];
	int curDirection = 1;
	bool isJump = 0;
	bool isAttack = 0;
	void stand();
	void attack(bool x);
	void jump(bool x);
	void run(int direction);
public:
	const float enlargeRate = 5.0;
	Hero();
	void keyListen();
	Vector2f getCenter();
};