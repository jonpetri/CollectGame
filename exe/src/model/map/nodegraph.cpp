#include "nodegraph.h"
#include <map>
#include <random>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/graph_utility.hpp>

//-----------------------------------------------------------------------------------------------------------------------
// NodeGraph :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
using namespace boost;

NodeGraph::NodeGraph()
    : m_nodeGraph()
{

}
NodeGraph::~NodeGraph()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// NodeGraph :: Getters
//-----------------------------------------------------------------------------------------------------------------------
/**
 * Retrieve the edge count.
 * This method Should be used for unit testing only.
 * @return edge count
 */
int NodeGraph::edgeCount()
{
    return static_cast<int>(num_edges(m_nodeGraph));
}

/**
 * Retrieve the node count.
 * This method Should be used for unit testing only.
 * @return node count
 */
int NodeGraph::nodeCount()
{
    return static_cast<int>(num_vertices(m_nodeGraph));
}

//-----------------------------------------------------------------------------------------------------------------------
// NodeGraph :: Setters
//-----------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
// NodeGraph :: Methods
//-----------------------------------------------------------------------------------------------------------------------

/**
 * Add node to the graph, it is note connected yet
 * @param [in] node
 */
void NodeGraph::addIsolateNode(const std::shared_ptr<Node> &node)
{
    node->setGraphIndex( add_vertex(node, m_nodeGraph));
}

/**
 * Make an edge between the two nodes
 * @param [in] node1
 * @param [in] node2
 */
void NodeGraph::connectNodes(const std::shared_ptr<Node> &node1, const std::shared_ptr<Node> &node2)
{
    // As the father class (Map) is in charge of adding all the Nodes before connecting then,
    // Node's existence in the graph is not checked, in order to make the code faster.

    add_edge(node1->graphIndex(), node2->graphIndex(), m_nodeGraph);
}

/**
 * Retrieve the list of the nodes connected to node.
 * @param [in] node
 * @param [out] nodeList
 */
void NodeGraph::getAdjacentNodesOf(const std::shared_ptr<Node> &node, std::vector<std::shared_ptr<Node>> & nodeList ) const
{
    nodeList.clear();

    auto vertexidMap = get(boost::vertex_index, m_nodeGraph);
    boost::graph_traits <BoostNodeGraph>::adjacency_iterator adjIt, adjEnd;

    for (boost::tie(adjIt, adjEnd) = adjacent_vertices(node->graphIndex(), m_nodeGraph); adjIt != adjEnd; ++adjIt)
    {
        nodeList.push_back(m_nodeGraph[vertexidMap[*adjIt]]);
    }

}

/**
 * remove all the nodes that are in "Absent" or "candidate" state,
 * and remove the related edges.
 */
void NodeGraph::removeAbsentNodesAndEdges()
{
    std::shared_ptr<Node> node;
    VertexIndex nodeIndex;
    //graph_traits<node_graph_t>::vertices_size_type lVertexCount = num_vertices(m_nodeGraph);
    std::pair<BoostNodeGraph::vertex_iterator, BoostNodeGraph::vertex_iterator> it = boost::vertices(m_nodeGraph);
    --it.second;
    for( ; it.first -1 != it.second; --it.second)
    {
       nodeIndex = *it.second;
       //node = get(boost::vertex_bundle, m_nodeGraph)[nodeIndex];
       node = m_nodeGraph[nodeIndex];

       if (node->exists() == false)
       {
           // first connecteed edges delete is needed
           clear_vertex(nodeIndex, m_nodeGraph);
           // then the vertex can be deleted
           remove_vertex(nodeIndex, m_nodeGraph);
       }
    }
}

/**
 * remove edges without splitting the graph.
 * The algo remove as much edge as possible, to reach the target count.
 * @param [in] iRemainingTargetCount The quantity target of edge.
 */
void NodeGraph::removeNonBridgeEdges(int iRemainingTargetCount)
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

    boost::graph_traits<BoostNodeGraph>::edges_size_type edgeCount;
    std::vector<EdgeDescription> nonBridgeEdgeList;
    unsigned int iRemovedEdge;
    unsigned long lRemainingTargetCount = static_cast<unsigned long>(iRemainingTargetCount);

    edgeCount = num_edges(m_nodeGraph);
    this->selectNonBridges(nonBridgeEdgeList);

    while((lRemainingTargetCount < edgeCount) and (nonBridgeEdgeList.size() > 0))
    {
        // remove a random edge within that edges
        std::uniform_int_distribution<> randomDistribution(0, static_cast<int>(nonBridgeEdgeList.size()-1));
        iRemovedEdge =  static_cast<unsigned int>(randomDistribution(gen));

        remove_edge(nonBridgeEdgeList[iRemovedEdge], m_nodeGraph);

        --edgeCount;
        this->selectNonBridges(nonBridgeEdgeList);
    }

}

