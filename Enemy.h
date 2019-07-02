#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include<SFML/Graphics/Sprite.hpp>

using namespace std;
using namespace sf;
class Enemy :public Sprite
{
protected:
	int hp;
	double speed;
	int atk;
	double vision;
	int speedState;//用于区分怪物运动状态
	bool moveChange = true;
public:
	bool isBoss;
	//virtual void move();
	Enemy() = default;
	Enemy(int _hp, double _speed, int _atk, double _vision, bool _isBoss) :hp(_hp), speed(_speed), atk(_atk), vision(_vision), isBoss(_isBoss) {};
};

class Axe :public Enemy
{
	int run_i = 0;
	int atk_i = 0;
	int stand_i = 0;
	Texture runTexture;
	Texture atkTexture;
	Texture noMoveTexture;

public:
	//Sprite axeRun;
	//Sprite axeAtk;
	//Sprite axeNoMove;
	Axe(const char*run, const char*atk, const char*stand, int _hp=5, double _speed=5, int _atk=1, double _vision=500, bool _isBoss=false)
	{
		Enemy(_hp, _speed, _atk, _vision, _isBoss);
		runTexture.loadFromFile(run);
		atkTexture.loadFromFile(atk);
		noMoveTexture.loadFromFile(stand);
	}
	void run()
	{
		setTexture(runTexture);
		setTextureRect(IntRect(80 * run_i, 0, 80, 80));
		run_i++;
		run_i = run_i % 8;
	}

	void atk()
	{
		setTextureRect(IntRect(80 * atk_i, 0, 80, 80));
		atk_i++;
		atk_i = atk_i % 7;
	}
	void stand()
	{

		setTextureRect(IntRect(80 * stand_i, 0, 80, 80));
		stand_i++;
		stand_i = stand_i % 6;
	}

	void move(int vision)
	{
		Vector2f position = this->getPosition();
		if (1)
		{
			;
		}
	}
};