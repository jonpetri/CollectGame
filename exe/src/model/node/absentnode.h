/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                       */
/*----------------------------------------------------------------*/
/**
 * CLASS: AbsentNode
 * State "absent" of a node.
 * It can have 3 states: 1- Absent, 2- Candidate (Candidate to be existent) and  3- Existing
 *
 * The state diagram is:  Absent -----> Candidate -----> Existing
 *                            \____________________________^
 *
 * So, the state can evolve into "Candidate" or "Existing".
 *
 * When it become existent, the signal setAdjacentsAsCandidate is called,
 * and :
 *   - all the adjacent absent nodes become Candidate.
 *   - The  adjacent candidate do not change of state
 *   - The existing's keep being existent, following the state diagram.
 *
 * When the class become candidate (that happen only once in it live time), the signal addToCandidateList is called.
 */
#ifndef ABSENTNODE_H
#define ABSENTNODE_H

// Includes:
#include "nodestate.h"


class AbsentNode : public NodeState
{
public:
    AbsentNode();

    ~AbsentNode() override;

    // Getters:

    // Setters:

    // Methods:
    virtual void setIntoCandidateState(std::shared_ptr<Node> & node) override;
    virtual void setIntoExistingState(std::shared_ptr<Node> & node) override;
    virtual bool exists() override;

private:
    // Methods:

    // Members:

};

#endif // ABSENTNODE_H
