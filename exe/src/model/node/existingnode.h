/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                       */
/*----------------------------------------------------------------*/
/**
 * CLASS: ExistingNode
 * State "Existing" of a node.
 * It can have 3 states: 1- Absent, 2- Candidate (Candidate to be existent) and  3- Existing
 *
 * The state diagram is:  Absent -----> Candidate -----> Existing
 *                            \____________________________^
 *
 * So, when the Existing state is reached, the state can't evolve.
 */
#ifndef EXISTINGNODE_H
#define EXISTINGNODE_H

// Includes:
#include "nodestate.h"

class ExistingNode : public NodeState
{
public:
    ExistingNode();

    ~ExistingNode() override;

    // Getters:

    // Setters:

    // Methods:
    virtual void setIntoCandidateState(std::shared_ptr<Node> & node) override;
    virtual void setIntoExistingState(std::shared_ptr<Node> & node) override;
    virtual bool exists() const override;

    virtual bool isCandidate() const override;
    virtual bool isAbsent() const override;



private:
    // Methods:

    // Members:

};

#endif // EXISTINGNODE_H
