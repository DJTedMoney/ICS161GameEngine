#include "PathFinder.h"

#include <cstdlib>
#include <iostream>

template <std::size_t width, std::size_t height>
class ExampleMap
{
public:
//    ExampleMap()
//    {
//        for(auto& row : walls_)
//        {
//            row.fill(false);
//        }
//    }

    bool is_open(int x, int y) const
    {
        return x >= 0 && y >= 0 && x < width && y < height && !walls_[y][x];
    }

    void set_wall(int x, int y, bool wall)
    {
        walls_[y][x] = wall;
    }

private:
    std::array<std::array<bool, width>, height> walls_{};
};

template< std::size_t width, std::size_t height>
std::ostream& operator<<(std::ostream& out, const ExampleMap<width, height>& map)
{
    for(std::size_t y = 0; y != height; ++y)
    {
        for(std::size_t x = 0; x != width; ++x)
        {
            out << (map.is_open(x, y) ? '.' : '#') << std::endl;
        }
        out << std::endl;
    }

    return out;
}

template <typename MapType>
class ExamplePathNode
{
public:
    using Map = MapType;

    // pair(cost, adjacent_node)
    using MoveList = std::vector<std::pair<int,ExamplePathNode>>;

    ExamplePathNode(Map *p_map = nullptr, int x = 0, int y = 0)
        : p_map_(p_map)
        , x_(x)
        , y_(y)
    { }

    ExamplePathNode(const ExamplePathNode& src) = default;
    ExamplePathNode& operator=(const ExamplePathNode& src) = default;

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
            if(p_map_->is_open(x_ + location.first, y_ + location.second))
            {
                move_list.push_back(std::pair<int, ExamplePathNode>(1, {p_map_, x_ + location.first, y_ + location.second}));
            }
        }
        return move_list;
    }

    bool operator==(const ExamplePathNode& rhs) const
    {
        return p_map_ == rhs.p_map_ && x_ == rhs.x_ && y_ == rhs.y_;
    }

    bool operator!=(const ExamplePathNode& rhs) const
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

template <typename Map>
struct hash<ExamplePathNode<Map>>
{
    using argument_type = ExamplePathNode<Map>;
    using result_type = std::size_t;

    result_type operator()(const argument_type& arg) const
    {
        return (arg.get_x() << 16 | arg.get_x() >> 16) ^ arg.get_y();
    }
};

}

template <typename Map>
std::ostream& operator<<(std::ostream& out, const ExamplePathNode<Map>& path_node)
{
    return out << "{" << path_node.get_x() << ", " << path_node.get_y() << "}";
}

template <typename Map>
struct ExampleHeuristic
{
    int operator()(const ExamplePathNode<Map>& lhs, const ExamplePathNode<Map>& rhs)
    {
        // manhattan distance
        return std::abs(lhs.get_x() - rhs.get_x()) + std::abs(lhs.get_y() - rhs.get_y());
    }
};


template <typename Path>
//static std::ostream& print_path(std::ostream& out, const decltype(std::declval<PathFinder<ExamplePathNode<Map>, ExampleHeuristic<Map>>>().get_optimal_path(std::declval<ExamplePathNode<Map>>()))& path)
static std::ostream& print_path(std::ostream& out, const Path& path)
{
    if(path == boost::none)
    {
        std::cout << "none";
    }
    else {
        for(auto& node : path.get())
        {
            std::cout << " -> " << node;
        }
    }

    return out;
}


int main()
{
    using Map = ExampleMap<5, 5>;
    Map map;
    
    map.set_wall(1, 1, true);
    map.set_wall(1, 2, true);
    map.set_wall(1, 3, true);

    map.set_wall(2, 0, true);
    map.set_wall(2, 1, true);
    map.set_wall(2, 3, true);

    map.set_wall(3, 1, true);
    map.set_wall(3, 2, true);
    map.set_wall(3, 3, true);

    PathFinder<ExamplePathNode<Map>, ExampleHeuristic<Map>> path_finder(ExamplePathNode<Map>(&map, 0, 0));

    std::cout << "path to middle: ";
    print_path(std::cout, path_finder.get_optimal_path(ExamplePathNode<Map>(&map, 2, 2)));
    std::cout << std::endl;

    std::cout << "path to upper-right: ";
    print_path(std::cout, path_finder.get_optimal_path(ExamplePathNode<Map>(&map, 3, 0)));
    std::cout << std::endl;
    //std::cout << "path to middle: " << path_finder.get_optimal_path(ExamplePathNode<Map>(&map, 2, 2)) << std::endl;
    //std::cout << "path to upper-right: " << path_finder.get_optimal_path(ExamplePathNode<Map>(&map, 0, 3)) << std::endl;
}
