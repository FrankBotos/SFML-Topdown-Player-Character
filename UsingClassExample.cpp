#include "character.h"
#include "worldObject.h"
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

int main() {
	sf::RenderWindow w(sf::VideoMode(1280, 720), "Test!");

	//Character test("sprites/playerCharacter8.png", 32, 32, 6, true, true);
	Character test("sprites/playerCharacter8.png", 32, 32, 6, true, false);
	WorldObject block("sprites/block.png", 256, 128, 200, 200);

	//begin game loop
	while (w.isOpen()) {
		sf::Event event;

		while (w.pollEvent(event)) {//processing events
			if (event.type == sf::Event::Closed) { w.close(); }//close windows if exit is clicked
		}

		w.clear(sf::Color::White);//clearing before drawing new frame

		/*DRAWING IS TO BE DONE BETWEEN CLEAR AND DISPLAY*/
		w.draw(block);
		w.draw(test);
		test.checkCollision(block);//to test collision, you pass the block object to collision player character's collision function each update
		test.charMove();

		w.display();//end current frame, display its contents on the screen
	}

}
