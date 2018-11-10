#include "nodesignaltester.h"


NodeSignalTester::NodeSignalTester()
    :m_node{nullptr}
{

}
NodeSignalTester::~NodeSignalTester()
{

}

void NodeSignalTester::slotGetNode(const std::shared_ptr<Node> &n)
{
    m_node = n;
}

std::shared_ptr<Node> NodeSignalTester::node() const
{
    return m_node;
}

void NodeSignalTester::setNode(const std::shared_ptr<Node> &node)
{
    m_node = node;
}
