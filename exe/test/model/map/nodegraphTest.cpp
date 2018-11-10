#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include "model/map/nodegraph.h"

#include "model/node/node.h"
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/graph/graph_utility.hpp>


BOOST_AUTO_TEST_SUITE( graph_suite )

//using namespace boost;
void createSampleGraph( NodeGraph & g, std::vector<std::shared_ptr<Node>> & nodes)
{



    g.clear();
    nodes.clear();
    nodes.resize(9);
    for (auto&& n : nodes)
    {
        n = Node::create() ;
        g.addIsolateNode(n);
    }
    g.connectNodes(nodes[0], nodes[5]);
    g.connectNodes(nodes[1], nodes[0]);
    g.connectNodes(nodes[4], nodes[5]);
    g.connectNodes(nodes[4], nodes[1]);
    g.connectNodes(nodes[2], nodes[1]);
    g.connectNodes(nodes[3], nodes[1]);
    g.connectNodes(nodes[2], nodes[3]);
    g.connectNodes(nodes[0], nodes[6]);
    g.connectNodes(nodes[8], nodes[6]);
    g.connectNodes(nodes[7], nodes[6]);
    g.connectNodes(nodes[7], nodes[8]);
}



BOOST_AUTO_TEST_CASE(isConnected)
{
    NodeGraph g;
    std::vector<std::shared_ptr<Node>> nodes(6);

    for (auto&& n : nodes)
    {
        n = Node::create() ;
        g.addIsolateNode(n);
    }

    g.connectNodes(nodes[0], nodes[1]);
    g.connectNodes(nodes[1], nodes[4]);
    g.connectNodes(nodes[4], nodes[0]);
    g.connectNodes(nodes[2], nodes[5]);

    BOOST_CHECK_EQUAL(g.isConnected(), false);

    g.connectNodes(nodes[2], nodes[1]);
    BOOST_CHECK_EQUAL(g.isConnected(), false);

    g.connectNodes(nodes[2], nodes[3]);
    BOOST_CHECK_EQUAL(g.isConnected(), true);

    g.connectNodes(nodes[4], nodes[3]);
    g.connectNodes(nodes[5], nodes[3]);
    BOOST_CHECK_EQUAL(g.isConnected(), true);
}



bool testVectorContainsNode(const std::vector<std::shared_ptr<Node>> & nodeList, const std::shared_ptr<Node> & node)
{
    for (auto&& n : nodeList)
    {
        if (n == node)
            return true;
    }
    return false;
}

BOOST_AUTO_TEST_CASE(getAdjacentNodesOf)
{
    NodeGraph g;
    std::vector<std::shared_ptr<Node>> nodes;
    createSampleGraph(g, nodes);

    std::vector<std::shared_ptr<Node>>  adjacentNodes;
    g.getAdjacentNodesOf(nodes[1], adjacentNodes);
    BOOST_CHECK_EQUAL(adjacentNodes.size(), 4);

    BOOST_CHECK_EQUAL(testVectorContainsNode(adjacentNodes, nodes[0]), true);
    BOOST_CHECK_EQUAL(testVectorContainsNode(adjacentNodes, nodes[4]), true);
    BOOST_CHECK_EQUAL(testVectorContainsNode(adjacentNodes, nodes[2]), true);
    BOOST_CHECK_EQUAL(testVectorContainsNode(adjacentNodes, nodes[3]), true);
    BOOST_CHECK_EQUAL(testVectorContainsNode(adjacentNodes, nodes[1]), false);
    BOOST_CHECK_EQUAL(testVectorContainsNode(adjacentNodes, nodes[5]), false);
    BOOST_CHECK_EQUAL(testVectorContainsNode(adjacentNodes, nodes[6]), false);
    BOOST_CHECK_EQUAL(testVectorContainsNode(adjacentNodes, nodes[7]), false);
    BOOST_CHECK_EQUAL(testVectorContainsNode(adjacentNodes, nodes[8]), false);

    g.connectNodes(nodes[7], nodes[1]);

    g.getAdjacentNodesOf(nodes[1], adjacentNodes);
    BOOST_CHECK_EQUAL(adjacentNodes.size(), 5);

    BOOST_CHECK_EQUAL(testVectorContainsNode(adjacentNodes, nodes[0]), true);
    BOOST_CHECK_EQUAL(testVectorContainsNode(adjacentNodes, nodes[4]), true);
    BOOST_CHECK_EQUAL(testVectorContainsNode(adjacentNodes, nodes[2]), true);
    BOOST_CHECK_EQUAL(testVectorContainsNode(adjacentNodes, nodes[3]), true);
    BOOST_CHECK_EQUAL(testVectorContainsNode(adjacentNodes, nodes[1]), false);
    BOOST_CHECK_EQUAL(testVectorContainsNode(adjacentNodes, nodes[5]), false);
    BOOST_CHECK_EQUAL(testVectorContainsNode(adjacentNodes, nodes[6]), false);
    BOOST_CHECK_EQUAL(testVectorContainsNode(adjacentNodes, nodes[7]), true);
    BOOST_CHECK_EQUAL(testVectorContainsNode(adjacentNodes, nodes[8]), false);

}




