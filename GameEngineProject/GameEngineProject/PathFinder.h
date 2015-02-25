#pragma once

template <std::size_t Width, std::size_t Height>
class ExampleMap
{
public:
    constexpr auto width = Width;
    constexpr auto height = Height;

    bool is_open(int x, int y) const
    {
        return x > 0 && y > 0 && x < width && y < height && !walls_[y][x];
    }

    void set_wall(int x, int y, bool wall)
    {
        walls_[y][x] = wall;
    }

private:
    std::array<std::array<bool, width> height> walls_{};
};

class ExamplePathNode
{
public:

    // pair(cost, adjacent_node)
    using MoveList = std::vector<std::pair<int,ExamplePathNode>>;

    ExamplePathNode(ExampleMap *p_map = nullptr, int x = 0, int y = 0)
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

    NodeList get_moves() const
    {
        NodeList node_list;
        for(auto& location : std::array<std::pair<int>> {{0, -1}, {0, 1}, {-1, 0}, {1, 0}})
        {
            if(p_map_->is_open(x_ + location.first, y_ + location.second))
            {
                node_list.emplace_back(1, {p_map_, x_ + location.first, y_ + location.second});
            }
        }
        return node_list;
    }

    bool operator==(const ExamplePathNode& rhs) const
    {
        return p_map_ == rhs.p_map_ && x_ == rhs.x_ && y_ == rhs.y_;
    }

private:
    ExampleMap *p_map_;
    int x_;
    int y_;
};

namespace std
{

template <>
struct hash<ExamplePathNode>
{
    using argument_type = ExamplePathNode;
    using result_type = std::size_t;

    result_type operator()(const argument_type& arg) const
    {
        return (x_ << 16 | x_ >> 16) ^ y_;
    }
};

}


struct ExampleHeuristic
{
    int operator()(const ExamplePathNode& lhs, const ExamplePathNode& rhs)
    {
        // manhattan distance
        return std::abs(lhs.get_x() - rhs.get_x()) + std::abs(lhs.get_y(), rhs.get_y());
    }
};


template <typename PathNodeType, typename HeuristicType>
class PathFinder
{
public:
    using PathNode = PathNodeType;
    using Heuristic = HeuristicType;

    using Path = std::vector<PathNode>;
    using Cost = decltype(heuristic_(start_node_, start_node_));

    PathFinder(PathNode start_node, Heuristic heuristic = Heuristic());

    boost::optional<Path> get_optimal_path(PathNode end_node);

private:
    PathNode start_node_;
    Heurstic heuristic_;
    std::unordered_map<PathNode, PathNode> optimal_previous_nodes_;
    std::unordered_map<PathNode, Cost> g_costs_;
    std::unordered_set<PathNode> unexplored_nodes_;
    std::unordered_set<PathNode> explored_nodes_;

    Path reconstruct_path_(PathNode end_node) const;
};


template <typename ...T>
PathFinder<T...>::get_optimal_path(PathNode start_node, Heuristic heuristic)
    : start_node_(start_node)
    , heuristic_(heuristic)
{
    unexplored_nodes_.insert(start_node);
    g_costs_[start_node] = Cost{};
    optimal_previous_nodes_[start_node_] = start_node_;
}

template <typename ...T>
auto PathFinder<T...>::get_optimal_path(PathNode end_node) -> boost::optional<Path>
{
    // while path not found
    while(optimal_previous_nodes_.count(end_node) == 0)
    {
        if(unexplored_nodes_.empty())
        {
            return boost::none;
        }
        auto calc_f_cost = [=this, =end_node] (const PathNode& unexplored)
        {
            return g_costs_[unexplored] + heuristic_(unexplored, end_node);
        };

        auto to_explore = std::min_element(unexplored_nodes_.begin(), unexplored_nodes_.end(),
            [=this, =end_node] (const PathNode& lhs, const PathNode& rhs)
            {
                return calc_f_cost(lhs) < calc_f_cost(rhs);
            }
        );

        unexplored_nodes_.erase(to_explore);
        explored_nodes_.insert(to_explore);
        for(auto& move : to_explore.get_moves())
        {
            if(explored_nodes_.count(move.second) != 0)
            {
                continue;
            }
            
            auto potential_g_cost = g_costs_[to_explore] + move.first;
            if(unexplored_nodes_.count(move.second) == 0 || potential_g_cost < g_costs_[move.second])
            {
                optimal_previous_nodes_[move.second] = to_explore;
                g_costs_[move.second] = potential_g_cost;
                unexplored_nodes_.insert(move.second);
            }
        }
    }
    return reconstruct_path_(end_node);
};
