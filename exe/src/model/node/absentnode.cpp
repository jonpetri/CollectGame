#include "absentnode.h"
#include "existingnode.h"
#include "candidatenode.h"


//-----------------------------------------------------------------------------------------------------------------------
// AbsentNode :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
AbsentNode::AbsentNode()
{

}
AbsentNode::~AbsentNode()
{

}


//-----------------------------------------------------------------------------------------------------------------------
// AbsentNode :: Getters
//-----------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
// AbsentNode :: Setters
//-----------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
// AbsentNode :: Methods
//-----------------------------------------------------------------------------------------------------------------------


/**
 * Set the node into Candidate state.
 * @param node
 */
void AbsentNode::setIntoCandidateState(std::shared_ptr<Node> &node)
{
    std::unique_ptr<NodeState> state = std::unique_ptr<NodeState>(new CandidateNode);
    node->setState(state);
    node->addToCandidateList(node);
}

/**
 * Set the node into Existing state.
 * @param node
 */
void AbsentNode::setIntoExistingState(std::shared_ptr<Node> &node)
{
    std::unique_ptr<NodeState> state = std::unique_ptr<NodeState>(new ExistingNode);
    node->setState(state);
    node->setAdjacentsAsCandidate(node);
}

/**
 * indicate if the node is in Existing state.
 * @return  false
 */
bool AbsentNode::exists()
{
    return false;
}
