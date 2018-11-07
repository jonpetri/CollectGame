#include "node.h"
#include "nodestate.h"
#include "absentnode.h"
#include "candidatenode.h"
#include "existingnode.h"
#include <memory>
//-----------------------------------------------------------------------------------------------------------------------
// Node :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
Node::Node()
    : addToCandidateList()
    , setAdjacentsAsCandidate()
    , m_iX(0)
    , m_iY(0)
    , m_lGraphIndex(0)
    , m_state(std::unique_ptr<NodeState>(new AbsentNode))
{

}
Node::~Node()
{

}


//-----------------------------------------------------------------------------------------------------------------------
// Node :: Getters
//-----------------------------------------------------------------------------------------------------------------------

int Node::x() const
{
    return m_iX;
}

int Node::y() const
{
    return m_iY;
}

unsigned long Node::graphIndex() const
{
    return m_lGraphIndex;
}

//-----------------------------------------------------------------------------------------------------------------------
// Node :: Setters
//-----------------------------------------------------------------------------------------------------------------------

void Node::setX(int iX)
{
    m_iX = iX;
}

void Node::setY(int iY)
{
    m_iY = iY;
}

void Node::setGraphIndex(unsigned long value)
{
    m_lGraphIndex = value;
}

void Node::setState(std::unique_ptr<NodeState> &state)
 {
     m_state.reset();
     m_state = std::move(state);
 }
//-----------------------------------------------------------------------------------------------------------------------
// Node :: Methods
//-----------------------------------------------------------------------------------------------------------------------

/**
 * Set the node into Candidate state, is the current state allows it.
 * @param node
 */
void Node::setIntoCandidateState()
{
    std::shared_ptr<Node> n = shared_from_this();
    m_state->setIntoCandidateState(n);
}

/**
 * Set the node into Existing state, is the current state allows it.
 * @param node
 */
void Node::setIntoExistingState()
{
    std::shared_ptr<Node> n = shared_from_this();
    m_state->setIntoExistingState(n);
}

bool Node::exists()
{
    return m_state->exists();
}
