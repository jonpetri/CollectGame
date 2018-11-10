#include "nodegraph.h"

#include <map>
#include <random>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/biconnected_components.hpp>

#include "model/node/node.h"

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
unsigned long NodeGraph::edgeCount() const
{
    return num_edges(m_nodeGraph);
}

/**
 * Retrieve the node count.
 * This method Should be used for unit testing only.
 * @return node count
 */
unsigned long NodeGraph::nodeCount() const
{
    return num_vertices(m_nodeGraph);
}

/**
 * Return the node at the index.
 * iNodeIndex goes from 0 to NodeGraph::nodeCount()
 * @param iNodeIndex
 * @return node
 */
std::shared_ptr<Node> NodeGraph::node(unsigned long lNodeIndex) const
{
    //VertexId id = iNodeIndex;
    if (lNodeIndex >= boost::num_vertices(m_nodeGraph))
    {
        throw std::out_of_range( "In NodeGraph::node(iNodeIndex)" );
    }

    return m_nodeGraph[lNodeIndex] ;
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
    std::pair<VertexId, bool> idNode = this->nodeIndex(node);

    if (idNode.second == true)
    {
        for (boost::tie(adjIt, adjEnd) = adjacent_vertices(idNode.first, m_nodeGraph); adjIt != adjEnd; ++adjIt)
        {
            nodeList.push_back(m_nodeGraph[vertexidMap[*adjIt]]);
        }
    }
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
bool NodeGraph::connectNodes(const std::shared_ptr<Node> &node1, const std::shared_ptr<Node> &node2)
{
    // As the father class (Map) is in charge of adding all the Nodes before connecting then,
    // Node's existence in the graph is not checked, in order to make the code faster.
    std::pair<VertexId, bool> idNode1, idNode2;
    idNode1 = this->nodeIndex(node1);
    idNode2 = this->nodeIndex(node2);

    if (idNode1.second == false || idNode2.second == false)
        return false;

    add_edge(idNode1.first,idNode2.first, m_nodeGraph);
    return true;
}

/**
 * remove all the nodes that are in "Absent" or "candidate" state,
 * and remove the related edges.
 */
void NodeGraph::removeAbsentNodesAndEdges()
{
    std::shared_ptr<Node> node;
    VertexId nodeIndex;
    std::pair<BoostNodeGraph::vertex_iterator, BoostNodeGraph::vertex_iterator> it = boost::vertices(m_nodeGraph);
    auto vertexidMap = get(boost::vertex_index, m_nodeGraph);
    --it.second;
    for( ; it.first -1 != it.second; --it.second)
    {
       nodeIndex = vertexidMap[*it.second];
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
void NodeGraph::removeNonBridgeEdges(unsigned long lRemainingTargetCount)
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

    boost::graph_traits<BoostNodeGraph>::edges_size_type edgeCount;
    std::vector<EdgeDescription> nonBridgeEdgeList;
    unsigned long lRemovedEdge;

    edgeCount = num_edges(m_nodeGraph);
    this->selectNonBridges(nonBridgeEdgeList);

    while((lRemainingTargetCount < edgeCount) and (nonBridgeEdgeList.size() > 0))
    {
        // remove a random edge within that edges
        std::uniform_int_distribution<unsigned long> randomDistribution(0, nonBridgeEdgeList.size()-1);
        lRemovedEdge =  randomDistribution(gen);

        remove_edge(nonBridgeEdgeList[lRemovedEdge], m_nodeGraph);

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
bool NodeGraph::edgeExists(const std::shared_ptr<Node> &node1, const std::shared_ptr<Node> &node2) const
{
    std::pair<VertexId, bool> idNode1, idNode2;
    if (node1->exists() == false || node2->exists() == false)
        return false;

    idNode1 = this->nodeIndex(node1);
    idNode2 = this->nodeIndex(node2);

    if (idNode1.second == false || idNode2.second == false)
        return false;

    std::pair<EdgeDescription, bool> ret = edge(idNode1.first, idNode2.first, m_nodeGraph);
    return ret.second;
}

void NodeGraph::clear()
{
    m_nodeGraph.clear();
}

/**
 * Save the index of the nodes (VertexId) in the graph within the Node object.
 * Remove of nodes in the graph change the VertexId values, so updating it can be usefull
 */
void NodeGraph::updateNodeIds()
{
    VertexId nodeIndex;
    std::pair<BoostNodeGraph::vertex_iterator, BoostNodeGraph::vertex_iterator> it = boost::vertices(m_nodeGraph);
    std::vector<std::shared_ptr<Node>>  adjNodes;
    auto vertexidMap = get(boost::vertex_index, m_nodeGraph);

    for( ; it.first != it.second; ++it.first)
    {
       nodeIndex = vertexidMap[*it.first];
       m_nodeGraph[nodeIndex]->setGraphIndex(nodeIndex);
    }
}

/**
 * Set the adjacent nodes to "node" into the state candidate
 * @param [in] node
 */
void NodeGraph::setAdjacentsCandidate(const std::shared_ptr<Node> &node)
{
    auto vertexidMap = get(boost::vertex_index, m_nodeGraph);
    boost::graph_traits <BoostNodeGraph>::adjacency_iterator adjIt, adjEnd;
    std::pair<VertexId, bool> idNode = this->nodeIndex(node);

    if (idNode.second == true)
    {
        for (tie(adjIt, adjEnd) = adjacent_vertices(idNode.first, m_nodeGraph); adjIt != adjEnd; ++adjIt)
        {
            m_nodeGraph[vertexidMap[*adjIt]]->setIntoCandidateState();
        }
    }
}



/**
 * Check if there is no more than one connected component in the graph
 * @return true if all the vertices are connected
 */
bool NodeGraph::isConnected() const
{
    std::vector<unsigned long> verticesComponent(num_vertices(m_nodeGraph));
    unsigned long lCompoponentCount = boost::connected_components(m_nodeGraph, &verticesComponent[0]);

    if (lCompoponentCount == 1)
        return true;
    else
        return false;

}

/**
 * Graph print for debug
 */
void NodeGraph::printGraphDebug()
{

    std::shared_ptr<Node> node;
    VertexId nodeIndex;
    std::pair<BoostNodeGraph::vertex_iterator, BoostNodeGraph::vertex_iterator> it = boost::vertices(m_nodeGraph);
    std::vector<std::shared_ptr<Node>>  adjNodes;
    auto vertexidMap = get(boost::vertex_index, m_nodeGraph);
    this->updateNodeIds();
    for( ; it.first != it.second; ++it.first)
    {
       nodeIndex = vertexidMap[*it.first];

       node = m_nodeGraph[nodeIndex];
       std::cout << nodeIndex << " -- ";

       this->getAdjacentNodesOf(node, adjNodes);
       for (const std::shared_ptr<Node>& n : adjNodes) // const
           std::cout << n->graphIndex() << ", ";
       std::cout << std::endl;
    }
}



/**
 * (private)
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
    unsigned long lComponentTag;

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
        lComponentTag = component[*edgeIt];
        ++componentsEdgeQty[lComponentTag];
        edgeComponentTag[*edgeIt] = lComponentTag;
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


/**
 * (private)
 * Retrieve the vertex id of node in the graph.
 * @param [in] node
 * @return {VertexId, true if node find}
 */
std::pair<VertexId, bool> NodeGraph::nodeIndex(const std::shared_ptr<Node> & node) const
{
  for (VertexId id = 0; id < boost::num_vertices(m_nodeGraph); ++id)
  {
    if (m_nodeGraph[id] == node)
      return std::make_pair(id, true);
  }
  return std::make_pair(0, false);
}
