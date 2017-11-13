
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
    bool loadCollisionsFromText(const std::string& tileset, std::string textFileName, sf::Vector2u tileSize, unsigned int width, unsigned int height);
    bool loadDoorsFromText(const std::string& tileset, std::string textFileName, sf::Vector2u tileSize, unsigned int width, unsigned int height);
    void drawBoxes(sf::RenderWindow* target);
    int checkCollision(int actorX, int actorY);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void clear();

    std::vector<sf::RectangleShape> m_boxes;
private:

    sf::VertexArray m_vertices;
    std::vector<int> m_tileNumbers;
    sf::Texture m_tileset;
    int m_height;
    int m_width;
};

#endif
