#include "character.h"

//constructor takes a string argument holding file location of sprite, sprite width, sprite height, number of frames, and a bool
//for 8 directional animation
Character::Character(std::string filename, int sprW, int sprH, int nFrames, bool eightDirs) {
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

	moveSpeed = 0.01;

	eightDirections = eightDirs;//bool value, if false 4 directional animation, if true, 8 directional animation, defaults to 4

}

Character::~Character() {};//default destructor

//returns current Sprite object
sf::Sprite Character::getSpriteObj() {
	return _character;
}

void Character::charMove() {

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
	} else {//if no 8 directional animation to take place
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
		} else {//if player is NOT moving, reset to first frame
			anim_frame_x = 0;
		}
		_character.setTextureRect(sf::IntRect(anim_frame_x, dir * spriteHeight, spriteWidth, spriteHeight));//finds appropriate "frame" in tileset, assigns to sprite
	}

}
