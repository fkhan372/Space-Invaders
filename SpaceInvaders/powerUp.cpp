#include "powerUp.h"

using namespace sf;

powerUp::powerUp(sf::Vector2f size, sf::Vector2f initialPosition, sf::Texture& texture, const char* type)
{
	_shape.setSize(size);
	_shape.setPosition(initialPosition);
	_shape.setTexture(&texture);
	_type = type;
}

void powerUp::Update(float deltaTime)
{
	//Constantly move the enemy down with the given speed
	_shape.move(0, _speed * deltaTime);
}

bool powerUp::checkCollision(const sf::RectangleShape& playerShape)
{
	//Get the global boundaries for the power up and the player
	sf::FloatRect powerUpBounds = _shape.getGlobalBounds();
	sf::FloatRect playerBounds = playerShape.getGlobalBounds();

	//If power up intersects the player this will return true
	if (powerUpBounds.intersects(playerBounds))
	{
		return true;
	}

	//If there is no collision it will return false
	return false;
}