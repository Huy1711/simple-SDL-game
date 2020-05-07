#ifndef MAP_H
#define MAP_H
#include <string>

class Map{
public:
    Map();
    ~Map();

    void loadMap(std::string path);
    int map[20][30];
};

#endif // MAP_H
