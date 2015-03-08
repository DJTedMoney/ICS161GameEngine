#include "Map.h"

#include <regex>
#include <sstream>

Layer::Layer(const tmx::Layer* p_layer) :
    p_layer_(p_layer)
{
}

const std::string& Layer::getName() const
{
    return p_layer_->getName();
}

Map::Map(const std::string& file_path)
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
