#include<iostream>
#include<SFML/Graphics.hpp>
#include"Enemy.h"
#include<SFML/Window.hpp>
#include<SFML/Graphics/Texture.hpp>

using namespace std;
using namespace sf;

const int WindowHeight = 720;
const int WindowWidth = 1280;

int main()
{

	RenderWindow window(VideoMode(WindowWidth, WindowHeight), "First Window");
	window.setFramerateLimit(60);
	Axe axe1("./picture/enemy/axe/axebanditrun.png", 
		"./picture/enemy/axe/AxeBanditAttack.png",
		"./picture/enemy/axe/AxeBandit.png");
	while (window.isOpen())
	{
		Event event;
		window.clear();
		axe1.run();
		window.draw(axe1);
		window.display();
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed:
				if (event.key.code == Keyboard::Escape)
					window.close();
				break;
			default:
				break;
			}

		}
	}

}