#include "Map.h"

#include <vector>

class MapPathNode
{
public:
    // pair(cost, adjacent_node)
    using MoveList = std::vector<std::pair<int,MapPathNode>>;

    MapPathNode(Map *p_map = nullptr, int x = 0, int y = 0)
        : p_map_(p_map)
        , x_(x)
        , y_(y)
    { }

    MapPathNode(const MapPathNode& src) = default;
    MapPathNode& operator=(const MapPathNode& src) = default;

    int get_x() const
    {
        return x_;
    }

    int get_y() const
    {
        return y_;
    }

    MoveList get_moves() const
    {
        MoveList move_list;
        for(auto& location : std::array<std::pair<int, int>, 4> {{{0, -1}, {0, 1}, {-1, 0}, {1, 0}}})
        {
			int x = x_ + location.first;
			int y = y_ + location.second;
			if (p_map_->isInMap(x, y) && !p_map_->getCell(x, y).isWall() )
            {
                move_list.push_back(std::pair<int, MapPathNode>(1, {p_map_, x, y}));
            }
        }
        return move_list;
    }

    bool operator==(const MapPathNode& rhs) const
    {
        return p_map_ == rhs.p_map_ && x_ == rhs.x_ && y_ == rhs.y_;
    }

    bool operator!=(const MapPathNode& rhs) const
    {
        return !(*this == rhs);
    }

private:
    Map *p_map_;
    int x_;
    int y_;
};

namespace std
{

template <>
struct hash<MapPathNode>
{
	using argument_type = MapPathNode;
    using result_type = std::size_t;

    result_type operator()(const argument_type& arg) const
    {
        return (arg.get_x() << 16 | arg.get_x() >> 16) ^ arg.get_y();
    }
};

}

std::ostream& operator<<(std::ostream& out, const MapPathNode& path_node)
{
    return out << "{" << path_node.get_x() << ", " << path_node.get_y() << "}";
}

struct MapHeuristic
{
    int operator()(const MapPathNode& lhs, const MapPathNode& rhs)
    {
        // manhattan distance
        return std::abs(lhs.get_x() - rhs.get_x()) + std::abs(lhs.get_y() - rhs.get_y());
    }
};