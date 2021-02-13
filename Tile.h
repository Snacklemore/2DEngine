//
// Created by root on 03.09.19.
//

#ifndef INC_2DENGINE_TILE_H
#define INC_2DENGINE_TILE_H

#include <SFML/Graphics.hpp>
#include "ResourceAllocator.h"
struct TileInfo
{
    TileInfo() : tileID(-1)
    {

    }
    TileInfo(int textureID, unsigned int tileID,sf::IntRect textureRect)
            : textureID(textureID), tileID(tileID),textureRect(textureRect){}

            int tileID;
    int textureID;
    sf::IntRect textureRect;
};
struct Tile
{
    std::shared_ptr<TileInfo> properties;
    int x;
    int y;

};



#endif //INC_2DENGINE_TILE_H
