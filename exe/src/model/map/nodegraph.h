/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: NodeGraph
 *
 */
#ifndef NODEGRAPH_H
#define NODEGRAPH_H

// Includes:
#include <vector>
#include <list>
#include <iterator>
#include <memory>
#include <utility>

#include <boost/graph/biconnected_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/config.hpp>

#include "model/node/node.h"




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
 * @typedef adjacency_list
 * Graph type definition
 */
typedef boost::adjacency_list < boost::vecS, boost::vecS, boost::undirectedS,
       std::shared_ptr<Node> , boost::property < boost::Edge, std::size_t > > BoostNodeGraph;

/**
 * @typedef vertex_index_t
 * Index of a vertex in the graph (unsigned long)
 */
typedef BoostNodeGraph::vertex_descriptor VertexIndex;

/**
 * @typedef edge_index_t
 * Index of an edge in the graph (unsigned long)
 */
typedef BoostNodeGraph::edge_descriptor  EdgeDescription;





class NodeGraph
{
public:
    NodeGraph();

    ~NodeGraph();

    // Getters:

    // Setters:

    // Methods:
    void addIsolateNode(const std::shared_ptr<Node> & node);
    void connectNodes(const std::shared_ptr<Node> & node1, const std::shared_ptr<Node> & node2);
    void getAdjacentNodesOf(const std::shared_ptr<Node> &node, std::vector<std::shared_ptr<Node>> & nodeList )const;
    void removeAbsentNodesAndEdges();
    void removeNonBridgeEdges(int iRemainingTargetCount);
    bool edgeExists(const std::shared_ptr<Node> & node1, const std::shared_ptr<Node> & node2);
    void clear();

    // Slots
    void setAdjacentsCandidate(const std::shared_ptr<Node> & node);


    // Should be used for unit testing only
    int edgeCount();
    int nodeCount();
    bool isConnected();


private:
    // Methods:
    void selectNonBridges(std::vector<EdgeDescription> & edgeList);

    // Members:
    BoostNodeGraph m_nodeGraph;

};

#endif // NODEGRAPH_H
