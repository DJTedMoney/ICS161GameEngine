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
    SDL_Texture *getTexture() const { return p_texture_; }
    int getTextureOffsetX() const { return texture_offset_x_; }
    int getTextureOffsetY() const { return texture_offset_y_; }

	void draw(int screenMapX, int screenMapY) const;

private:
    friend class Map;
	Map *p_map_ = nullptr;
    int x_ = 0;
    int y_ = 0;
    bool is_wall_ = false;
    SDL_Texture *p_texture_ = nullptr;
    int texture_offset_x_ = 0;
    int texture_offset_y_ = 0;
};

class Map
{
public:
    Map() = default;
    Map(SDL_Renderer *p_renderer, const std::string& file_path);

    void readFile(const std::string& file_path);

    int getWidth() const;
    int getHeight() const;

    int getTileWidth() const;
    int getTileHeight() const;

    SDL_Color getBackgroundColor() const;

    bool isInMap(int x, int y) const;
    const Cell& getCell(int x, int y) const;

	void draw(int screenOffsetX, int screenOffsetY) const;

private:
	friend class Cell;

    using TexturePtr = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;

    Cell& getCell_(int x, int y);

    void loadTileSets();
    void loadCells();
    TexturePtr loadImage(const std::string& image_path) const;

	std::string res_path_;
	SDL_Renderer *p_renderer_;
    std::unique_ptr<tmx::Map> p_map_;
    std::unordered_map<const tmx::TileSet*, TexturePtr> tile_set_textures_;
    std::vector<Cell> cells_;
};