BOOST_AUTO_TEST_CASE(removeAbsentNodesAndEdges1)
{
    NodeGraph g;
    std::vector<std::shared_ptr<Node>> nodes;
    createSampleGraph(g, nodes);

    g.removeAbsentNodesAndEdges();
    BOOST_CHECK_EQUAL(g.edgeCount(), 0);
    BOOST_CHECK_EQUAL(g.nodeCount(), 0);
}

BOOST_AUTO_TEST_CASE(removeAbsentNodesAndEdges2)
{
    NodeGraph g;
    std::vector<std::shared_ptr<Node>> nodes;
    createSampleGraph(g, nodes);

    nodes[7]->setIntoCandidateState();
    nodes[1]->setIntoCandidateState();
    nodes[0]->setIntoExistingState();
    nodes[4]->setIntoExistingState();
    nodes[5]->setIntoExistingState();


    g.removeAbsentNodesAndEdges();
    BOOST_CHECK_EQUAL(g.edgeCount(), 2);
    BOOST_CHECK_EQUAL(g.nodeCount(), 3);

    BOOST_CHECK_EQUAL(g.edgeExists(nodes[0], nodes[4]), false);
    BOOST_CHECK_EQUAL(g.edgeExists(nodes[0], nodes[5]), true);
    BOOST_CHECK_EQUAL(g.edgeExists(nodes[5], nodes[4]), true);
    BOOST_CHECK_EQUAL(g.edgeExists(nodes[0], nodes[1]), false);

    BOOST_CHECK_EQUAL(g.edgeCount(), 2);

}




