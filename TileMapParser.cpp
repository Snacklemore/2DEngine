//
// Created by root on 03.09.19.
//

#include <cstring>
#include <iostream>


#include "TileMapParser.h"
#include "C_Sprite.h"
#include "S_LightSystem.h"


TileMapParser::TileMapParser(ResourceAllocator<sf::Texture> &textureAllocator,SharedContext& context) : textureAllocator(textureAllocator),context(context){

}

std::vector<std::shared_ptr<Object>> TileMapParser::Parse(const std::string &file, sf::Vector2i offset) {
    char* fileLoc = new char[file.size()] +1;

#ifdef MACOS
    strlcpy(fileLoc,file.c_str(),file.size()+ 1);
#else
    strcpy(fileLoc,file.c_str());
#endif
    rapidxml::file<> xmlFile(fileLoc);
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    xml_node<>* rootNode = doc.first_node("map");
    // Loads tile layers from XML.
    std::shared_ptr<MapTiles> map = BuildMapTiles(rootNode);


    int tileSizeX = std::atoi(rootNode->first_attribute("tilewidth")->value());
    int tileSizeY = std::atoi(rootNode->first_attribute("tileheight")->value());
    int mapsizeX = std::atoi(rootNode->first_attribute("width")->value());
    int mapsizeY = std::atoi(rootNode->first_attribute("height")->value());
    std::vector<int > layerSizes;
    // This will contain all of our tiles as objects.
    std::vector<std::shared_ptr<Object>> tileObjects;

    // 2
    int layerCount =map->size() -1;
    // We iterate through each layer in the tile map
    for (const auto& layer : *map)
    {

        unsigned int layerSize = layer.second->tiles.size();
        layerSizes.emplace_back(layerSize);
        // And each tile in the layer
        for (const auto& tile : layer.second->tiles)
        {
            std::shared_ptr<TileInfo> tileInfo = tile->properties;

            std::shared_ptr<Object> tileObject = std::make_shared<Object>(&context);
            tileObject->setType(ObjectType::Tile);
            //TODO: tile scale should be set at the data level.
            const unsigned int tileScale = 2;
            std::shared_ptr<C_Sprite> Sprite;

            if (layer.second->isVisible)
            {
                Sprite = tileObject->AddComponent<C_Sprite>();
                //rect needs to set first, because used in Load()
                Sprite->SetTextureRect(tileInfo->textureRect);
                Sprite->Load(tileInfo->textureID);

                Sprite->SetScale(tileScale, tileScale);
               // std::cout << "LayerCount: "<< layerCount << std::endl;
                Sprite->SetSortOrder(layerCount);
                //ptr to to C_Sprite from C_Drawable

                //should be set if sprite belongs to background, need a way to see that its background or foreground

                if ( layer.first == "background" || layer.first == "bckgrnd"|| layer.first == "Background" )
                {
                    Sprite->SetDrawLayer(DrawLayer::BehindPlayer);
                }
                if ( layer.first == "Foreground" || layer.first == "frgrnd"|| layer.first == "foreground" )
                {
                    Sprite->SetDrawLayer(DrawLayer::InfrontPlayer);
                }
                //Light is a object layer, not a tile layer
                if (layer.first == "Light")
                {
                    //build light here
                    Sprite->SetDrawLayer(DrawLayer::InfrontPlayer);
                    std::cout << "here"<< std::endl;


                }
                if(layer.first == "Interactable")
                {
                    Sprite->SetDrawLayer(DrawLayer::BehindPlayer);
                            std::shared_ptr<C_Interactable> Interactable;
                    Interactable = tileObject->AddComponent<C_Interactable>();

                }
                //auto tileComp = tileObject->AddComponent<C_Tile>();

            }
            if(layer.first == "Interactable")
            {
                tileObject->setType(ObjectType::InterActable);
                tileObject->transform->SetPosition(tile->x, tile->y);
                tileObject->transform->setStatic(false);

                auto collider = tileObject->AddComponent<C_BoxCollider>();
                //should  get  user data  on collision  specs for object( from tiled)
                float left = tile->x-((float)tileSizeX * (float)tileScale) *0.5f;
                float top = tile->y- ((float)tileSizeY * tileScale) * 0.5f;
                float width = (float)tileSizeX * tileScale;
                float height = (float)tileSizeY*tileScale;

                //Passed to ObjectCollection, newObjects
                //Added via collidables.Add() inside ObjectCollection.ProcessNewObjects()
                collider->setBodyDef(Util::sf_to_b2(tileObject->transform->GetPosition().x/Util::SCALE,tileObject->transform->GetPosition().y/Util::SCALE));
                collider->setBodyType("Static");
                collider->setBodyShape("Box",height,width);
                collider->setFixtureDef(1.0f,0.7f);


                tileObjects.emplace_back(tileObject);
                continue;
            }
            //Light already has correct positioning
            if ( layer.first == "Light")
            {
                std::cout << "here"<< std::endl;
                tileObject->setType(ObjectType::Lightobject);
                tileObject->transform->SetPosition(tile->x, tile->y-64);
                tileObject->transform->setStatic(true);
                //build light and add to light system with with object
                context.lightSytstem->AddLight(tileObject);
                tileObjects.emplace_back(tileObject);
                continue;
            }

            // Calculate world position.

            float x = tile->x * tileSizeX * tileScale + offset.x;
            float y = tile->y * tileSizeY * tileScale + offset.y;
            tileObject->transform->SetPosition(x, y);
            tileObject->transform->setStatic(true);


            if(layer.first == "Collisions" || layer.first == "Collision")
            {
                auto collider = tileObject->AddComponent<C_BoxCollider>();
                float left = x-((float)tileSizeX * (float)tileScale) *0.5f;
                float top = y- ((float)tileSizeY * tileScale) * 0.5f;
                float width = (float)tileSizeX * tileScale;
                float height = (float)tileSizeY*tileScale;
                //rework this to set collidable data for box2d, like dynamic or static
                //All tiles are returned
                //Passed to ObjectCollection, newObjects
                //Added via collidables.Add() inside ObjectCollection.ProcessNewObjects()
                collider->setBodyDef(Util::sf_to_b2(tileObject->transform->GetPosition().x/Util::SCALE,tileObject->transform->GetPosition().y/Util::SCALE));
                collider->setBodyType("Static");
                collider->setBodyShape("Box",height,width);
                collider->setFixtureDef(1.0f,0.7f);
                //still no body created, and no fixture applied to that body

            }


            // Add new tile Object to the collection.

            tileObjects.emplace_back(tileObject);
        }


        layerCount--;
        
    }





   //BuildNeighbourPointer(tileObjects);
    return tileObjects;
}

