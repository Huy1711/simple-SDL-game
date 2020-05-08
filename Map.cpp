#include "Map.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

Map::Map() {

}

Map::~Map() {

}

void Map::loadMap(string path) {
    ifstream file(path);
    string line, numb, temp;
    int x=0, y=0;
    while(!file.eof()) {
        x=0;
        getline(file, line);
        stringstream s(line);
        while (getline(s, numb, ',')) {
            map[y][x] = stoi(numb);
            x++;
        }
        y++;
    }
    file.close();
}
