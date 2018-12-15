
#include "Game.h"
//#include "GameObject.h"

Game::Game() :
	m_window(sf::VideoMode(640, 480), "Cool Game")
{
	//load background music
	if (!music.openFromFile(resource_path + "background.wav")) {
		std::cout << "Error! Can't load music" << std::endl;
	}
	music.setVolume(50.0f);

	//load sound effects
	if (!buffer1.loadFromFile(resource_path + "car_horn.wav"))
		std::cout << "Error" << std::endl;
	sound1.setBuffer(buffer1);

	if (!buffer2.loadFromFile(resource_path + "zombie.wav"))
		std::cout << "Error" << std::endl;
	sound2.setBuffer(buffer2);

	if (!buffer3.loadFromFile(resource_path + "battery.wav"))
		std::cout << "Error" << std::endl;
	sound3.setBuffer(buffer3);

	//load font
	if (!font.loadFromFile("content\\Yesterdays meal.ttf")) {
		std::cout << "Error loading font file" << std::endl;
		system("pause");
	}

	//setup start screen
	screens.push_back(new RegularGameObject());
	screens[0]->load("content\\fingerprint.png");
	screens[0]->setScale(0.4f);
	screens[0]->setPosition(0, 0);

	//setup game over screen
	screens.push_back(new RegularGameObject());
	screens[1]->load("content\\BlackBlood.png");
	screens[1]->setScale(0.5f);
	screens[1]->setPosition(0, 0);

	items.push_back(new RegularGameObject); //create items

	enemies.push_back(new EnemyGameObject(0, 148, 32, 64, 64, 128)); //create zombies
	
	m_player.push_back(m_sprite4);
	m_player.push_back(new RegularGameObject);
	
	srand(time(NULL));

	for (auto i = items.begin(); i < items.end(); i++) {
		(*i)->load("content\\battery.png");
		(*i)->setPosition(float(rand() % 600), float(rand() % 400));
		(*i)->setScale(0.1f);
	}

	m_player[0]->load("content\\professor.png");
	m_player[0]->setPosition(250.0f, 250.0f);

	m_player[1]->load("content\\car.png");
	m_player[1]->setPosition(float(rand() % 500), float(rand() % 300));
	m_player[1]->setScale(0.4f);


	for (auto i = enemies.begin(); i < enemies.end(); i++) {
		(*i)->load("content\\zombie_n_skeleton2.png");
		(*i)->setPosition(-10.0f, float(rand() % 400));
	}

}

Game::~Game()
{
	for (auto i = items.begin(); i < items.end(); i++) {
		delete *i;
	}
	for (auto i = enemies.begin(); i < enemies.end(); i++) {
		delete *i;
	}
	for (auto i = m_player.begin(); i < m_player.end(); i++) {
		delete *i;
	}
}

void Game::run() {
	sf::Clock clock;

	music.setLoop(true);
	music.play();

	while (m_window.isOpen()) 
	{
		if (m_startScreen)
		{
			render();
			//std::cout << "You're at the Start Screen" << std::endl;
		}
	
		
		if (m_startGame) {
			//std::cout << "Game Started" << std::endl;
			if (clock.getElapsedTime().asSeconds() > 0.1f) {

				
				sf::Time deltaT = clock.restart();
				processEvents();
				float timeAsFloat = deltaT.asSeconds();

				for (unsigned int i = 0; i < enemies.size(); i++)
				{
					enemies[i]->update(timeAsFloat); //update movement and animation of each enemy
					bool oob = enemies[i]->checkOutOfBounds(); //check if enemy is out of bounds
					if (oob)
					{
						enemies.erase(enemies.begin() + i);
						std::cout << "Enemy dead" << std::endl;

					}
				}

				update(deltaT);
				render();

				float timeAsFloat2 = clock.getElapsedTime().asSeconds();
				//std::cout << "Enemy vector size: " << enemies.size() << " Number of zombies: " << m_numOfZombies << std::endl;
				spawnItems(timeAsFloat2);
				if (enemies.empty()) //respawn enemies if all enemies are dead
				{
					m_has_Spawned = true;
					spawnEnemies(timeAsFloat2);
				}
				

			}
		}
		
		if (m_isDead)
		{
			m_startGame = false;
			render();
			if (m_score >= m_highscore)
				m_highscore = m_score;

			m_score = 0;
		}
		

		
	}

}