std::shared_ptr<TileSheets> TileMapParser::BuildTileSheetData(xml_node<> *rootNode) {
    TileSheets tileSheets;

    for (xml_node<> * tilesheetNode
            = rootNode->first_node("tileset");
         tilesheetNode;
         tilesheetNode = tilesheetNode->next_sibling("tileset"))
    {
        TileSheetData tileSheetData;

        int firstid
                = std::atoi(tilesheetNode->first_attribute("firstgid")->value());

        tileSheetData.tileSize.x
                = std::atoi(tilesheetNode->first_attribute("tilewidth")->value());

        tileSheetData.tileSize.y
                = std::atoi(tilesheetNode->first_attribute("tileheight")->value());

        int tileCount
                = std::atoi(tilesheetNode->first_attribute("tilecount")->value());

        tileSheetData.
                columns = std::atoi(
                tilesheetNode->first_attribute("columns")->value()
        );

        tileSheetData.rows = tileCount / tileSheetData.columns;

        xml_node<>* imageNode = tilesheetNode->first_node("image");
        tileSheetData.textureID
                = textureAllocator.Add(
                std::string(imageNode->first_attribute("source")->value()));

        tileSheetData.imageSize.x
                = std::atoi(imageNode->first_attribute("width")->value());
        tileSheetData.imageSize.y
                = std::atoi(imageNode->first_attribute("height")->value());

        // We store the tile sheets firstid.
        tileSheets.insert(
                std::make_pair(
                        firstid, std::make_shared<TileSheetData>(tileSheetData))
        );

    }

    return std::make_shared<TileSheets>(tileSheets);
}

