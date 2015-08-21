# SFML-Topdown-Player-Character
A player character controller class for use with SFML. 2D, top down, includes built in animation and movement features, and a choice between 4-directional animation and 8-directional animation.

All you, the user, needs to have are the following:

A character sprite sheet, and your C++ IDE configured to work with SFML.

#Here is how the class works:

1) Create an object of type Character. Pass the sprite sheet directory, the sprite width in pixels, sprite height in pixels, then the amount of frames per animation (each walking animation should have the same amount of frames), and a bool value representing whether you are using 8 directional animation(true) or 4 directional animation(false)

Character objName ("spriteSheetDirectory.png", int spriteWidth, int spriteHeight, int numFrames, bool isEightDirectional);

2) From an SFML window, call the charMove function. This starts a perpetual loop that animates and moves the character based on user input. Default keys are the arrow keys.
objName.charMove();

3)From an SMFL window, draw the sprite.
w.draw(objName.getSpriteObj());

#Here is a real world example:
//begin game loop
	while (w.isOpen()) {
		sf::Event event;

		while (w.pollEvent(event)) {//processing events
			if (event.type == sf::Event::Closed) { w.close(); }//close windows if exit is clicked
		}

		w.clear();//clearing before drawing new frame

		/*DRAWING IS TO BE DONE BETWEEN CLEAR AND DISPLAY*/
		test.charMove();
		w.draw(test.getSpriteObj());

		w.display();//end current frame, display its contents on the screen
	}
