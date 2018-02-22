#pragma once

#include <SFML/Graphics.hpp>
#include "shapeStructure.hpp"

class Shape : public ShapeStructure
{
private:
	// times since last downward movement
	float time;

public:
	sf::Color tiles[4][4];
	sf::Vector2i pos;

    Shape();

	// reinitialise the shape: move to top and change shape
    void init();

	// move downwards once per second
    void update(float dt);

	// render the shape
    void draw(sf::RenderWindow& w);

	// rotate the shape
	void rotateLeft();
    void rotateRight();

};
