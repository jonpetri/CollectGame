#include "candidatenode.h"
#include "existingnode.h"
#include "node.h"

//-----------------------------------------------------------------------------------------------------------------------
// CandidateNode :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
CandidateNode::CandidateNode()
{

}
CandidateNode::~CandidateNode()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// CandidateNode :: Getters
//-----------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
// CandidateNode :: Setters
//-----------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
// CandidateNode :: Methods
//-----------------------------------------------------------------------------------------------------------------------

/**
 * Since the node is already Candidate, the method does nothing.
 * @param [in] node
 */
void CandidateNode::setIntoCandidateState(std::shared_ptr<Node> &node)
{
    (void)node; // Just to silence compiler's unused parameter warning
}

/**
 * Set the node into Existing state.
 * @param [in] node
 */
void CandidateNode::setIntoExistingState(std::shared_ptr<Node> &node)
{
    std::unique_ptr<NodeState> state = std::unique_ptr<NodeState>(new ExistingNode);
    node->removeFromCandidateList(node);
    node->setState(state);
    node->setAdjacentsAsCandidate(node);
}

/**
 * indicate if the node is in Existing state.
 * @return  false
 */
bool CandidateNode::exists() const
{
    return false;
}


/**
 * indicate if the node is in Candidate state.
 * @return  true
 */
bool CandidateNode::isCandidate() const
{
    return true;
}

/**
 * indicate if the node is in Absent state.
 * @return  false
 */
bool CandidateNode::isAbsent() const
{
    return false;
}



