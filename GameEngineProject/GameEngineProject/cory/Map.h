#pragma once

#include <tmx/Map.h>

#include <SDL.h>

#include <memory>
#include <string>
#include <unordered_map>
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
    Map(SDL_Renderer* p_renderer, const std::string& file_path);

    void readFile(const std::string& file_path);

    int getWidth() const;
    int getHeight() const;

    int getTileWidth() const;
    int getTileHeight() const;

    SDL_Color getBackgroundColor() const;

    std::vector<Layer> getLayers() const;

private:
    using SurfacePtr = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>;
    void loadTileSets();
    SurfacePtr loadImage(const std::string& image_path) const;

    SDL_Renderer *p_renderer_;
    std::unique_ptr<tmx::Map> p_map_;
    std::unordered_map<const tmx::TileSet*, SurfacePtr> tile_set_surfaces_;
};
