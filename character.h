#pragma once
#include <SFML\Graphics.hpp>
#include "worldObject.h"
#include <string>

//basic "character" class that creates an in game character
//sprite directory is specified in constructor argument along with dimensions in sprite sheet
//example instantiation:
//Character foo("spritedirectory.png");

class Character : public sf::Drawable {//publically inheriting from "Drawable" class for cleaner syntax when drawing to screen
private:
	sf::Sprite _character;
	sf::Texture _t;//the texture needs to be a private variable so it does not go out of scope until destructor

				   //used in conjunction with sprite sheet
				   //directions should correspond to actual order of animatoin rows on sprite sheet
	enum Facing {

		down = 0,//row zero on sprite sheet
		left = 1,//row one on sprite sheet
		up = 3,//row two on sprite sheet
		right = 2,//row three on sprite sheet
				  //these are used for 8 directional animation!
		downLeft = 4,
		downRight = 5,
		upLeft = 6,
		upRight = 7,
	};
	Facing dir;//dir represents not only direction but also the "row" on the sprite shee that is being used for animation

	sf::Clock frameTimer;//used for timing frame switches
	sf::Time currentFrameTime;//records current frame's time
	sf::Time nextFrameTime;//represents time @ which next frame should be played
	sf::Time timeToWait;//time between frames

	int anim_frame_x;//frame number origin in animation, defaults to zero
	int spriteWidth;
	int spriteHeight;
	int numFrames;

	bool slopingMovement;//bool passed to constructor to decide movement method

	float xSpeed;//used for sloping movement
	float ySpeed;
	float xDecrease;
	float yDecrease;
	float maxSpeed;
	sf::FloatRect collisionBox;
	bool collision;

	float moveSpeed = 0.015f;//used for static movement

	bool eightDirections;

public:
	Character(std::string filename, int sprW, int sprH, int nFrames, bool eightDir = false, bool slopingMovement = false);
	~Character();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void charMove();
	virtual void charMoveStatic();
	virtual void charMoveSloping();
	virtual void animate(bool isMoving);
	void checkCollision(WorldObject& obj);
};
