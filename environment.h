#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
using namespace sf;
class environment :
	public Sprite
{
private:
	bool isBlock;
	Texture* tex;
public:
	void init(const char* path);
	//����ͼƬ�ļ���

	
	environment();
	virtual ~environment();
};