void Game::intro() {

		sf::Clock clock;
		//sf::Time deltaT;

		screens[0]->draw(m_window);

		sf::Text text;
		text.setFont(font);
		text.setString("ZOMBIELAND");
		text.setCharacterSize(50);
		text.setFillColor(sf::Color::Black);
		text.setStyle(sf::Text::Style::Bold);
		text.setOutlineColor(sf::Color::White);
		text.setOutlineThickness(10);
		text.setPosition(150, 200);
		m_window.draw(text);

		sf::Text textA;
		textA.setFont(font);
		textA.setString("Press Space to continue.....");
		textA.setCharacterSize(20);
		textA.setFillColor(sf::Color::White);
		textA.setStyle(sf::Text::Style::Bold);
		textA.setOutlineColor(sf::Color::Black);
		textA.setOutlineThickness(2);
		textA.setPosition(120, 400);
		m_window.draw(textA);

		sf::Time deltaT = clock.restart();
		processEvents();
		update(deltaT);

}

void Game::runGame() {
}

void Game::gameOver() {
		sf::Clock clock;
		//sf::Time deltaT;

		screens[1]->draw(m_window);

		sf::Text text;
		text.setFont(font);
		text.setString("GAME OVER");
		text.setCharacterSize(50);
		text.setFillColor(sf::Color::Black);
		text.setStyle(sf::Text::Style::Bold);
		text.setOutlineColor(sf::Color::Red);
		text.setOutlineThickness(10);
		text.setPosition(180, 150);
		m_window.draw(text);

		sf::Text textA;
		std::ostringstream ss1;
		textA.setFont(font);
		ss1 << "SCORE: " << m_score;
		textA.setCharacterSize(20);
		textA.setFillColor(sf::Color::Black);
		textA.setStyle(sf::Text::Style::Bold);
		textA.setOutlineColor(sf::Color::Red);
		textA.setOutlineThickness(2);
		textA.setPosition(200, 300);

		textA.setString(ss1.str());
		m_window.draw(textA);

		sf::Text textB;
		std::ostringstream ss2;
		ss2 << "HIGH SCORE : " << m_highscore;
		textB.setFont(font);
		textB.setCharacterSize(20);
		textB.setFillColor(sf::Color::Black);
		textB.setStyle(sf::Text::Style::Bold);
		textB.setOutlineColor(sf::Color::Red);
		textB.setOutlineThickness(2);
		textB.setPosition(200, 350);

		textB.setString(ss2.str());
		m_window.draw(textB);

		sf::Text textC;
		textC.setFont(font);
		textC.setString("<<< Press Space to replay >>>");
		textC.setCharacterSize(10);
		textC.setFillColor(sf::Color::Black);
		textC.setOutlineColor(sf::Color::Red);
		textC.setOutlineThickness(2);
		textC.setPosition(200, 450);
		m_window.draw(textC);


		sf::Time deltaT = clock.restart();
		processEvents();
		update(deltaT);

}

void Game::processEvents() {
	sf::Event event;
	while (m_window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::KeyPressed:
			//handle key down here
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			m_window.close();
			break;
		}
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isDown) {
	if (key == sf::Keyboard::Left) {
		m_left = isDown;
	}
		
	if (key == sf::Keyboard::Right)
		m_right = isDown;
	if (key == sf::Keyboard::Up)
		m_up = isDown;
	if (key == sf::Keyboard::Down)
		m_down = isDown;
	if (key == sf::Keyboard::Space)
		m_enter = isDown;
}

