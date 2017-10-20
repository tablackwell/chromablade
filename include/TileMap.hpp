
#ifndef TILEMAP
#define TILEMAP

/*
 This is not my original code! This is adapted from:
 https://www.sfml-dev.org/tutorials/2.4/graphics-vertex-array.php
 - Thomas
*/

#include <SFML/Graphics.hpp>
class TileMap: public sf::Drawable, public sf::Transformable {
public:
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
    void init();
    bool loadFromFile(std::string fileName);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

#endif
