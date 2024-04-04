#include "playerShip.h"

using namespace sf;

playerShip::playerShip(sf::Vector2f size, sf::Vector2f initialPosition, sf::Texture& texture, sf::Color color, sf::Keyboard::Key left, sf::Keyboard::Key right, sf::Keyboard::Key space)
{
	_shape.setSize(size);
	_shape.setPosition(initialPosition);
	_shape.setFillColor(color);
	_shape.setTexture(&texture);

	_leftKey = left;
	_rightKey = right;
	_spaceKey = space;
}

void playerShip::Update(float deltaTime)
{
	//Move the player left and right stopping at the end of the screens
	if (Keyboard::isKeyPressed(_leftKey))
	{
		if (_shape.getPosition().x > 0)
			_shape.move(_leftKey * -_speed * deltaTime, 0.0f);
	}
	else if (Keyboard::isKeyPressed(_rightKey))
	{
		if (_shape.getPosition().x < 550)
		_shape.move(_rightKey * _speed * deltaTime, 0.0f);
	}

	//Call the fire function to release the projectile rectangle based on fire rate
	if (sf::Keyboard::isKeyPressed(_spaceKey) && _fireCooldown.getElapsedTime().asSeconds() > _fireRate)
	{
		Fire();
		_fireCooldown.restart();
	}

	//Incrementally move the projectile up the screen
	for (auto& projectile : _projectiles)
	{
		projectile.move(0, -_projectileSpeed * deltaTime); // Move projectiles upwards
	}

	//Remove the projectile once it reaches a y value of 0
	RemoveProjectiles();
}

//Create rectangles at location of the player and store them in a collection called projectiles
void playerShip::Fire()
{
	sf::RectangleShape projectile(sf::Vector2f(5.0f, 5.0f));
	projectile.setFillColor(sf::Color::Red);
	projectile.setPosition(_shape.getPosition().x + _shape.getSize().x / 2 - projectile.getSize().x / 2, _shape.getPosition().y);
	_projectiles.push_back(projectile);
}

//Return projectile from collection of projectiles
std::vector<sf::RectangleShape>& playerShip::getProjectiles()
{
	return _projectiles;
}

//Remove projectile once it reaches the top
void playerShip::RemoveProjectiles()
{
	auto it = std::remove_if(_projectiles.begin(), _projectiles.end(), [](const sf::RectangleShape& projectile) {
		return projectile.getPosition().y <= 0;
		});
	_projectiles.erase(it, _projectiles.end());
}

//Increase the players fire rate (this will be affected by power up)
void playerShip::IncreaseFireRate()
{
	if (_fireRate > 0.1)
		_fireRate = _fireRate - 0.15;
}