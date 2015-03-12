#include "Map.h"

#include <SDL.h>

#include <iostream>

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    Map map;
    try
    {
        map.readFile("map.tmx");
        std::cout << "successfully read map!" << std::endl;
        std::cout << "width: " << map.getWidth() << ", height: " << map.getHeight() << std::endl;
        std::cout << "tileWidth: " << map.getTileWidth() << ", tileHeight: " << map.getTileHeight() << std::endl;
        for(auto& layer : map.getLayers())
        {
            std::cout << "layerName: " << layer.getName() << std::endl;
        }
        SDL_Color backgroundColor = map.getBackgroundColor();
        std::cout << "backgroundColor = {"
            << static_cast<int>(backgroundColor.r) << ", "
            << static_cast<int>(backgroundColor.g) << ", "
            << static_cast<int>(backgroundColor.b) << ", "
            << static_cast<int>(backgroundColor.a) << "}" << std::endl;
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << "could not read map file, error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
