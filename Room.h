#pragma once
#include<SFML\Graphics.hpp>
#include<SFML\Window.hpp>
#include<SFML\Graphics\Texture.hpp>
#include<iostream>
#include"environment.h"
#include<string>
#include<vector>
using namespace std;
using namespace sf;
class Room
{
private:
	Texture* texBg[20];
	Texture* texTile[20];
	environment env[40];
	vector<int> bgIndexList1;
	vector<int> bgIndexList2;
	vector<int> tileIndexList;
	int bgCnt;
	int tileCnt;
	bool hasGenerated = 0;
	int commenFactor = 70;//1到100之间，表示墙出现的频率，墙之外为特殊背景
public:
	bool getHasGenerated();
	Room(const int bgCnt, const int tileCnt,string bgRootPath, string tileRootPath);
	void generate();
	
	void draw(RenderWindow& win, const float levelHeight);
	bool isTile(Vector2f pos);
	bool friend isIn(Vector2f pos,FloatRect tileRect);
	float standPlace(FloatRect person);
	~Room();
};

