#pragma once

template <typename NodeType
    , typename HeuristicType
    , typename NodeHashType = std::hash<NodeType>
    , typename NodeEqualType = std::equal_to<NodeType>
    , typename NodeRefAllocatorType = std::allocator<std::reference_wrapper<NodeType>>
    , typename NodeRefPairAllocatorType = std::allocator<std::pair<std::reference_wrapper<NodeType>, std::reference_wrapper<NodeType>>>
    >
class PathFinder
{
public:
    using Node = NodeType;
    using Heuristic = HeuristicType;
    using NodeHash = NodeHashType;
    using NodeEqual = NodeEqualType;
    using NodeRefAllocator = NodeRefAllocatorType;

    using ScoreType = decltype(std::declval<Heuristic>().(std::declval<Node>()));

    using NodeRef = std::reference_wrapper<Node>;
    using NodeSet = std::unordered_set<NodeRef, NodeHash, NodeEqual, NodeRefAllocator>
    using NodeMap = std::unordered_map<NodeRef, NodeRef, NodeHash, NodeEqual, NodeRefPairAllocator>

    PathFinder(
        Heuristic heuristic = Heuristic(),
        NodeHash node_hash = NodeHash(),
        NodeEqual node_equal = NodeEqual(),
        NodeRefAllocator node_ref_allocator = NodeRefAllocator(),
        NodeRefPairAllocator node_ref_pair_allocator = NodeRefPairAllocator());

    template <typename OutputIt>
    bool find_path(const Node& start, const Node& end, OutputIt out) const;

private:
    Heuristic heuristic_;
    NodeHash node_hash_;
    NodeEqual node_equal_;
    NodeRefAllocator node_ref_allocator_;
    NodeRefPairAllocator node_ref_pair_allocator_;
};

template <typename T>
PathFinder<T>::PathFinder(Heuristic heuristic, NodeHash node_hash, NodeEqual equal, NodeRefAllocator node_ref_allocator, NodeRefPairAllocator node_ref_pair_allocator)
    : heuristic_(heuristic)
    , node_hash_(node_hash)
    , node_equal_(node_equal)
    , node_ref_allocator_(node_ref_allocator)
    , node_ref_pair_allocator_(node_ref_pair_allocator)
{ }

template <typename NodeType, typename HashType, typename NodeEqualType, typename AllocatorType>
template <typename OutputIt>
PathFinder<NodeType, HeuristicType, HashType, NodeEqualType, AllocatorType>::find_path(Node& start, Node& end, OutputIt out)
{
    NodeSet nodes_visited(0, node_hash_, node_equal_, node_ref_allocator_);
    NodeSet nodes_to_visit(0, node_hash_, node_equal_, node_ref_allocator_);
    NodeMap previous_nodes(0, node_hash_, node_equal_, node_ref_pair_allocator_);

    nodes_to_visit.insert(std::ref(start));

    while(!nodes_to_visit.empty())
    {
    }
}
