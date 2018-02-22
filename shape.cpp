#include "shape.hpp"
#include <iostream>
void Shape::rotateLeft()
{
    sf::Color tmp[4][4];
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            tmp[i][j]=tiles[j][3-i];
        }
    }
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            tiles[i][j]=tmp[i][j];
        }
    }
}

void Shape::rotateRight()
{
    rotateLeft();
    rotateLeft();
    rotateLeft();
}

Shape::Shape()
{
	//ShapeStructure();
    init();
}

void Shape::init()
{
	// move to top and reset timer
    pos.y = 0;
    pos.x = 4;
	time = 0.0f;

	int shapeType = rand() % shapeFormCount;
	// set fill color
	int formIndex = 1;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            tiles[i][j] = shapeForms[formIndex++][shapeType];
        }
    }
}

void Shape::update(float dt)
{
    time += dt;
    if(time > 1) {
        time = 0;
        pos.y += 1;
    }
}

void Shape::draw(sf::RenderWindow& w)
{
    sf::CircleShape s;
    s.setRadius(8);
    s.setOrigin(8,8);
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(tiles[i][j] != sf::Color::Black) {
                s.setFillColor(tiles[i][j]);
                s.setPosition(sf::Vector2f(pos.x * 16 + 16 * i + 100, pos.y * 16 + 16 * j + 100));
                w.draw(s);
            }
        }
    }
}
