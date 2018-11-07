/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                       */
/*----------------------------------------------------------------*/
/**
 * CLASS: NodeState
 * Abstract class of the state of a node.
 * A node can have 3 states: 1- Absent, 2- Candidate (Candidate to be existent) and  3- Existing
 *
 * The state diagram is:  Absent -----> Candidate -----> Existing
 *                            \____________________________^
 *
 */
#ifndef NODESTATE_H
#define NODESTATE_H

// Includes:
#include "node.h"

class NodeState
{
public:
    NodeState();
    virtual ~NodeState();

    // Getters:

    // Setters:

    // Methods:
    virtual void setIntoCandidateState(std::shared_ptr<Node> & node) = 0 ;
    virtual void setIntoExistingState(std::shared_ptr<Node> & node) = 0 ;
    virtual bool exists() = 0 ;

private:
    // Methods:

    // Members:

};

#endif // NODESTATE_H