std::shared_ptr<MapTiles> TileMapParser::BuildMapTiles(xml_node<> *rootNode) {
    std::shared_ptr<TileSheets> tileSheetData = BuildTileSheetData(rootNode);

    std::shared_ptr<MapTiles> map = std::make_shared<MapTiles>();
    bool buildInteractable = false;
    bool buildLight = false;
    //jumping from layer to layer, but we also need to jump
    // to ObjectGroups to get Lights, or other objects
    for (xml_node<> * node = rootNode->last_node("objectgroup");node;
    node = node->previous_sibling("objectgroup"))
    {


            for (xml_node<> * OBnode = node->last_node("object");OBnode;
                 OBnode = OBnode->previous_sibling("object"))
            {
                std::pair<std::string, std::shared_ptr<Layer>> mapLayer;
                std::cout << "Name  : " <<  node->last_attribute()->value()<< std::endl;
                if(strcmp(node->last_attribute()->value(),"Light") ==0)
                {
                    mapLayer =
                            BuildLayer(OBnode, tileSheetData,false,true);
                }
                if(strcmp(node->last_attribute()->value(),"Interactable") ==        0)
                {
                     mapLayer =
                            BuildLayer(OBnode, tileSheetData,true,false);
                }
                //std::cout << "Name  : " <<  OBnode->name()<< std::endl;


                map->emplace_back(mapLayer);
                std::cout << "ObjectLayerCount : " << map->size()<< std::endl;
            }

    }



    // We loop through each layer in the XML document.
    for (xml_node<> * node = rootNode->last_node("layer");
         node; node = node->previous_sibling("layer"))
    {
        std::pair<std::string, std::shared_ptr<Layer>> mapLayer =
                BuildLayer(node, tileSheetData,false,false);

        map->emplace_back(mapLayer);
        std::cout << "LayerCount : " << map->size()<< std::endl;
    }

    return map;
}