BOOST_AUTO_TEST_CASE(removeNonBridgeEdges1)
{
    NodeGraph g;
    std::vector<std::shared_ptr<Node>> nodes;
    createSampleGraph(g, nodes);

    BOOST_CHECK_EQUAL(g.edgeCount(), 11);
    BOOST_CHECK_EQUAL(g.isConnected(), true);

    g.removeNonBridgeEdges(0);
    BOOST_CHECK_EQUAL(g.edgeCount(), 8);
    BOOST_CHECK_EQUAL(g.isConnected(), true);
    //g.printGraph();
}
BOOST_AUTO_TEST_CASE(removeNonBridgeEdges2)
{
    NodeGraph g;
    std::vector<std::shared_ptr<Node>> nodes;
    createSampleGraph(g, nodes);

    BOOST_CHECK_EQUAL(g.edgeCount(), 11);
    BOOST_CHECK_EQUAL(g.isConnected(), true);

    g.removeNonBridgeEdges(9);
    BOOST_CHECK_EQUAL(g.edgeCount(), 9);
    BOOST_CHECK_EQUAL(g.isConnected(), true);
    //g.printGraph();
}
BOOST_AUTO_TEST_CASE(removeNonBridgeEdges3)
{
    NodeGraph g;
    std::vector<std::shared_ptr<Node>> nodes;
    createSampleGraph(g, nodes);

    BOOST_CHECK_EQUAL(g.edgeCount(), 11);
    BOOST_CHECK_EQUAL(g.isConnected(), true);

    g.removeNonBridgeEdges(8);
    BOOST_CHECK_EQUAL(g.edgeCount(), 8);
    BOOST_CHECK_EQUAL(g.isConnected(), true);
    //g.printGraph();
}
BOOST_AUTO_TEST_CASE(removeNonBridgeEdges4)
{
    NodeGraph g;
    std::vector<std::shared_ptr<Node>> nodes;
    createSampleGraph(g, nodes);

    BOOST_CHECK_EQUAL(g.edgeCount(), 11);
    BOOST_CHECK_EQUAL(g.isConnected(), true);

    g.removeNonBridgeEdges(11);
    BOOST_CHECK_EQUAL(g.edgeCount(), 11);
    BOOST_CHECK_EQUAL(g.isConnected(), true);
    //g.printGraph();
}
BOOST_AUTO_TEST_CASE(edgeExists)
{
    NodeGraph g;
    std::vector<std::shared_ptr<Node>> nodes(6);

    for (auto&& n : nodes)
    {
        n = Node::create() ;
        n->setIntoExistingState();
        g.addIsolateNode(n);
    }

    g.connectNodes(nodes[0], nodes[1]);
    g.connectNodes(nodes[1], nodes[4]);
    g.connectNodes(nodes[4], nodes[0]);
    g.connectNodes(nodes[2], nodes[5]);

    BOOST_CHECK_EQUAL(g.edgeExists(nodes[0], nodes[1]), true);
    BOOST_CHECK_EQUAL(g.edgeExists(nodes[1], nodes[4]), true);
    BOOST_CHECK_EQUAL(g.edgeExists(nodes[4], nodes[0]), true);
    BOOST_CHECK_EQUAL(g.edgeExists(nodes[2], nodes[5]), true);
    BOOST_CHECK_EQUAL(g.edgeExists(nodes[0], nodes[5]), false);
    BOOST_CHECK_EQUAL(g.edgeExists(nodes[4], nodes[2]), false);

}


BOOST_AUTO_TEST_CASE(setAdjacentsCandidate)
{
    NodeGraph g;
    std::vector<std::shared_ptr<Node>> nodes;
    createSampleGraph(g, nodes);

    BOOST_CHECK_EQUAL(nodes[0]->isCandidate(), false);
    BOOST_CHECK_EQUAL(nodes[4]->isCandidate(), false);
    BOOST_CHECK_EQUAL(nodes[2]->isCandidate(), false);
    BOOST_CHECK_EQUAL(nodes[3]->isCandidate(), false);
    BOOST_CHECK_EQUAL(nodes[1]->isCandidate(), false);
    BOOST_CHECK_EQUAL(nodes[5]->isCandidate(), false);
    BOOST_CHECK_EQUAL(nodes[6]->isCandidate(), false);
    BOOST_CHECK_EQUAL(nodes[7]->isCandidate(), false);
    BOOST_CHECK_EQUAL(nodes[8]->isCandidate(), false);

    g.setAdjacentsCandidate(nodes[1]);


    BOOST_CHECK_EQUAL(nodes[0]->isCandidate(), true);
    BOOST_CHECK_EQUAL(nodes[4]->isCandidate(), true);
    BOOST_CHECK_EQUAL(nodes[2]->isCandidate(), true);
    BOOST_CHECK_EQUAL(nodes[3]->isCandidate(), true);
    BOOST_CHECK_EQUAL(nodes[1]->isCandidate(), false);
    BOOST_CHECK_EQUAL(nodes[5]->isCandidate(), false);
    BOOST_CHECK_EQUAL(nodes[6]->isCandidate(), false);
    BOOST_CHECK_EQUAL(nodes[7]->isCandidate(), false);
    BOOST_CHECK_EQUAL(nodes[8]->isCandidate(), false);

}


BOOST_AUTO_TEST_SUITE_END()
