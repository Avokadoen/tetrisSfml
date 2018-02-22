
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "shape.hpp"
#include "board.hpp"
#include "globals.hpp"


int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "Tetris");

    sf::Clock clock;
    clock.restart();

    Shape shape;

    Board board;
	bool gameover = false;
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();


            if (event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Left) {
                    shape.pos.x -= 1;
					if (board.intersect(shape)) {
						shape.pos.x += 1;
					}
                }
                if(event.key.code == sf::Keyboard::Right) {
                    shape.pos.x += 1;
                    if(board.intersect(shape)) {
						shape.pos.x -= 1;
					}
                }
                if(event.key.code == sf::Keyboard::Down) {
                    shape.pos.y += 1;
                    if(board.intersect(shape)) {
						shape.pos.y -= 1;
					}
                }
                if(event.key.code == sf::Keyboard::Up) {
                    shape.rotateLeft();
                    if(board.intersect(shape)) {
						shape.rotateRight();
					}
                }
            }
        }

		float dt = clock.restart().asSeconds();

		if(gameover){
			std::cout << "GAME OVER" << std::endl;
			dt = 0;
		}

        shape.update(dt);

		if(!gameover){
	        if(board.intersect(shape)) {
	            shape.pos.y -= 1;
	            board.add(shape);
	            board.reduce();
	            shape.init();

	            gameover = board.intersect(shape);

	        }
		}

        window.clear(sf::Color::Black);

        board.draw(window);
        shape.draw(window);

        window.display();
    }

    return 0;
}
