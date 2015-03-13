#include "Map.h"

#include "res_path.h"

#include <tmx/TileLayer.h>

#include <SDL_image.h>

#include <regex>
#include <sstream>
#include <stdexcept>

void Cell::draw(int screenMapX, int screenMapY) const
{
	if (p_texture_ == nullptr)
	{
		// cell is empty; nothing to draw
		return;
	}
	int tile_width = p_map_->getTileWidth();
	int tile_height = p_map_->getTileHeight();
	SDL_Rect src_rect{ texture_offset_x_, texture_offset_y_, tile_width, tile_height };
	SDL_Rect dest_rect{ screenMapX + x_ * tile_width, screenMapY + y_ * tile_height, tile_width, tile_height };
	SDL_RenderCopy(p_map_->p_renderer_, p_texture_, &src_rect, &dest_rect);
}

Map::Map(SDL_Renderer *p_renderer, const std::string& file_path)
    : res_path_(getResourcePath("map"))
	, p_renderer_(p_renderer)
{
    readFile(file_path);
}

void Map::readFile(const std::string& file_path)
{
	std::string full_path = res_path_ + file_path;
    p_map_ = tmx::Map::parseFile(full_path);
    if(p_map_ == nullptr)
    {
        throw std::runtime_error("could not parse map " + full_path);
    }
    if(p_map_->getOrientation() != tmx::Orientation::ORTHOGONAL)
    {
        throw std::runtime_error("only orthogonal maps are supported");
    }

    loadTileSets();
    loadCells();
}

int Map::getWidth() const
{
    // cast from unsigned int -> int
    return static_cast<int>(p_map_->getWidth());
}

int Map::getHeight() const
{
    // cast from unsigned int -> int
    return static_cast<int>(p_map_->getHeight());
}

int Map::getTileWidth() const
{
    // cast from unsigned int -> int
    return static_cast<int>(p_map_->getTileWidth());
}

int Map::getTileHeight() const
{
    // cast from unsigned int -> int
    return static_cast<int>(p_map_->getTileHeight());
}

// converts two characters [00-FF] into a byte
static uint8_t hexToByte(const std::string& hex_byte)
{
    if(hex_byte.length() != 2)
    {
        throw std::runtime_error("hex_byte must be 2 characters, got " + hex_byte);
    }
    unsigned int result;
    std::stringstream sstr;
    sstr << hex_byte;
    if(!(sstr >> std::hex >> result))
    {
        throw std::runtime_error("invalid hex_byte: " + hex_byte);
    }
    return static_cast<uint8_t>(result);
}

// hex_color should look like "#RRGGBB"
static SDL_Color hexToColor(const std::string& hex_color)
{
    // use regex to extract R,G,B
    std::regex color_regex("#([0-9A-F]{2})([0-9A-F]{2})([0-9A-F]{2})", std::regex::icase);
    std::smatch match;
    if(!std::regex_match(hex_color, match, color_regex))
    {
        throw std::runtime_error("expected hex color, got " + hex_color);
    }

    // store results into an SDL_Color
    SDL_Color result;
    result.r = hexToByte(match.str(1));
    result.g = hexToByte(match.str(2));
    result.b = hexToByte(match.str(3));
    result.a = 255;
    return result;
}

SDL_Color Map::getBackgroundColor() const
{
    return hexToColor(p_map_->getBackgroundColor());
}

bool Map::isInMap(int x, int y) const
{
    return x >= 0 && y >= 0 && x < getWidth() && y < getHeight();
}

const Cell& Map::getCell(int x, int y) const
{
    if(!isInMap(x, y))
    {
        std::ostringstream message;
        message << "coordinate {" << x << ", " << y << "} not in map";
        throw std::runtime_error(message.str());
    }
    return const_cast<Map*>(this)->getCell_(x, y);
}

void Map::draw(int screenOffsetX, int screenOffsetY) const
{
	//TODO cull cells from outside viewport
	for (int y = 0; y < getHeight(); ++y)
	{
		for (int x = 0; x < getWidth(); ++x)
		{
			getCell(x, y).draw(screenOffsetX, screenOffsetY);
		}
	}
}

Cell& Map::getCell_(int x, int y)
{
    return cells_[y * getWidth() + x];
}

void Map::loadTileSets()
{
    for(auto p_tileset : p_map_->getTileSets())
    {
        if(p_tileset->hasImage())
        {
			std::string image_path = p_tileset->getImage()->getSource().string();
			tile_set_textures_.emplace(std::make_pair(p_tileset, loadImage(image_path)));
        }
    }
}

void Map::loadCells()
{
    // create vector of default-initialized cells
    cells_ = std::vector<Cell>{static_cast<std::size_t>(getWidth() * getHeight())};

    // loop through all layers
    for(auto p_layer : p_map_->getLayers())
    {
        auto p_tile_layer = dynamic_cast<const tmx::TileLayer*>(p_layer);
        if(p_tile_layer != nullptr)
        {
            // layers named "wall" contain walls
            auto& name = p_tile_layer->getName();
            bool is_wall = name == "wall";

            // loop through each tmx::Cell
            int i = 0;
            for(auto tmxCell : *p_tile_layer)
            {
                // calculate x, y of cell
                int y = i / getWidth();
                int x = i - y * getWidth();

                // store information in the Cell in our cells_
                auto& cell = getCell_(x, y);
				cell.p_map_ = this;
                cell.x_ = x;
                cell.y_ = y;

                auto cell_gid = tmxCell.getGID();
                auto p_tile_set = p_map_->getTileSetFromGID(cell_gid);
                // if this cell is not empty
                if(p_tile_set != nullptr)
                {
                    // calculate texture offset
                    auto relative_gid = cell_gid - p_tile_set->getFirstGID();
                    auto p_texture = tile_set_textures_.at(p_tile_set).get();
					int texture_w, texture_h;
					SDL_QueryTexture(p_texture, nullptr, nullptr, &texture_w, &texture_h);
                    auto coords = p_tile_set->getCoords(relative_gid, {static_cast<unsigned int>(texture_w), static_cast<unsigned int>(texture_h)});

                    cell.is_wall_ = is_wall;
                    cell.p_texture_ = p_texture;
                    cell.texture_offset_x_ = coords.x;
                    cell.texture_offset_y_ = coords.y;
                }

                ++i;
            }
        }
    }
}

auto Map::loadImage(const std::string& image_path) const -> TexturePtr
{
	//std::string full_path = res_path_ + image_path;
	auto& full_path = image_path;
    TexturePtr result{IMG_LoadTexture(p_renderer_, full_path.c_str()), &SDL_DestroyTexture};
    if(result == nullptr)
    {
        std::ostringstream message;
        message << "Map::loadImage(\"" << full_path << "\") error, cannot load image";
        throw std::runtime_error(message.str());
    }
    return result;
}
