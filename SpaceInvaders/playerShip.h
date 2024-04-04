#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H
#include <SFML/Graphics.hpp>

class playerShip
{
private:
	sf::RectangleShape _shape;
	sf::Vector2f _size;
	float _speed = 10.0f;
	float _projectileSpeed = 300.0f;
	sf::Clock _fireCooldown;
	float _fireRate = 0.5f;

	sf::Keyboard::Key _leftKey;
	sf::Keyboard::Key _rightKey;
	sf::Keyboard::Key _spaceKey;
	std::vector<sf::RectangleShape> _projectiles;

public:
	sf::RectangleShape getShape() { return _shape; }
	std::vector<sf::RectangleShape>& getProjectiles();

	void Update(float deltaTime);
	void Fire();
	void RemoveProjectiles();
	void IncreaseFireRate();
	void Init();

	playerShip(sf::Vector2f size, sf::Vector2f initialPosition, sf::Texture& texture, sf::Color color, sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key space);

};

#endif