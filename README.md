# SFML-Topdown-Player-Character
A player character controller class for use with SFML. 2D, top down, includes built in animation and movement features, and a choice between 4-directional animation and 8-directional animation.

All you, the user, needs to have are the following:

A character sprite sheet, and your C++ IDE configured to work with SFML.

#Here is how the class works:

Character objName ("spriteSheetDirectory.png", int spriteWidth, int spriteHeight, int numFrames, bool isEightDirectional);
objName.charMove();
w.draw(objName.getSpriteObj());
