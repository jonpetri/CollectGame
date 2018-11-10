/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                       */
/*----------------------------------------------------------------*/
/**
 * CLASS: NodeSignalTester
 *
 */
#ifndef NODESIGNALTESTER_H
#define NODESIGNALTESTER_H

// Includes:
#include <memory>
#include "model/node/node.h"
class NodeSignalTester
{
public:
    NodeSignalTester();

    ~NodeSignalTester();

    // Getters:

    // Setters:

    // slots:
    void slotGetNode(const std::shared_ptr<Node> & n);

    std::shared_ptr<Node> node() const;
    void setNode(const std::shared_ptr<Node> &node);

private:
    // Methods:

    // Members:
    std::shared_ptr<Node>  m_node;

};

#endif // NODESIGNALTESTER_H
