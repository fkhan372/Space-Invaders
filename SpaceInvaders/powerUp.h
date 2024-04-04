#ifndef POWERUP_H
#define POWERUP_H
#include <SFML/Graphics.hpp>

class powerUp
{
private:
	sf::RectangleShape _shape;
	sf::Vector2f _size;
	float _speed = 120.0f;
	const char* _type;

public:
	sf::RectangleShape getShape() { return _shape; }
	const char* getType() { return _type; }

	void Update(float deltaTime);
	bool checkCollision(const sf::RectangleShape& playerShape);
	void Init();

	powerUp(sf::Vector2f size, sf::Vector2f initialPosition, sf::Texture& texture, const char* _type);

};

#endif
