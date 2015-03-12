#pragma once

#include <tmx/Map.h>

#include <SDL.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Cell
{
public:
    int getX() const { return x_; }
    int getY() const { return y_; }
    bool isWall() const { return is_wall_; }
    SDL_Surface *getSurface() const { return p_surface_; }
    int getSurfaceOffsetX() const { return surface_offset_x_; }
    int getSurfaceOffsetY() const { return surface_offset_y_; }

private:
    friend class Map;
    int x_ = 0;
    int y_ = 0;
    bool is_wall_ = false;
    SDL_Surface *p_surface_ = nullptr;
    int surface_offset_x_ = 0;
    int surface_offset_y_ = 0;
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

    bool isInMap(int x, int y) const;
    const Cell& getCell(int x, int y) const;

private:
    using SurfacePtr = std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>;

    Cell& getCell_(int x, int y);

    void loadTileSets();
    void loadCells();
    SurfacePtr loadImage(const std::string& image_path) const;

    SDL_Renderer *p_renderer_;
    std::unique_ptr<tmx::Map> p_map_;
    std::unordered_map<const tmx::TileSet*, SurfacePtr> tile_set_surfaces_;
    std::vector<Cell> cells_;
};
