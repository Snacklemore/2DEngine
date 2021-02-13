//
// Created by root on 25.08.19.
//

#ifndef INC_2DENGINE_WORKINGDIRECTORY_H
#define INC_2DENGINE_WORKINGDIRECTORY_H

#include <string>
class WorkingDirectory {
public:
    WorkingDirectory();
    inline const std::string& Get()
    {
        return path;
    }

private:
    std::string path;

};


#endif //INC_2DENGINE_WORKINGDIRECTORY_H
