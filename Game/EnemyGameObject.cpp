#include "EnemyGameObject.h"

EnemyGameObject::EnemyGameObject(int left, int top, int width, int height, int row_left, int row_right) {
	sf::IntRect temp(left, top, width, height);
	m_rectSourceSprite = temp;

	//std::cout << m_rectSourceSprite.left << " " << m_rectSourceSprite.top << std::endl;

	m_width = width;
	m_row_left = row_left;
	m_row_right = row_right;

	//std::cout << m_row_left << " " << m_row_right << std::endl;
	

}

bool EnemyGameObject::load(const std::string& filename) {
	if (m_texture.loadFromFile(filename)) {
		m_filename = filename;
		m_sprite.setTexture(m_texture);
		m_valid = true;
		return true;
	}
	return false;
}

void EnemyGameObject::draw(sf::RenderWindow& window) {
	if (m_valid)
		window.draw(m_sprite);
	
}

void EnemyGameObject::move(sf::Vector2f loc) {
	if (m_valid)
		m_sprite.move(loc);
}

void EnemyGameObject::setPosition(float x, float y) {
	if (m_valid)
		m_sprite.setPosition(x, y);
}

sf::Vector2f EnemyGameObject::getPosition() const {
	if (m_valid)
		return m_sprite.getPosition();
	else
		return sf::Vector2f(0, 0);
}

float EnemyGameObject::getHeight() const {
	return m_sprite.getLocalBounds().height;
}

float EnemyGameObject::getWidth() const {
	return m_sprite.getLocalBounds().width;
}

void EnemyGameObject::setScale(float scale) {
	if (m_valid)
		m_sprite.setScale(scale, scale);
}

void EnemyGameObject::update(float timeAsFloat) {
	if (m_valid)
	{
		float time = 1;
		time = time + timeAsFloat;
		sf::Vector2f movement(0.0f, 0.0f);
		//std::cout << time << std::endl;

		if (time > 1)
		{
			if (m_left_or_right) { //for enemies movie right
				m_rectSourceSprite.top = m_row_right;
				if (m_rectSourceSprite.left >= 2 * m_width)
					m_rectSourceSprite.left = 0;
				else
					m_rectSourceSprite.left += m_width;

				movement.x += m_speed;
				//std::cout << m_rectSourceSprite.left << " " << m_rectSourceSprite.top << " ";
				//std::cout << m_rectSourceSprite.width << " " << m_rectSourceSprite.height << std::endl;
				time = 0;
				m_sprite.setTextureRect(m_rectSourceSprite);
				m_sprite.move(movement * timeAsFloat);
				//std::cout << movement.x << " " << movement.y << std::endl;
			}
			else { //for enemies moving left;
				m_rectSourceSprite.top = m_row_left;
				if (m_rectSourceSprite.left >= 2 * m_width)
					m_rectSourceSprite.left = 0;
				else
					m_rectSourceSprite.left += m_width;

				movement.x -= m_speed;
				//std::cout << m_rectSourceSprite.left << " " << m_rectSourceSprite.top << " ";
				//std::cout << m_rectSourceSprite.width << " " << m_rectSourceSprite.height << std::endl;
				time = 0;
				m_sprite.setTextureRect(m_rectSourceSprite);
				m_sprite.move(movement * timeAsFloat);
				//std::cout << movement.x << " " << movement.y << std::endl;
			}
			
			
		}	
		
	}
}


sf::Sprite EnemyGameObject::getSprite() {
	return m_sprite;
}

sf::IntRect EnemyGameObject::getRect() {
	return m_rectSourceSprite;
}

void EnemyGameObject::setRect(sf::IntRect &rectSourceSprite)
{
	m_rectSourceSprite = rectSourceSprite;
	m_sprite.setTextureRect(rectSourceSprite);
}

bool EnemyGameObject::checkOutOfBounds() {
	sf::Vector2f bounds = m_sprite.getPosition();
	if (bounds.x > 680 || bounds.x < -60 || bounds.y > 480)
		m_outOfBounds = true;
	return m_outOfBounds;

}

void EnemyGameObject::setLeftorRight(bool leftRight) {
	m_left_or_right = leftRight;
}

void EnemyGameObject::setSpeed(float speed) {
	m_speed = speed;
}


		


