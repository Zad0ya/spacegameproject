#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <locale>
#include "Content.h"
#include "mapmars.h"
#include "view.h"
#include "sound.h"
#include "images.h"
#include <Windows.h>

using namespace sf;
int main()

{

	RenderWindow window(VideoMode(1920, 1080), "SPACE BETA V 0.1");
	view.reset(sf::FloatRect(0, 0, 1920, 1080));
	Image map_image;
	map_image.loadFromFile("images/marsprops.png");
	if (!map_image.loadFromFile("images/marsprops.png")) {
		std::cout << "FATAL ERROR: MISSED FILES. PLEASE CHECK IMAGE FOLDER BEFORE!";
		return 1;
	}
	else std::cout << std::time << ":" << "Marsprops loaded.";
	
	Texture map;
	map.loadFromImage(map_image);

	Sprite s_map;
	s_map.setTexture(map);
	s_map.setPosition(50, 30);

	SoundBuffer walkbuffer;
	walkbuffer.loadFromFile("sound/walk.wav");
	Sound walk;
	walk.setBuffer(walkbuffer);



	//MAIN HERO
	Player p("herobeta.png", 2500, 2500, 112, 178); 
	
	float CurrentFrame = 0;
	Clock clock;
	while (window.isOpen())

	{
		float times = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		times = times / 800;
		Event event;

		while (window.pollEvent(event))

		{
			if (event.type == Event::Closed)

				window.close();

		}
		// MAP MAIN 
		window.clear();
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == '0')  s_map.setTextureRect(IntRect(42, 34, 691, 652)); //texture main
				if (TileMap[i][j] == '1')  s_map.setTextureRect(IntRect(803, 35, 1455, 652)); //texture second
				


				s_map.setPosition(j * 649, i * 618); //map generation 

				window.draw(s_map);
			}
		//movemainchar
		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
			p.dir = 0; p.speed = 0.1;
			CurrentFrame += 0.005 * times;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			p.sprite.setTextureRect(IntRect(128 * int(CurrentFrame), 386, 112, 179));
			getPlayerCoordinateforview(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
		}
		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
			p.dir = 0; p.speed = -0.1;
			CurrentFrame += 0.005 * times;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			p.sprite.setTextureRect(IntRect(128 * int(CurrentFrame), 192, 112, 179));
			getPlayerCoordinateforview(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
		}   
		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
			p.dir = 3; p.speed = 0.1;
			CurrentFrame += 0.005 * times;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			p.sprite.setTextureRect(IntRect(128 * int(CurrentFrame), 577, 112, 179));
			getPlayerCoordinateforview(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
			walk.play();
		}
		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
			p.dir = 2; p.speed = 0.1;
			CurrentFrame += 0.005 * times;
			if (CurrentFrame > 4) CurrentFrame -= 4;
			p.sprite.setTextureRect(IntRect(128 * int(CurrentFrame), 2, 112, 179));
			getPlayerCoordinateforview(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
			bool walksound = true;
				if (walksound == true) {
					walk.play();
				}
				if (((!Keyboard::isKeyPressed(Keyboard::Down) || (!Keyboard::isKeyPressed(Keyboard::S))))) {
					walksound = false;
					walk.stop();
				}
		}

			p.update(times);
			viewmap(times);
			changeview();
			window.setView(view);
		window.draw(p.sprite);
		window.display();

	}

	return 0;

}