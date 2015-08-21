//This class works only in conjunction with SFML!

//This is just a basic example of how you can set up an SFML window and then use the Character class within that Window's update cycle to import a sprite sheet, and have it be
//automatically animated and moved based on user input

#include "character.h"
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

int main() {
	sf::RenderWindow w(sf::VideoMode(1280, 720), "Test!");//creating SFML window

	//Character test("sprites/playerCharacter.png", 32, 32, 5, false);
	Character test("sprites/playerCharacter8.png", 32, 32, 6, true); //creating Character object - passing in spritesheet directory, width of a single frame, height of a single frame
																																	//number of frames in each animation, and a bool for 8 directional animation

	//begin game loop
	while (w.isOpen()) {
		sf::Event event;

		while (w.pollEvent(event)) {//processing events
			if (event.type == sf::Event::Closed) { w.close(); }//close windows if exit is clicked
		}

		w.clear();//clearing before drawing new frame

		/*DRAWING IS TO BE DONE BETWEEN CLEAR AND DISPLAY*/
		test.charMove(); // call the charMove function, which initiates a perpetual loop tha checks for movement and animation
		w.draw(test.getSpriteObj());//using SFML, draw the sprite associated with the Character object

		w.display();//end current frame, display its contents on the screen
	}

}
