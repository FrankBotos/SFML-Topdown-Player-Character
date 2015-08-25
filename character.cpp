#include "character.h"
#include <iostream>

//constructor takes a string argument holding file location of sprite, sprite width, and sprite height
Character::Character(std::string filename, int sprW, int sprH, int nFrames, bool eightDirs, bool slopeMove) {
	//loading a file in directory "filename"
	if (_t.loadFromFile(filename)) {
		_character = sf::Sprite(_t);
	}

	anim_frame_x = 0;//represents starting x coordinate of first frame, default zero
	spriteWidth = sprW;
	spriteHeight = sprH;
	numFrames = nFrames - 1;//needs to be one less than actual amount of frames, as 0 counts as first frame

	dir = down;//initilizating direction (player will face down @ spawn)

			   //focusing in on first frame to display upon creation, so that not the entire sprite sheet is shown
	_character.setTextureRect(sf::IntRect(0, 0, spriteWidth, spriteHeight));

	currentFrameTime = sf::milliseconds(0);
	timeToWait = sf::milliseconds(85);
	nextFrameTime = timeToWait;

	eightDirections = eightDirs;//bool value, if false 4 directional animation, if true, 8 directional animation, defaults to 4
	slopingMovement = slopeMove;//bool balue, if false, character speeds are static, if true, character speed "slopes" to a limit, then slopes back down to zero upon key release

	if (slopingMovement) {
		xSpeed = 0.0f;
		ySpeed = 0.0f;
		xDecrease = 0.0005f;
		yDecrease = 0.0005f;
		maxSpeed = 0.01f;
	}

}

Character::~Character() {};//default destructor

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(_character);
}

void Character::charMove() {
	if (slopingMovement) { charMoveSloping(); }
	if (!slopingMovement) { charMoveStatic(); }
	std::cout << dir << std::endl;
}

void Character::checkCollision(WorldObject& obj) {
	collision = false;//defaullt collision to false
	collisionBox = _character.getGlobalBounds();
	if (collisionBox.intersects(obj.getCollisionBox())) {//update collision
		collision = true;
		//here we are checking keyboard values instead of dir enum because dir enum can be unreliable
		//if we are using only 4-directional movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || dir == down) {
			_character.setPosition(_character.getPosition().x, _character.getPosition().y - 1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			_character.setPosition(_character.getPosition().x, _character.getPosition().y + 1);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			_character.setPosition(_character.getPosition().x + 1, _character.getPosition().y);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			_character.setPosition(_character.getPosition().x - 1, _character.getPosition().y);
		}
		//it is fine to check the dir enum for 8-directional collision checking
		if (dir == downRight) {
			_character.setPosition(_character.getPosition().x - 1, _character.getPosition().y - 1);
		}
		if (dir == downLeft) {
			_character.setPosition(_character.getPosition().x + 1, _character.getPosition().y - 1);
		}
		if (dir == upRight) {
			_character.setPosition(_character.getPosition().x - 1, _character.getPosition().y + 1);
		}
		if (dir == upLeft) {
			_character.setPosition(_character.getPosition().x + 1, _character.getPosition().y + 1);
		}
	}
}

void Character::charMoveStatic() {

	bool isMoving = false;

	if (eightDirections) {//if using 8 directional sprite sheet
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			_character.move(-moveSpeed, 0);
			dir = left;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			_character.move(moveSpeed, 0);
			dir = right;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			_character.move(0, -moveSpeed);
			dir = up;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			_character.move(0, moveSpeed);
			dir = down;
		}

		//8-directional stuff
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			_character.move(-moveSpeed, -moveSpeed);
			dir = upLeft;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			_character.move(moveSpeed, -moveSpeed);
			dir = upRight;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			_character.move(-moveSpeed, moveSpeed);
			dir = downLeft;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			_character.move(moveSpeed, moveSpeed);
			dir = downRight;
		}
	}
	else {//if no 8 directional animation to take place
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			_character.move(-moveSpeed, 0);
			dir = left;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			_character.move(moveSpeed, 0);
			dir = right;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			_character.move(0, -moveSpeed);
			dir = up;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			_character.move(0, moveSpeed);
			dir = down;
		}
	}

	//if any movement key is pressed, isMoving is true
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		isMoving = true;
	}

	animate(isMoving);//calling own animate function every frame
}

void Character::charMoveSloping() {
	bool isMoving = false;

	//setting speed variables depending on input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && xSpeed < maxSpeed) {
		xSpeed += (nextFrameTime - currentFrameTime).asMilliseconds() * .000025f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && xSpeed > -maxSpeed) {
		xSpeed -= (nextFrameTime - currentFrameTime).asMilliseconds() * .000025f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && ySpeed < maxSpeed) {
		ySpeed += (nextFrameTime - currentFrameTime).asMilliseconds() * .000025f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && ySpeed > -maxSpeed) {
		ySpeed -= (nextFrameTime - currentFrameTime).asMilliseconds() * .000025f;
	}

	//resetting speed to zero if right/left keys pressed at same time, or if up/down keys pressed at same time
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		xSpeed = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		ySpeed = 0;
	}

	//stopping movement if no user input
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && xSpeed > 0) {
		xSpeed -= xDecrease;
		if (xSpeed < 0) {
			xSpeed = 0;
		}
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && xSpeed < 0) {
		xSpeed += xDecrease;
		if (xSpeed > 0) {
			xSpeed = 0;
		}
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && ySpeed < 0) {
		ySpeed += yDecrease;
		if (ySpeed > 0) {
			ySpeed = 0;
		}
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && ySpeed > 0) {
		ySpeed -= yDecrease;
		if (ySpeed < 0) {
			ySpeed = 0;
		}
	}

	//finding direction
	if (xSpeed < 0) { dir = left; }
	if (xSpeed > 0) { dir = right; }
	if (ySpeed < 0) { dir = up; }
	if (ySpeed > 0) { dir = down; }

	if (eightDirections) {
		if (xSpeed < 0 && ySpeed < 0) { dir = upLeft; }
		if (xSpeed > 0 && ySpeed < 0) { dir = upRight; }
		if (xSpeed < 0 && ySpeed > 0) { dir = downLeft; }
		if (xSpeed > 0 && ySpeed > 0) { dir = downRight; }
	}

	//actually moving character
	_character.move(xSpeed, ySpeed);

	//calling animate function
	if (xSpeed != 0 || ySpeed != 0) { isMoving = true; }
	else { isMoving = false; }
	animate(isMoving);

}

//is called during every update from move function
//need to pass a boolean value representing whether the player is moving
void Character::animate(bool isMoving) {
	//finds the exact time that current frame executes
	//time value for "next frame" is initialized in constructor
	currentFrameTime = frameTimer.getElapsedTime();

	if (currentFrameTime > nextFrameTime) {//execute if the current frame time has surpassed the next frame's expected display time
		nextFrameTime = currentFrameTime + timeToWait;
		if (isMoving) {//if player is currently moving, anime sprite
			anim_frame_x = anim_frame_x + spriteWidth;//increments frame value to next frame in animation, but this value is only used when it is time for next frame to be displayed
			if (anim_frame_x >= (spriteWidth * numFrames)) { anim_frame_x = 0; }//resets frame to starting point if last frame in sequence has been displayed
		}
		else {//if player is NOT moving, reset to first frame
			anim_frame_x = 0;
		}
		_character.setTextureRect(sf::IntRect(anim_frame_x, dir * spriteHeight, spriteWidth, spriteHeight));//finds appropriate "frame" in tileset, assigns to sprite
	}

}
