//
// Created by bswenson3 on 11/9/16.
//
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameObject.h"
#include "RegularGameObject.h"
#include "AnimatedGameObject.h"
#include "EnemyGameObject.h"
#include <vector>
#include <iostream>
#include "resource_path.h"
#include <sstream>
#include <stdlib.h>

class Game {
public:
	//use default screen size
	Game();

	~Game();
	//run the game
	void run();

private:

	void intro();
	void runGame();
	void gameOver();

	void processEvents();
	//update the game objects
	void update(sf::Time deltaT); //{}
	//draw the scene
	void render();
	//handle input from the user
	void handlePlayerInput(sf::Keyboard::Key key, bool isDown);

	sf::RenderWindow m_window;
	//RegularGameObject m_player;
	//AnimatedGameObject m_player;

	std::vector<GameObject *> m_player;
	std::vector<GameObject* > items;
	std::vector<EnemyGameObject* > enemies;
	AnimatedGameObject* m_sprite4 = new AnimatedGameObject(0, 241, 76, 63);
	std::vector<GameObject* > screens;

	void checkCollision();
	void spawnItems(float time);
	void spawnEnemies(float time);

	void displayScore();

	//TODO::these should be moved to game object
	float m_speed = 120.0f;
	bool m_left = false;
	bool m_right = false;
	bool m_up = false;
	bool m_down = false;
	bool m_enter = false;

	sf::Font font;
	sf::Music music;
	sf::SoundBuffer buffer1;
	sf::SoundBuffer buffer2;
	sf::SoundBuffer buffer3;
	sf::Sound sound1;
	sf::Sound sound2;
	sf::Sound sound3;

	int m_score = 0;
	int m_highscore = 0;
	bool m_nextLevel = false;
	bool m_has_Spawned = false;
	int m_numOfZombies = 0;

	bool m_startScreen = true;
	bool m_startGame = false;
	bool m_isDead = false;

};
