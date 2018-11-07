#include "existingnode.h"

//-----------------------------------------------------------------------------------------------------------------------
// ExistingNode :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
ExistingNode::ExistingNode()
{

}
ExistingNode::~ExistingNode()
{

}


//-----------------------------------------------------------------------------------------------------------------------
// ExistingNode :: Getters
//-----------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
// ExistingNode :: Setters
//-----------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
// ExistingNode :: Methods
//-----------------------------------------------------------------------------------------------------------------------

/**
 * Since the node is Existing, the method does nothing.
 * @param node
 */
void ExistingNode::setIntoCandidateState(std::shared_ptr<Node> &node)
{
    (void)node; // Just to silence compiler's unused parameter warning
}

/**
 * Since the node is already Existing, the method does nothing.
 * @param node
 */
void ExistingNode::setIntoExistingState(std::shared_ptr<Node> &node)
{
    (void)node; // Just to silence compiler's unused parameter warning
}

/**
 * indicate if the node is in Existing state.
 * @return  true
 */
bool ExistingNode::exists()
{
    return true;
}


/**
 * indicate if the node is in Candidate state.
 * @return  false
 */
bool ExistingNode::isCandidate()
{
    return false;
}

/**
 * indicate if the node is in Absent state.
 * @return  false
 */
bool ExistingNode::isAbsent()
{
    return false;
}


