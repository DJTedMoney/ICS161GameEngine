#include "Map.h"

#include <tmx/TileLayer.h>

#include <SDL_image.h>

#include <regex>
#include <sstream>

#pragma message("TODO REMOVE IOSTREAM")
#include <iostream>

Layer::Layer(const tmx::Layer* p_layer) :
    p_layer_(p_layer)
{
}

const std::string& Layer::getName() const
{
    return p_layer_->getName();
}

Map::Map(SDL_Renderer* p_renderer, const std::string& file_path)
    : p_renderer_(p_renderer)
{
    readFile(file_path);
}

void Map::readFile(const std::string& file_path)
{
    p_map_ = tmx::Map::parseFile(file_path);
    if(p_map_ == nullptr)
    {
        throw std::runtime_error("could not parse map " + file_path);
    }
    if(p_map_->getOrientation() != tmx::Orientation::ORTHOGONAL)
    {
        throw std::runtime_error("only orthogonal maps are supported");
    }

    loadTileSets();

    // test... print details for each cell in each tile layer
    for(auto p_layer : p_map_->getLayers())
    {
        auto p_tile_layer = dynamic_cast<const tmx::TileLayer*>(p_layer);
        if(p_tile_layer != nullptr)
        {
            std::cout << "tile layer!" << std::endl;
            int i = 0;
            for(auto cell : *p_tile_layer)
            {
                int y = i / getWidth();
                int x = i - y;

                auto gid = cell.getGID();
                auto p_tileset = p_map_->getTileSetFromGID(gid);
                std::string source;
                if(p_tileset == nullptr)
                {
                    source = "no-tileset";
                }
                else
                {
                    source = "tileset: ";
                    assert(p_tileset != nullptr);
                    const tmx::Image* p_image;
                    if(p_tileset->hasImage())
                    {
                        source += std::string("p_tileset->hasImage(): ");
                        p_image = p_tileset->getImage();
                    }
                    else
                    {
                        source += std::string("!p_tileset->hasImage(): ");
                        auto p_tile = p_tileset->getTile(gid);
                        assert(p_tile != nullptr);
                        p_image = p_tile->getImage();
                    }
                    assert(p_image != nullptr);
                    source += std::string(p_image->getSource().string());
                }

                std::cout << "    cell(" << x << ", " << y << "); gid: " << cell.getGID()
                    << ", path: \"" << source << "\"" << std::endl;

                ++i;
            }
        }
    }
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

std::vector<Layer> Map::getLayers() const
{
    std::vector<Layer> result;
    auto src = p_map_->getLayers();
    std::transform(src.begin(), src.end(), std::back_inserter(result), [] (const tmx::Layer* p_layer) { return Layer(p_layer); });
    return result;
}

void Map::loadTileSets()
{
    for(auto p_tileset : p_map_->getTileSets())
    {
        if(p_tileset->hasImage())
        {
            tile_set_surfaces_.emplace(std::make_pair(p_tileset, loadImage(p_tileset->getImage()->getSource().string())));
            //tile_set_surfaces_[p_tileset] = loadImage(p_tileset->getImage()->getSource().string());
        }
    }
}

auto Map::loadImage(const std::string& image_path) const -> SurfacePtr
{
    SurfacePtr result{IMG_Load(image_path.c_str()), &SDL_FreeSurface};
    if(result == nullptr)
    {
        std::ostringstream message;
        message << "Map::loadImage(\"" << image_path << "\") error, cannot load image";
        throw std::runtime_error(message.str());
    }
    return result;
}
