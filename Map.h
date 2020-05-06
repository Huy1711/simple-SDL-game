#ifndef MAP_H
#define MAP_H
#include <string>
/*
0 = ground
1 = top
2 = bottom
3 = left
4 = right
5 = top right corner
6 = top left corner
7 = bot right corner
8 = bot left corner
9 = U top
10 = U bottom
11 = U left
12 = U right
13 = left right parallel
14 = top bottom parallel
15 = full rec
*/

class Map{
public:
    Map();
    ~Map();

    void loadMap(std::string path);
    int map[20][30];
};

#endif // MAP_H
