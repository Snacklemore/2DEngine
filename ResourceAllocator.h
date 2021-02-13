//
// Created by root on 31.08.19.
//

#ifndef INC_2DENGINE_RESOURCEALLOCATOR_H
#define INC_2DENGINE_RESOURCEALLOCATOR_H

#include <map>
#include <memory>
#include "Debug.h"

template <typename T>
class ResourceAllocator{


public:
    int Add(const std::string& filePath)
    {
        auto it = resources.find(filePath);
        if (it != resources.end())
        {
            Debug::Log("Resource is already present, returning present ID");
            return it->second.first;
        }

        std::shared_ptr<T> resource = std::make_shared<T>();

        if (!resource->loadFromFile(filePath))
        {
            Debug::LogError("Couldnt load resource "+ filePath);
            return -1;

        }
        resources.insert(
                std::make_pair(filePath,std::make_pair(currentId,resource))
                );
        Debug::Log("Resource is added, returning ID  "+std::to_string(currentId));
        return currentId++;
    }



    void Remove(int id)
    {
        for (auto it = resources.begin(); it != resources.end();++it){
            if (it->second.first == id)
            {
                resources.erase(it->first);
            }
        }
    }


    std::shared_ptr<T> Get(int id)
    {

        for ( auto it = resources.begin();it != resources.end(); ++it)
        {
            if (it->second.first == id)
            {
                return it->second.second;
            }
        }
        return nullptr;
    }

    bool Has(int id)
    {
        return (Get(id) != nullptr);
    }
private:
    int currentId=0;
    std::map<std::string, std::pair<int , std::shared_ptr<T>>> resources;
};


#endif //INC_2DENGINE_RESOURCEALLOCATOR_H
