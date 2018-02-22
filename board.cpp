#include "board.hpp"



void Board::reduce()
{
	bool fullLine;
	for(int i = 0; i < 19; i++) {
		fullLine = false;
        for(int j = 1; j < 11; j++) {

			if(tiles[j][i] == sf::Color::Black){
				break; // break current j
			}
			else if(j == 11 - 1){
				fullLine = true;
			}
		}
		// note: 	could be optimized by doing one
		//			iteration instead of each line
		if(fullLine){
			for(int k = i; k >= 0; k--){
				for(int l = 1; l < 11; l++) {
					if(k == 18) tiles[l][k+1] = sf::Color::Red;
					else 		tiles[l][k+1] = tiles[l][k];

				}

			}
		}
	}
}

bool Board::intersect(Shape& shape)
{
    bool intersect = false;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(tiles[i+shape.pos.x][j+shape.pos.y] != sf::Color::Black &&
               shape.tiles[i][j] != sf::Color::Black)
               intersect = true;
        }
    }
    return intersect;
}

void Board::draw(sf::RenderWindow& w)
{
    sf::CircleShape s;
    s.setRadius(8);
    s.setOrigin(8,8);
    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 20; j++) {
            s.setFillColor(tiles[i][j]);
            s.setPosition(sf::Vector2f(16 * i + 100, 16*j + 100));
            w.draw(s);
        }
    }
}

void Board::add(Shape& shape)
{
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {

            if(shape.tiles[i][j] != sf::Color::Black) {
                tiles[i + shape.pos.x][j + shape.pos.y] = shape.tiles[i][j];

                }

            }

        }


}





Board::Board()
{
	// fill with black
    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 20; j++) {
            tiles[i][j] = sf::Color::Black;
        }
    }

	// boundary
    for(int i = 0; i < 12; i++) {
        tiles[i][19] = sf::Color::Red;
    }
    for(int i = 0; i < 19; i++) {
        tiles[0][i] = sf::Color::Red;
        tiles[11][i] = sf::Color::Red;
    }
}
