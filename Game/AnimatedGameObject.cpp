#include "AnimatedGameObject.h"
#include "GameObject.h"
#include <iostream>

AnimatedGameObject::AnimatedGameObject(int left, int top, int width, int height) {
	//sf::IntRect temp(0, 148, 32, 52); //zombie
	//sf::IntRect temp(0, 241, 76, 63); //main character
	sf::IntRect temp(left, top, width, height);
	m_rectSourceSprite = temp;
}

bool AnimatedGameObject::load(const std::string& filename) {
	if (m_texture.loadFromFile(filename)) {
		m_filename = filename;
		m_sprite.setTexture(m_texture);
		m_sprite.setTextureRect(m_rectSourceSprite);
		m_valid = true;
		return true;
	}
	return false;
}

void AnimatedGameObject::draw(sf::RenderWindow& window) {
	if (m_valid)
	{
		//setup initial sprite 
		window.draw(m_sprite); //sprite rectangle (width 38 by height 52)
	}
}
		

void AnimatedGameObject::move(sf::Vector2f loc) {
	if (m_valid)
		m_sprite.move(loc);
}

void AnimatedGameObject::setPosition(float x, float y) {
	if (m_valid)
		m_sprite.setPosition(x, y);
}

sf::Vector2f AnimatedGameObject::getPosition() const {
	if (m_valid)
		return m_sprite.getPosition();
	else
		return sf::Vector2f(0, 0);
}

float AnimatedGameObject::getHeight() const {
	return m_sprite.getLocalBounds().height;
}

float AnimatedGameObject::getWidth() const {
	return m_sprite.getLocalBounds().width;
}

void AnimatedGameObject::setScale(float scale) {
	if (m_valid)
		m_sprite.setScale(scale, scale);
}

sf::Sprite AnimatedGameObject::getSprite() {
	return m_sprite;
}

sf::IntRect AnimatedGameObject::getRect() {
	return m_rectSourceSprite;
}

void AnimatedGameObject::setRect(sf::IntRect &rectSourceSprite)
{
	m_rectSourceSprite = rectSourceSprite;
	m_sprite.setTextureRect(rectSourceSprite);
}