std::pair<std::string, std::shared_ptr<Layer>>
TileMapParser::BuildLayer(xml_node<> *layerNode, std::shared_ptr<TileSheets> tileSheets,bool buildObjectLayer,bool buildLightLayer) {
    //determine if we are building tiles or objects via bool
    //rework needed to  other objects than lights
    if (!buildObjectLayer && buildLightLayer)
        {
            //this LightLayerBuilding should return all lights in the corresponding light layer
            //currently its just getting one Light and building a layer with this one light, bloating the layercount
            // unexpectedly
            TileSet tileSet;
            std::shared_ptr<Layer> layer = std::make_shared<Layer>();

            std::string nameNode = "Light";
            xml_node<> *ObjectNode = layerNode;
            int GID = std::atoi(ObjectNode->first_attribute("gid")->value());
            int owidth = std::atoi(ObjectNode->first_attribute("width")->value());
            int oheight =std::atoi(ObjectNode->first_attribute("height")->value());
            int x = std::atoi(ObjectNode->first_attribute("x")->value());
            int y = std::atoi(ObjectNode->first_attribute("y")->value());

            int tileId = GID; // 3
            //got tileId here to find in tilesheets
            if (tileId != 0) {
                auto itr = tileSet.find(tileId);
                //if its not found in tileSet, get it from the sheet
                if (itr == tileSet.end()) {
                    std::shared_ptr<TileSheetData> tileSheet;
                    int firstId = 0;

                    //search for the sheet the tile is in
                    for (auto iter = tileSheets->rbegin(); iter != tileSheets->rend(); ++iter) {
                        if (tileId >= iter->first) {
                            firstId = iter->first;
                            tileSheet = iter->second;
                            break;
                        }
                    }

                    if (!tileSheet) {
                        std::cout << "here" << std::endl;

                    }
                    //set textureCoords
                    int textureX = (tileId - firstId) % tileSheet->columns;
                    int textureY = (tileId - firstId) / tileSheet->columns;
                    if (textureX < 0) {
                        std::cout << "here" << std::endl;
                    }
                    //set tileinfo
                    std::shared_ptr<TileInfo> tileInfo = std::make_shared<TileInfo>(tileSheet->textureID, tileId,
                                                                                    sf::IntRect(textureX *
                                                                                                tileSheet->tileSize.x,
                                                                                                textureY *
                                                                                                tileSheet->tileSize.y,
                                                                                                tileSheet->tileSize.x,
                                                                                                tileSheet->tileSize.y));
                    //add to tileSet for future use
                    itr = tileSet.insert(std::make_pair(tileId, tileInfo)).first;
                }

                std::shared_ptr<Tile> tile = std::make_shared<Tile>();

                // Bind properties of a tile from a set.
                tile->properties = itr->second; // 7
                tile->x = x*2;
                tile->y = y*2;


                layer->tiles.emplace_back(tile); // 8
            }
            const std::string layerName = nameNode;

            bool layerVisible = true;
            xml_attribute<> *visibleAttribute = layerNode->first_attribute("visible");
            if (visibleAttribute) {
                layerVisible = std::stoi(visibleAttribute->value());

            }
            layer->isVisible = layerVisible;


            return std::make_pair(layerName, layer);


        }
        if (buildObjectLayer && !buildLightLayer)
            {
                //objects that are no light, pickupable, etc.
                TileSet tileSet;
                std::shared_ptr<Layer> layer = std::make_shared<Layer>();

                std::string nameNode = "Interactable";
                xml_node<> *ObjectNode = layerNode;
                int GID = std::atoi(ObjectNode->first_attribute("gid")->value());
                int owidth = std::atoi(ObjectNode->first_attribute("width")->value());
                int oheight =std::atoi(ObjectNode->first_attribute("height")->value());
                int x = std::atoi(ObjectNode->first_attribute("x")->value());
                int y = std::atoi(ObjectNode->first_attribute("y")->value());

                int tileId = GID; // 3
                //got tileId here to find in tilesheets
                if (tileId != 0) {
                    auto itr = tileSet.find(tileId);
                    //if its not found in tileSet, get it from the sheet
                    if (itr == tileSet.end()) {
                        std::shared_ptr<TileSheetData> tileSheet;
                        int firstId = 0;

                        //search for the sheet the tile is in
                        for (auto iter = tileSheets->rbegin(); iter != tileSheets->rend(); ++iter) {
                            if (tileId >= iter->first) {
                                firstId = iter->first;
                                tileSheet = iter->second;
                                break;
                            }
                        }

                        if (!tileSheet) {
                            std::cout << "here" << std::endl;

                        }
                        //set textureCoords
                        int textureX = (tileId - firstId) % tileSheet->columns;
                        int textureY = (tileId - firstId) / tileSheet->columns;
                        if (textureX < 0) {
                            std::cout << "here" << std::endl;
                        }
                        //set tileinfo
                        std::shared_ptr<TileInfo> tileInfo = std::make_shared<TileInfo>(tileSheet->textureID, tileId,
                                                                                        sf::IntRect(textureX *
                                                                                                    tileSheet->tileSize.x,
                                                                                                    textureY *
                                                                                                    tileSheet->tileSize.y,
                                                                                                    tileSheet->tileSize.x,
                                                                                                    tileSheet->tileSize.y));
                        //add to tileSet for future use
                        itr = tileSet.insert(std::make_pair(tileId, tileInfo)).first;
                    }

                    std::shared_ptr<Tile> tile = std::make_shared<Tile>();

                    // Bind properties of a tile from a set.
                    tile->properties = itr->second; // 7
                    tile->x = x*2;
                    tile->y = y*2;


                    layer->tiles.emplace_back(tile); // 8
                }
                const std::string layerName = nameNode;

                bool layerVisible = true;
                xml_attribute<> *visibleAttribute = layerNode->first_attribute("visible");
                if (visibleAttribute) {
                    layerVisible = std::stoi(visibleAttribute->value());

                }
                layer->isVisible = layerVisible;


                return std::make_pair(layerName, layer);

            }
        if (!buildLightLayer && !buildObjectLayer)
        {

        TileSet tileSet;
        std::shared_ptr<Layer> layer = std::make_shared<Layer>();
        int width = std::atoi(layerNode->first_attribute("width")->value());
        int height = std::atoi(layerNode->first_attribute("height")->value());

        xml_node<> *dataNode = layerNode->first_node("data");
        char *mapIndices = dataNode->value();

        std::stringstream fileStream(mapIndices);

        int count = 0;

        std::string line;
        while (fileStream.good()) {
            std::string substr;
            std::getline(fileStream, substr, ','); // 1

            if (!Utilities::IsInteger(substr)) // 2
            {
                // We remove special characters from the int before parsing
                substr.erase(
                        std::remove(substr.begin(), substr.end(), '\r'), substr.end());
                substr.erase(
                        std::remove(substr.begin(), substr.end(), '\n'), substr.end());


            }

            int tileId = std::stoi(substr); // 3
            //got tileId here to find in tilesheets
            if (tileId != 0) {
                auto itr = tileSet.find(tileId);
                //if its not found in tileSet, get it from the sheet
                if (itr == tileSet.end()) {
                    std::shared_ptr<TileSheetData> tileSheet;
                    int firstId = 0;

                    //search for the sheet the tile is in
                    for (auto iter = tileSheets->rbegin(); iter != tileSheets->rend(); ++iter) {
                        if (tileId >= iter->first) {
                            firstId = iter->first;
                            tileSheet = iter->second;
                            break;
                        }
                    }

                    if (!tileSheet) {
                        continue;
                    }
                    //set textureCoords
                    int textureX = (tileId - firstId) % tileSheet->columns;
                    int textureY = (tileId - firstId) / tileSheet->columns;
                    if (textureX < 0) {
                        std::cout << "here" << std::endl;
                    }
                    //set tileinfo
                    std::shared_ptr<TileInfo> tileInfo = std::make_shared<TileInfo>(tileSheet->textureID, tileId,
                                                                                    sf::IntRect(textureX *
                                                                                                tileSheet->tileSize.x,
                                                                                                textureY *
                                                                                                tileSheet->tileSize.y,
                                                                                                tileSheet->tileSize.x,
                                                                                                tileSheet->tileSize.y));
                    //add to tileSet for future use
                    itr = tileSet.insert(std::make_pair(tileId, tileInfo)).first;
                }

                std::shared_ptr<Tile> tile = std::make_shared<Tile>();

                // Bind properties of a tile from a set.
                tile->properties = itr->second; // 7
                tile->x = count % width;
                tile->y = count / width;


                layer->tiles.emplace_back(tile); // 8
            }

            count++;

        }

        const std::string layerName = layerNode->first_attribute("name")->value();

        bool layerVisible = true;
        xml_attribute<> *visibleAttribute = layerNode->first_attribute("visible");
        if (visibleAttribute) {
            layerVisible = std::stoi(visibleAttribute->value());

        }
        layer->isVisible = layerVisible;


        return std::make_pair(layerName, layer);
    }
}



