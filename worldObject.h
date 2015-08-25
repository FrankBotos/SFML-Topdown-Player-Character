//This is a class that should be inherited from by all "physical objects" in the game world
//Inheriting from this class will enable collision checking with player character
#pragma once
#include <SFML\Graphics.hpp>
#include <string>

//inhereting from drawable for syntactically clean drawing
//inheriting from Transformable so that object may be altered if needed
class WorldObject : public sf::Drawable {
private:
	sf::Sprite _sprite;
	sf::Texture _texture;

	int spriteWidth;
	int spriteHeight;
	int xPos;
	int yPos;

public:
	WorldObject(std::string filename, int width, int height, int _xPos, int _yPos);
	~WorldObject();
	//implementing draw function for easier draw syntax
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::FloatRect getCollisionBox();

};
