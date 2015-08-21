# SFML-Topdown-Player-Character
A player character controller class for use with SFML. 2D, top down, includes built in animation and movement features, and a choice between 4-directional animation and 8-directional animation.

<b>All you, the user, needs to have are the following:

A character sprite sheet, and your C++ IDE configured to work with SFML.

The class will animate and move the player based on user input for you.</b>

#Here is how the class works:

1) Create an object of type Character. Pass the sprite sheet directory, the sprite width in pixels, sprite height in pixels, then the amount of frames per animation (each walking animation should have the same amount of frames), and a bool value representing whether you are using 8 directional animation(true) or 4 directional animation(false)
```
Character objName ("spriteSheetDirectory.png", int spriteWidth, int spriteHeight, int numFrames, bool isEightDirectional);
```
2) From an SFML window, call the charMove function. This starts a perpetual loop that animates and moves the character based on user input. Default keys are the arrow keys. Here is a real world example:
```
objName.charMove();
```

3)From an SMFL window, draw the sprite.
```
w.draw(objName.getSpriteObj());
```

#Here is a real world example:

```
	while (w.isOpen()) {//begin game loop
		sf::Event event;

		while (w.pollEvent(event)) {//processing events
			if (event.type == sf::Event::Closed) { w.close(); }//close windows if exit is clicked
		}

		w.clear();//clearing before drawing new frame

		/*DRAWING IS TO BE DONE BETWEEN CLEAR AND DISPLAY*/
		objName.charMove();
		w.draw(objName.getSpriteObj());

		w.display();//end current frame, display its contents on the screen
	}
```

#Important Notes:
This class depends on an enum to function correctly. It takes rectangular chunks out of the defined image and animates them. Therefore, it is very important that your sprite sheet is formatted exactly so that each "frame" fits into the exact same sized square or rectangular dimensions.

Furthermore, the rows must be lined up as such:

Row 1 - Walking down animation

Row 2 - Walking left animation

Row 3 - Walking up animation

Row 4 - Walking right animation


If you are using eight directional animation:

Row 5 - Walking down and left animation

Row 6 - Walking down and right animation

Row 7 - Walking up and left animation

Row 8 - Walking up and right animation
