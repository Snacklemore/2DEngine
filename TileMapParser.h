//
// Created by root on 03.09.19.
//

#ifndef INC_2DENGINE_TILEMAPPARSER_H
#define INC_2DENGINE_TILEMAPPARSER_H


#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <sstream>

#include "rapidxml.hpp"

#include "rapidxml_utils.hpp"
#include "rapidxml_print.hpp"
#include "Tile.h"
#include "Utilities.h"
#include "Object.h"
#include "C_SpriteStatic.h"
#include "C_BoxCollider.h"
#include "C_Interactable.h"



using namespace rapidxml;

struct TileSheetData
{
    int textureID;
    sf::Vector2u imageSize;
    int columns;
    int rows;
    sf::Vector2u tileSize;
};


using TileSheets = std::map<int, std::shared_ptr<TileSheetData>>;

struct Layer
{
    std::vector<std::shared_ptr<Tile>> tiles;
    bool isVisible;
};

using MapTiles = std::vector<std::pair<std::string,std::shared_ptr<Layer>>>;

using TileSet = std::unordered_map<unsigned int, std::shared_ptr<TileInfo>>;

class TileMapParser {
public:
    SharedContext& context;
    TileMapParser(ResourceAllocator<sf::Texture>& textureAllocator,SharedContext& context);
    std::vector<std::shared_ptr<Object>> Parse(const std::string& file,sf::Vector2i offset);



private:
    std::shared_ptr<TileSheets> BuildTileSheetData(xml_node<>* rootNode);
    std::shared_ptr<MapTiles > BuildMapTiles(xml_node<>* rootNode);
    std::pair<std::string,std::shared_ptr<Layer>> BuildLayer(xml_node<>* layerNode,std::shared_ptr<TileSheets> tileSheetData,bool buildObjectLayer,bool buildLightLayer);
    ResourceAllocator<sf::Texture>& textureAllocator;

};


#endif //INC_2DENGINE_TILEMAPPARSER_H
