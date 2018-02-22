#pragma once

#include "globals.hpp"
#include <string>
#include <array>
#include <SFML/Graphics.hpp>

class ShapeStructure{
protected:
	// number of shape variance
	static int shapeFormCount;

	// shape data
	static std::array<std::array<sf::Color, 16>, MAX_SHAPES> shapeForms;

	// if shapeStructure is already created
	static bool initialised;

	// loading default shapes
	ShapeStructure();

	/* load any file and try to convert data to shape
	@param: file path
	@return: successful = true, false otherwise
	*/
	static bool loadFromFile(std::string path);
};
