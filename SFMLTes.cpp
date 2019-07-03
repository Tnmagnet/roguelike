// SFMLTes.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <iostream>
#include<.\SFML\Graphics.hpp>
#include<.\SFML\Graphics\Texture.hpp>
#include<.\SFML\Graphics\Sprite.hpp>
#include "Hero.h"
using namespace std;
using namespace sf;
const int windowHeight = 720;
const int windowWidth = 1280;
int main()
{
	RenderWindow win(VideoMode(1280,720), "SFML Hello World");
	Hero hero;
	win.setFramerateLimit(60);
	hero.setPosition(600, 450);
	hero.setScale(hero.enlargeRate, hero.enlargeRate);
	while(win.isOpen()){
		win.clear();
		win.draw(hero);
		hero.keyListen();
		win.display();
	}
	return 0;
}
