#pragma once

#include <boost/optional.hpp>

#include <algorithm>
#include <array>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#pragma message("TODO remove iostream")
#include <iostream>

template <typename PathNodeType, typename HeuristicType>
class PathFinder
{
public:
    using PathNode = PathNodeType;
    using Heuristic = HeuristicType;

    using Path = std::vector<PathNode>;
    using Cost = decltype(std::declval<Heuristic>()(std::declval<PathNode>(), std::declval<PathNode>()));

    PathFinder(PathNode start_node, Heuristic heuristic = Heuristic());

    boost::optional<Path> get_optimal_path(PathNode end_node);

private:
    PathNode start_node_;
    Heuristic heuristic_;
    std::unordered_map<PathNode, PathNode> optimal_previous_nodes_;
    std::unordered_map<PathNode, Cost> g_costs_;
    std::unordered_set<PathNode> unexplored_nodes_;
    std::unordered_set<PathNode> explored_nodes_;

    Path reconstruct_path_(PathNode end_node) const;
};


template <typename PathNodeType, typename HeuristicType>
PathFinder<PathNodeType, HeuristicType>::PathFinder(PathNode start_node, Heuristic heuristic)
    : start_node_(start_node)
    , heuristic_(heuristic)
{
    unexplored_nodes_.insert(start_node);
    g_costs_[start_node] = Cost{};
    optimal_previous_nodes_[start_node_] = start_node_;
}

template <typename PathNodeType, typename HeuristicType>
auto PathFinder<PathNodeType, HeuristicType>::get_optimal_path(PathNode end_node) -> boost::optional<Path>
{
    // while path not found
    while(optimal_previous_nodes_.count(end_node) == 0)
    {
        if(unexplored_nodes_.empty())
        {
            return boost::none;
        }

        auto calc_f_cost = [this, end_node] (const PathNode& unexplored)
        {
            return g_costs_[unexplored] + heuristic_(unexplored, end_node);
        };

        auto to_explore = *std::min_element(unexplored_nodes_.begin(), unexplored_nodes_.end(),
            [this, end_node, &calc_f_cost] (const PathNode& lhs, const PathNode& rhs)
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

template <typename PathNodeType, typename HeuristicType>
auto PathFinder<PathNodeType, HeuristicType>::reconstruct_path_(PathNode end_node) const -> Path
{
    Path path;
    for(PathNode walk_node = end_node; walk_node != start_node_; walk_node = optimal_previous_nodes_.at(walk_node))
    {
        path.push_back(walk_node);
    }
    std::reverse(path.begin(), path.end());
    return path;
};
