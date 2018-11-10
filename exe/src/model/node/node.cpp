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
    , removeFromCandidateList()
    , setAdjacentsAsCandidate()
    , m_iX(UINT_MAX)
    , m_iY(UINT_MAX)
    , m_lGraphIndex(ULONG_MAX)
    , m_bHostThePlayer(false)
    , m_state(std::unique_ptr<NodeState>(new AbsentNode))

{

}
Node::~Node()
{

}


/**
 * The class has enable_shared_from_this,
 * so we have to make sure the class will always be stored in a std::shared_ptr<Node>.
 * The constructor is private, must use that method instead.
 * @return properly build Class
 */
std::shared_ptr<Node> Node::create()
{
    struct make_shared_enabler : public Node {};
    return std::make_shared<make_shared_enabler>();
}



//-----------------------------------------------------------------------------------------------------------------------
// Node :: Getters
//-----------------------------------------------------------------------------------------------------------------------

unsigned int Node::x() const
{
    return m_iX;
}

unsigned int Node::y() const
{
    return m_iY;
}

unsigned long Node::graphIndex() const
{
    return m_lGraphIndex;
}

bool Node::hostThePlayer() const
{
    return m_bHostThePlayer;
}

//-----------------------------------------------------------------------------------------------------------------------
// Node :: Setters
//-----------------------------------------------------------------------------------------------------------------------

void Node::setX(unsigned int iX)
{
    m_iX = iX;
}

void Node::setY(unsigned int iY)
{
    m_iY = iY;
}

void Node::setGraphIndex(unsigned long value)
{
    m_lGraphIndex = value;
}


/**
 * Method trigered by the class player, according his position
 * @param [in] bStatus true if the node host the player
 */
void Node::setHostThePlayer(bool bStatus)
{
     m_bHostThePlayer = bStatus;
}
//-----------------------------------------------------------------------------------------------------------------------
// Node :: Methods
//-----------------------------------------------------------------------------------------------------------------------

/**
 * Set the node into Candidate state, is the current state allows it.
 * @param [in] node
 */
void Node::setIntoCandidateState()
{
    std::shared_ptr<Node> n = shared_from_this();
    m_state->setIntoCandidateState(n);
}

/**
 * Set the node into Existing state, is the current state allows it.
 * @param [in] node
 */
void Node::setIntoExistingState()
{
    std::shared_ptr<Node> n = shared_from_this();
    m_state->setIntoExistingState(n);
}


/**
 * indicate if the node is in Existing state.
 * @return  true if Existing state
 */
bool Node::exists() const
{
    return m_state->exists();
}

/**
 * indicate if the node is in Candidate state.
 * @return  true if Candidate state
 */
bool Node::isCandidate() const
{
    return m_state->isCandidate();
}

/**
 * indicate if the node is in Absent state.
 * @return  true if Absent state
 */
bool Node::isAbsent() const
{
    return m_state->isAbsent();
}

/**
 * Retrieve the character to be used to represent the node
 * @return "@" if player, "O" if existing, " " if not existing
 */
std::string Node::consolePrintCharacter() const
{
    if (this->exists())
    {
        if (m_bHostThePlayer)
            return "@";
        else
            return "O";
    }
    else
    {
        return " ";
    }
}
/**
 * Retrieve the string about the item to be displayed in the console.
 * @return string to be print
 */
std::string Node::consoleFullPrint() const
{
    // The return print is:
    // Node[4 ; 2]
    return "Node[" + std::to_string(m_iX+1) + " ; " + std::to_string(m_iY+1) +"]";
}

/**
 * Set the node to a new state. (private)
 * @param [in] state
 */
void Node::setState(std::unique_ptr<NodeState> &state)
 {
     m_state.reset();
     m_state = std::move(state);
 }

