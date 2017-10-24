
#ifndef TILEMAP
#define TILEMAP

/*
 This is not entirely my original code! This is adapted from:
 https://www.sfml-dev.org/tutorials/2.4/graphics-vertex-array.php
 - Thomas

 See TileMap.cpp for more details.
*/

#include <SFML/Graphics.hpp>
class TileMap: public sf::Drawable, public sf::Transformable { //Inherits from sf::Drawable and Transformable so rendering is straightforward
public:
    bool loadFromText(const std::string& tileset, std::string fileName, sf::Vector2u tileSize, unsigned int width, unsigned int height);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

#endif
