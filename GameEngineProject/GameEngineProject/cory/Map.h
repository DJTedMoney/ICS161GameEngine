#pragma once

#include <tmx/Map.h>

// SDL_Color
#include <SDL_pixels.h>

#include <memory>
#include <string>
#include <vector>

class Layer
{
public:
    Layer() = default;

    const std::string& getName() const;

private:
    friend class Map;

    Layer(const tmx::Layer* p_layer);
    const tmx::Layer* p_layer_;
};

class Map
{
public:
    Map() = default;
    Map(const std::string& file_path);

    void readFile(const std::string& file_path);

    int getWidth() const;
    int getHeight() const;

    int getTileWidth() const;
    int getTileHeight() const;

    SDL_Color getBackgroundColor() const;

    std::vector<Layer> getLayers() const;

private:
    std::unique_ptr<tmx::Map> p_map_;
};
