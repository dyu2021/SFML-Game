#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <iostream>

class EnemyGameObject : public GameObject {

public:

	EnemyGameObject(int left, int top, int width, int height, int row_left, int row_right);

	virtual bool load(const std::string& filename);

	virtual void draw(sf::RenderWindow& window);

	virtual void update(float deltaT);

	virtual void setPosition(float x, float y);

	virtual void move(sf::Vector2f);

	virtual sf::Vector2f getPosition() const;

	virtual float getHeight() const;

	virtual float getWidth() const;

	virtual void setScale(float scale);

	virtual sf::Sprite getSprite();

	virtual sf::IntRect getRect();

	virtual void setRect(sf::IntRect &rectSourceSprite);

	bool checkOutOfBounds();

	void setLeftorRight(bool leftRight);

	void setSpeed(float speed);


private:
	sf::Sprite m_sprite;
	sf::IntRect m_rectSourceSprite;
	sf::Texture m_texture;
	std::string m_filename;
	bool m_valid = false;
	bool m_outOfBounds;
	int m_row_left;
	int m_row_right;
	int m_width;
	float m_speed = 50.0f;
	bool m_left_or_right = true;



};