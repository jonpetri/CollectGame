/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                       */
/*----------------------------------------------------------------*/
/**
 * CLASS: CandidateNode
 * State "Candidate" of a node.
 * It can have 3 states: 1- Absent, 2- Candidate (Candidate to be existent) and  3- Existing
 *
 * The state diagram is:  Absent -----> Candidate -----> Existing
 *                            \____________________________^
 *
 * So the state can evolve only into "Existing".
 * When it become existent, the signal setAdjacentsAsCandidate is called,
 * and :
 *   - all the adjacent absent nodes become Candidate.
 *   - The  adjacent candidate do not change of state
 *   - The existing's keep being existent, following the state diagram.
 */
#ifndef CANDIDATENODE_H
#define CANDIDATENODE_H

// Includes:
#include "nodestate.h"


class CandidateNode : public NodeState
{
public:
    CandidateNode();

    ~CandidateNode() override;

    // Getters:

    // Setters:

    // Methods:
    virtual void setIntoCandidateState(std::shared_ptr<Node> & node) override;
    virtual void setIntoExistingState(std::shared_ptr<Node> &node) override;
    virtual bool exists() const override;

    virtual bool isCandidate() const override;
    virtual bool isAbsent() const override;



private:
    // Methods:

    // Members:

};

#endif // CANDIDATENODE_H