//use time since last update to get smooth movement
void Game::update(sf::Time deltaT) {
	//Look a vector class!
	sf::Vector2f movement(0.0f, 0.0f);
	sf::Sprite m_sprite = m_sprite4->getSprite();
	sf::IntRect rectSourceSprite = m_sprite4->getRect();

	int left_move_row = 64; //148
	int move_limit = 512; //64 for zombie
	int move_increment = 64; //32 for zombie
	int right_move_row = 196;

	if (m_startScreen) //if at the start screen
	{
		if (m_enter)
		{
			m_startScreen = false;
			m_startGame = true; //once space is pressed, move on to the game screen
		}
	}

	if (m_startGame) { //in game 
		if (m_up)
		{
			rectSourceSprite.top = right_move_row;

			if (rectSourceSprite.left >= move_limit)
				rectSourceSprite.left = 0;
			else
				rectSourceSprite.left += left_move_row;

			movement.y -= m_speed;
			//std::cout << rectSourceSprite.left << " " << rectSourceSprite.top << " ";
			//std::cout << rectSourceSprite.width << " " << rectSourceSprite.height << std::endl;
		}

		if (m_down)
		{
			rectSourceSprite.top = right_move_row; //148
			if (rectSourceSprite.left >= move_limit)
				rectSourceSprite.left = 0;
			else
				rectSourceSprite.left += move_increment;

			movement.y += m_speed;
			//std::cout << rectSourceSprite.left << " " << rectSourceSprite.top << " ";
			//std::cout << rectSourceSprite.width << " " << rectSourceSprite.height << std::endl;
		}

		if (m_left)
		{
			rectSourceSprite.top = left_move_row; //83
			if (rectSourceSprite.left >= move_limit) //64
				rectSourceSprite.left = 0;
			else
				rectSourceSprite.left += move_increment;

			//std::cout << rectSourceSprite.left << " " << rectSourceSprite.top << " ";
			//std::cout << rectSourceSprite.width << " " << rectSourceSprite.height << std::endl;
			movement.x -= m_speed;
		}

		if (m_right)
		{
			rectSourceSprite.top = right_move_row;
			if (rectSourceSprite.left >= move_limit)
				rectSourceSprite.left = 0;
			else
				rectSourceSprite.left += move_increment;

			//std::cout << rectSourceSprite.left << " " << rectSourceSprite.top << " ";
			//std::cout << rectSourceSprite.width << " " << rectSourceSprite.height << std::endl;
			movement.x += m_speed;
		}

		m_sprite4->setRect(rectSourceSprite);
		m_sprite4->move(movement * deltaT.asSeconds());
		//std::cout << movement.x << " " << movement.y << std::endl;

		checkCollision();
	}

	if (m_isDead) //if player dies
	{
		if (m_enter)
		{
			m_startScreen = false;
			m_startGame = true;
			m_isDead = false;
		}
	}
	
}

void Game::render() {
	m_window.clear();

	if (m_startScreen) {
		intro();
	}

	if (m_startGame) {
		for (auto i = items.begin(); i < items.end(); i++) {
			(*i)->draw(m_window);
		}
		for (auto i = m_player.begin(); i != m_player.end(); ++i)
		{
			(*i)->draw(m_window);
		}
		for (auto i = enemies.begin(); i < enemies.end(); i++) {
			(*i)->draw(m_window);
		}
		displayScore();
	}

	if (m_isDead)
	{
		gameOver();
	}
	

	m_window.display();
}


