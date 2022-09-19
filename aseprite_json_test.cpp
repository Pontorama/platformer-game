#include "json.hpp"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
using json = nlohmann::json;

int main(int argc, char* args[]){
    string jsonPath = "/home/pongu/dev/platformer-game/assets/Animations/Animation-test-sprite.json";

    ifstream inputfile(jsonPath);

    json objects =  json::parse(inputfile);

    string imageFilePath = objects["meta"]["image"].get<string>();
    int width = objects["meta"]["size"]["w"].get<int>();
    int height = objects["meta"]["size"]["h"].get<int>();

    json frames = objects["frames"];

    for(auto iter = frames.begin(); iter != frames.end(); ++iter){
        cout << iter.key() << " : " << iter.value() << endl;
    }

    return 0;
}
