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
	for(auto i = shapeForms.begin(); i < shapeForms.end(); i++){
		i->fill(sf::Color::Black);
	}

	std::ifstream file;

	file.open(path);

	if(!file.good()){
		return false;
	}
	std::stringstream strStream;
	strStream << file.rdbuf();
	if(!strStream.good()){
		return false;
	}

	std::string fileContent = strStream.str();

	std::size_t pos = fileContent.find("shapes: ");

	if(pos == std::string::npos) return false;

	fileContent.erase(0, (unsigned int)pos+8);

	shapeFormCount = atoi(fileContent.c_str());
	for(int i = 0; i < shapeFormCount; i++){
		std::size_t colpos = fileContent.find("color:");
		fileContent.erase(0, (unsigned int)colpos+6);
		std::string currentColor = fileContent.substr(0, fileContent.find_first_of('\n'));

		int rgb[3];
		for(int j = 0; j < 3; j++){
			fileContent.erase(0, fileContent.find_first_of(" ")+1);
			std::cout << fileContent;
			rgb[j] = atoi(fileContent.c_str());
		}

		fileContent.erase(0, fileContent.find_first_of('\n') + 1);

		unsigned int count = 0;
		std::string str = fileContent;
		str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
		unsigned int prevStrLenght = 0;
		while(str.find_first_of('1') < str.find_first_of("color:") && prevStrLenght != str.size()){
			prevStrLenght = str.size();
			unsigned int firstOne = (unsigned int)str.find_first_of('1') + 1;
			count += firstOne;
			std::cout << " count: " << count << " r: " << rgb[0] << " g: " << rgb[1] << " b: " << rgb[2] << std::endl;
			shapeForms[count][i] = sf::Color(rgb[0], rgb[1], rgb[2]);
			str.erase(0, firstOne);
		}
	}
	return true;

}
