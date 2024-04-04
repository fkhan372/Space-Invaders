#include "enemy.h"

using namespace sf;

enemy::enemy(sf::Vector2f size, sf::Vector2f initialPosition, sf::Texture& texture, sf::Color color, int health, float speed)
{
	_shape.setSize(size);
	_shape.setPosition(initialPosition);
	_shape.setFillColor(color);
	_shape.setTexture(&texture);
	_health = health;
	_speed = speed;

}

void enemy::Update(float deltaTime)
{
	//Constantly move the enemy down with the given speed
	_shape.move(0, _speed * deltaTime);
}

//Return true or false based on wether collision was detected
bool enemy::checkCollision(const sf::RectangleShape& projectile)
{
	//Get the global boundaries for the enemy shape and the projectile shape
	sf::FloatRect enemyBounds = _shape.getGlobalBounds();
	sf::FloatRect projectileBounds = projectile.getGlobalBounds();

	//If enemy shape intersects the projectile shape this will subtract 1 from enemies health and return true
	if (enemyBounds.intersects(projectileBounds))
	{
		_health -= 1;

		return true;
	}

	//If there is no collision it will return false
	return false;
}

//Function used to erase the enemy from the collection of enemies
void enemy::killEnemy(std::vector<enemy>& enemies) 
{
	//Find the iterator pointing to this enemy
	auto x = std::find(enemies.begin(), enemies.end(), *this);

	//Remove the enemy from the vector
	if (x != enemies.end()) {
		enemies.erase(x);
	}
}