#include "player.h"

#include "model/node/node.h"

//-----------------------------------------------------------------------------------------------------------------------
// Player :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
Player::Player()
    : m_currentNode(nullptr)
    , m_startNode(nullptr)
{

}
Player::~Player()
{

}


//-----------------------------------------------------------------------------------------------------------------------
// Player :: Getters
//-----------------------------------------------------------------------------------------------------------------------
/**
 * player's current location.
 * @return node
 */
std::shared_ptr<Node> Player::currentNode() const
{
    return m_currentNode;
}

//-----------------------------------------------------------------------------------------------------------------------
// Player :: Setters
//-----------------------------------------------------------------------------------------------------------------------
/**
 * Switch from a node to another.
 * When the player switch from a node to another he is in charge of change nodes "HostThePlayer" status.
 * @param [in] node New player's location.
 */
void Player::setCurrentNode(const std::shared_ptr<Node> & node)
{
    if (m_currentNode != nullptr)
        m_currentNode->setHostThePlayer(false);

    m_currentNode = node;
    m_currentNode->setHostThePlayer(true);
}

std::shared_ptr<Node> Player::startNode() const
{
    return m_startNode;
}

void Player::setStartNode(const std::shared_ptr<Node> &startNode)
{
    m_startNode = startNode;
}



//-----------------------------------------------------------------------------------------------------------------------
// Player :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * Indicate if the player is at the start point
 * @return True if at start point
 */
bool Player::isAtStartNode() const
{
    return m_currentNode == m_startNode;
}
