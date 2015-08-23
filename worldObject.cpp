#include "worldObject.h"

WorldObject::WorldObject(std::string filename, int width, int height, int _xPos, int _yPos) {
	if (_texture.loadFromFile(filename)) {
		_sprite = sf::Sprite(_texture);
	}

	spriteWidth = width;
	spriteHeight = height;

	xPos = _xPos;
	yPos = _yPos;
	_sprite.setPosition(xPos, yPos);

}

void WorldObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_sprite);
}

WorldObject::~WorldObject() {}

sf::FloatRect WorldObject::getCollisionBox() { return _sprite.getGlobalBounds(); }
