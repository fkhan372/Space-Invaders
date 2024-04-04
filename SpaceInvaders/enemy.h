#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>

class enemy
{
private:
	sf::RectangleShape _shape;
	sf::Vector2f _size;
	float _speed;
	int _health;

public:
	sf::RectangleShape getShape() { return _shape; }
	int getHealth() { return _health; }
	float getSpeed() { return _speed; }

	void Update(float deltaTime);
	bool checkCollision(const sf::RectangleShape& projectile);
	void killEnemy(std::vector<enemy>& enemies);
	bool operator==(const enemy& other) const {
		return this == &other;
	}
	void Init();

	enemy(sf::Vector2f size, sf::Vector2f initialPosition, sf::Texture& texture, sf::Color color, int _health, float _speed);

};

#endif