void Game::checkCollision() {

	sf::Sprite player = (m_sprite4)->getSprite();

	//adjust bounding box of player
	sf::FloatRect rect = player.getGlobalBounds();
	rect.width = rect.width - 50;
	rect.height -= 10;
	rect.left += 10;
	//std::cout << rect.left << " " << rect.top << " " << rect.width << " " << rect.height << std::endl;

	for (unsigned i = 0; i < items.size(); i++) { //iterate through all items in vector
		//adjust bounding box of each item
		sf::Sprite object1 = (items[i])->getSprite();
		sf::FloatRect rect2 = object1.getGlobalBounds();
		rect2.width -= 15;
		
		//check for collision
		if (rect.intersects(rect2)) //if collide with object, delete it and increase score by 1;
		{
			sound3.play();
			m_score++;
			items.erase(items.begin() + i);
			std::cout << m_score << std::endl;
		}


	}

	//adjust bounding box of main object
	sf::Sprite object2 = (m_player[1])->getSprite();
	sf::FloatRect rect3 = object2.getGlobalBounds();
	rect3.height -= 15;
	rect3.width -= 30;                                
	//std::cout << rect3.left << " " << rect3.top << " " << rect3.width << " " << rect3.height << std::endl;

	if (rect.intersects(rect3))
	{
		sound1.play();
		std::cout << "Sound Played" << std::endl;
		m_nextLevel = true; //if player collides with main object, delete it, and respawn new objects and enemies
		unsigned int k = 1;
		m_player.erase(m_player.begin() + k);
		m_score += 5;
		std::cout << "Collision" << std::endl;
	}

	for (unsigned i = 0; i < enemies.size(); i++) {
		//adjust bounding box of enemy
		sf::Sprite enemy = (enemies[i])->getSprite();
		sf::FloatRect rect4 = enemy.getGlobalBounds();
		rect4.height -= 30;
		rect4.width -= 4;
		rect4.top += 30;
		//std::cout << rect4.left << " " << rect4.top << " " << rect4.width << " " << rect4.height << std::endl;
		if (rect.intersects(rect4))
		{
			sound2.play();
			m_isDead = true; //if player collides with enemy, player dies
			std::cout << "Your Dead" << std::endl;

		}
	}
}

void Game::spawnItems(float time) {
	
	if (m_nextLevel) { //if player has collided with main object
		for (int i = 0; i <= 1; i++) { 
			items.push_back(new RegularGameObject); //create new objects
		}
		for (auto i = items.begin(); i < items.end(); i++) { //load and print new objects
			(*i)->load("content\\battery.png");
			(*i)->setPosition(float(rand() % 600), float(rand() % 400));
			(*i)->setScale(0.1f);
		}

		std::cout << m_numOfZombies << std::endl;
		m_numOfZombies += 1;
		//std::cout << m_score << std::endl;

		m_has_Spawned = true;
		spawnEnemies(time);
		m_nextLevel = false;
		//create new main object
		m_player.push_back(new RegularGameObject);
		m_player[1]->load("content\\car.png");
		m_player[1]->setPosition(float(rand() % 500), float(rand() % 300));
		m_player[1]->setScale(0.4f);
		std::cout << "Next Level" << std::endl;
	}
}


void Game::spawnEnemies(float time) {
	if (m_has_Spawned) {

		//create zombies
		for (int i = 0; i <= (m_numOfZombies % 10); i++) {
			enemies.push_back(new EnemyGameObject(0, 148, 32, 64, 64, 128));
		}

		for (unsigned int i = 0; i <= m_numOfZombies; i++) {

			bool leftRight = rand() % 2;
			enemies[i]->setLeftorRight(leftRight);
			enemies[i]->load("content\\zombie_n_skeleton2.png");

			if (leftRight)
				enemies[i]->setPosition(-50.0f, float(rand() % 400));
			else
				enemies[i]->setPosition(650.0f, float(rand() % 400));

			float speed = rand() % 200 + 30;
			enemies[i]->setSpeed(speed);
			std::cout << "Enemy Spawned" << std::endl;

		}
		m_has_Spawned = false;
	}
	
}

void Game::displayScore() {
	std::ostringstream ss;
	ss << "Score: " << m_score;
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	text.setPosition(0, 0);

	text.setString(ss.str());
	m_window.draw(text);
	

}