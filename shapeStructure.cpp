// Source for reading file:
// https://stackoverflow.com/a/19922123


#include "shapeStructure.hpp"
#include <fstream> // ifstream
#include <iostream>
#include <sstream>

int ShapeStructure::shapeFormCount = 0;
bool ShapeStructure::initialised = false;
std::array<std::array<sf::Color, 16>, MAX_SHAPES> ShapeStructure::shapeForms;

ShapeStructure::ShapeStructure(){
	if(initialised == true){
		return;
	}

	if(loadFromFile("defaultShapes.shapes") == false){
		// handle;
	}
	initialised = true;
}

bool ShapeStructure::loadFromFile(std::string path){
	// Fill all arrays with black (default color)
	for(auto i = shapeForms.begin(); i < shapeForms.end(); i++){
		i->fill(sf::Color::Black);
	}

	std::ifstream file;
	file.open(path);
	if(!file.good()){
		return false;
	}

	// we need a string to handle file content
	std::stringstream strStream;
	strStream << file.rdbuf();
	if(!strStream.good()){
		return false;
	}
	std::string fileContent = strStream.str();

	// find start of content in file
	std::size_t pos = fileContent.find("shapes: ");

	// check if user use expected file structure
	if(pos == std::string::npos) return false;
	fileContent.erase(0, (unsigned int)pos+8);
	shapeFormCount = atoi(fileContent.c_str());

	// loop through all shapes in file
	for(int i = 0; i < shapeFormCount; i++){
		std::size_t colpos = fileContent.find("color:");
		fileContent.erase(0, (unsigned int)colpos+6);
		std::string currentColor = fileContent.substr(0, fileContent.find_first_of('\n'));

		int rgb[3];
		for(int j = 0; j < 3; j++){
			fileContent.erase(0, fileContent.find_first_of(" ")+1);
			rgb[j] = atoi(fileContent.c_str());
		}

		fileContent.erase(0, fileContent.find_first_of('\n') + 1);


		// remove whitespace from a temp string
		std::string str = fileContent;
		str.erase(remove_if(str.begin(), str.end(), isspace), str.end());

		unsigned int prevStrLenght = 0;
		unsigned int count = 0;

		// while we still reading one's from the same object
		// and have not reached end of string
		while(str.find_first_of('1') < str.find_first_of("color:")
		&& prevStrLenght != str.size()){
			prevStrLenght = str.size();
			// find index of colored tiled
			unsigned int firstOne = (unsigned int)str.find_first_of('1') + 1;
			count += firstOne;

			// color tile
			shapeForms[count][i] = sf::Color(rgb[0], rgb[1], rgb[2]);
			str.erase(0, firstOne);
		}

		// if not a valid shape
		if(!isPolyomino(i)){

			// revert changes done
			for(int j = 0; j < 16; j++){
				shapeForms[j][i] = sf::Color::Black;
			}
			std::cout << "invalid polyomino on one of shapes in file";
			shapeFormCount--;
			i--;
		}
	}
	return true;
}

bool ShapeStructure::isPolyomino(int index){

	std::cout << "helo\n";
	for(int i = 0; i < 16; i++){
			if(shapeForms[i][index] != sf::Color::Black){

				if((i%4) !=  0 && shapeForms[i-1][index] != sf::Color::Black){
					// has neighbour
				}
				else if( i < (15 - 4) && shapeForms[i+4][index] != sf::Color::Black){
					// has neighbour
				}
				else if((i%4) != 3 && shapeForms[i+1][index] != sf::Color::Black){
					// has neighbour
				}
				else if(i > 3 && shapeForms[i-4][index] != sf::Color::Black){
					// has neighbour
				}
				else{
					// does not have a neighbour
					return false;
				}
			}
	}
	// shape was pl
	return true;
}
