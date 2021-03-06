/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: NodeGraph
 * The class is a container for a Boost graph of the nodes (m_nodeGraph).
 * It has handy methods to handle Nodes in the graph, generate the map.
 *
 * All the methods except NodeGraph::edgeExists(n1, n2) serves to map generation.
 * (see generation algo in Map::createNewMap())
 *
 * NodeGraph::edgeExists(n1, n2) serves to check if player's move are possible.
 */
#ifndef NODEGRAPH_H
#define NODEGRAPH_H

// Includes:
#include <vector>
#include <memory>
#include <boost/graph/adjacency_list.hpp>

class Node;


namespace boost
{
/**
 * @struct Edge
 * Custom edge of the graph in order to run biconnected_components algorithms
 */
    typedef struct
    {
      typedef edge_property_tag kind;
    } Edge;
}



/**
 * @typedef BoostNodeGraph
 * Member graph typedef
 */
typedef boost::adjacency_list < boost::vecS, boost::vecS, boost::undirectedS,
       std::shared_ptr<Node> , boost::property < boost::Edge, std::size_t > > BoostNodeGraph;

/**
 * @typedef vertex_index_t
 * Id of a vertex in the graph (unsigned long)
 * At Vertex (node) remove, Id's are mixed.
 */
typedef BoostNodeGraph::vertex_descriptor VertexId;

/**
 * @typedef edge_index_t
 * This is a struct
 */
typedef BoostNodeGraph::edge_descriptor  EdgeDescription;





class NodeGraph
{
public:
    NodeGraph();

    ~NodeGraph();

    // Getters:
    unsigned long nodeCount() const;
    std::shared_ptr<Node> node(unsigned long lNodeIndex) const;
   void getAdjacentNodesOf(const std::shared_ptr<Node> &node, std::vector<std::shared_ptr<Node>> & nodeList ) const;

    // Setters:

    // Methods:
    void addIsolateNode(const std::shared_ptr<Node> & node);
    bool connectNodes(const std::shared_ptr<Node> & node1, const std::shared_ptr<Node> & node2);
    void removeAbsentNodesAndEdges();
    void removeNonBridgeEdges(unsigned long lRemainingTargetCount);
    bool edgeExists(const std::shared_ptr<Node> & node1, const std::shared_ptr<Node> & node2) const;
    void clear();
    void updateNodeIds();



    // Slots
    void setAdjacentsCandidate(const std::shared_ptr<Node> & node);


    // Should be used for unit testing only
    unsigned long edgeCount() const;
    bool isConnected() const;
    void printGraphDebug();


private:
    // Methods:
    void selectNonBridges(std::vector<EdgeDescription> & edgeList);  // not const
    std::pair<VertexId, bool> nodeIndex(const std::shared_ptr<Node> & node) const;

    // Members:
    BoostNodeGraph m_nodeGraph;

};

#endif // NODEGRAPH_H
