#pragma once
#include "shape.hpp"

class Board
{
public:
    sf::Color tiles[12][20];

    Board();

	// add a shape to the board
    void add(Shape& shape);

	// check if a shape intersects with the board
    bool intersect(Shape& shape);

	// remove full lines - should be implemented by you
    void reduce();

	// render board
    void draw(sf::RenderWindow& w);
};