/**
 * Test if a connection exists between node1 and node2
 * @param [in] node1
 * @param [in] node2
 * @return True if exists.
 */
bool NodeGraph::edgeExists(const std::shared_ptr<Node> &node1, const std::shared_ptr<Node> &node2)
{
    std::pair<EdgeDescription, bool> ret;
    ret = edge(node1->graphIndex(), node2->graphIndex(), m_nodeGraph);
    return ret.second;
}

void NodeGraph::clear()
{
    m_nodeGraph.clear();
}

/**
 * Set the adjacent nodes to "node" into the state candidate
 * @param [in] node
 */
void NodeGraph::setAdjacentsCandidate(const std::shared_ptr<Node> &node)
{
    auto vertexidMap = get(boost::vertex_index, m_nodeGraph);
    boost::graph_traits <BoostNodeGraph>::adjacency_iterator adjIt, adjEnd;
    //std::shared_ptr<Node> adjacentNode;

    for (tie(adjIt, adjEnd) = adjacent_vertices(node->graphIndex(), m_nodeGraph); adjIt != adjEnd; ++adjIt)
    {
        //adjacentNode = get(boost::vertex_bundle, m_nodeGraph)[vertexidMap[*ai]];
        //adjacentNode->setIntoCandidateState();
        m_nodeGraph[vertexidMap[*adjIt]]->setIntoCandidateState();
    }
}



/**
 * Check if there is no more than one connected component in the graph
 * @return true if all the vertices are connected
 */
bool NodeGraph::isConnected()
{
    std::vector<int> verticesComponent(num_vertices(m_nodeGraph));
    int iCompoponentCount = boost::connected_components(m_nodeGraph, &verticesComponent[0]);

    if (iCompoponentCount == 1)
        return true;
    else
        return false;

}

void NodeGraph::printGraph()
{
    print_graph(m_nodeGraph);
}



/**
 * Put all the non-bridge edges of the graph in edgeList.
 * The bridges are edges which make the graph non connected if deleted.
 * In other words, a bridge connect 2 separate group of vertices.
 * @param [out] edgeList The list of non-Bridge vertices
 */
void NodeGraph::selectNonBridges(std::vector<EdgeDescription> &edgeList)
{
    /* The bridges are identified thanks to the following characteristics:
     * -------------------
     * A biconnected-component is a group of vertex in which all vertices is connected at list two times.
     * When biconnected_components algorithm is launched in a boost graph,
     * it affects an id to each biconnected-component, and each edge is tagged with that id.
     * All the edges with the same id are in the same biconnected-component.
     * If a biconnected-component has an only edge, that edge is a bridge!
     */

    Edge edge;
    EdgeDescription edgeDescription;
    unsigned long componentTag;

    std::vector<unsigned long> componentsEdgeQty;
    std::map<EdgeDescription, unsigned long> edgeComponentTag;  //ULONG_MAX


    //biconnected_components algorithm run:
    property_map < BoostNodeGraph, Edge >::type component = get(edge, m_nodeGraph);
    std::size_t componentCount = biconnected_components(m_nodeGraph, component);

    componentsEdgeQty.clear();
    edgeComponentTag.clear();
    componentsEdgeQty.resize(componentCount,0);
    //edgeComponentTag.resize(edgeCount, std::numeric_limits<std::size_t>::max());

    // Iteration through edges to count the number of edge off each component,
    // and save the component tag of each edge
    graph_traits < BoostNodeGraph >::edge_iterator edgeIt, edgeItEnd;
    for (boost::tie(edgeIt, edgeItEnd) = edges(m_nodeGraph); edgeIt != edgeItEnd; ++edgeIt)
    {
        componentTag = component[*edgeIt];
        ++componentsEdgeQty[componentTag];
        edgeComponentTag[*edgeIt] = componentTag;
    }

    // if an edge's tag has a "components Edge Qty" superior to 1, it is not a bridge --> we add it to edgeList
    edgeList.clear();
    for(auto const &mapIt : edgeComponentTag) {

        if (componentsEdgeQty[mapIt.second] > 1)  // mapIt.second = component Tag
        {
            edgeList.push_back(mapIt.first);
        }

    }

}


