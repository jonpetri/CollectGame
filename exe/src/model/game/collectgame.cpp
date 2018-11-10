#include "collectgame.h"

#include <random>

#include "gameparameters.h"
#include "player.h"
#include "model/map/map.h"
#include "model/item/item.h"
#include "model/item/items.h"
#include "model/node/node.h"
//-----------------------------------------------------------------------------------------------------------------------
// CollectGame :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
CollectGame::CollectGame()
    : m_grameParameters (std::make_shared<GameParameters>())
    , m_player         (std::make_shared<Player>())
    , m_map            (std::make_shared<Map>())
    , m_items          (std::make_shared<Items>())
{

}
CollectGame::~CollectGame()
{

}






//-----------------------------------------------------------------------------------------------------------------------
// CollectGame :: Getters
//-----------------------------------------------------------------------------------------------------------------------

std::shared_ptr<GameParameters> CollectGame::gameParameters() const
{
    return m_grameParameters;
}

std::shared_ptr<Player> CollectGame::player() const
{
    return m_player;
}

std::shared_ptr<Map> CollectGame::map() const
{
    return m_map;
}

std::shared_ptr<Items> CollectGame::items() const
{
    return m_items;
}


//-----------------------------------------------------------------------------------------------------------------------
// CollectGame :: Setters
//-----------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
// CollectGame :: Methods
//-----------------------------------------------------------------------------------------------------------------------

/**
 * Map creation, items creation, items random spread in the map, player random positioning  in the map.
 */
void CollectGame::createNewGame()
{
    unsigned int iCreatedNodeCount(0);
    unsigned int iNode(0);
    unsigned int iItemCount(0);

    // Map creation
    // ------------
    this->m_map->createNewMap(m_grameParameters);

    // Items creation
    // --------------
    this->m_items->ceateRandomItems(m_grameParameters);


    // Items random spread in the map
    // ------------------------------
    iCreatedNodeCount = this->m_map->graph()->nodeCount();
    iItemCount = this->m_items->count();
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<unsigned int> nodeRandomDistribution(0, iCreatedNodeCount);
    for (unsigned int i = 0 ; i < iItemCount ; ++i)
    {
        iNode = nodeRandomDistribution(gen);
        m_items->item(i)->setHolder(m_map->graph()->node(iNode));
    }

    // Player random positioning  in the map
    // ------------------------------------
    iNode = nodeRandomDistribution(gen);
    this->m_player->setCurrentNode(m_map->graph()->node(iNode));

}

/**
 * Move the player according xMove and yMove direction, if possible.
 * @param [in] xMove Description of th move along the X axis
 * @param [in] yMove Description of th move along the Y axis
 * @return true if displacement is possible and achieved
 */
bool CollectGame::movePlayer(E_MOVE xMove, E_MOVE yMove)
{
    unsigned long iXCurrent, iYCurrent, iXTarget, iYTarget, iGridSize ;
    std::shared_ptr<Node> targetNode;

    // Player's current location
    // -------------------------
    iXCurrent = m_player->currentNode()->x();
    iYCurrent = m_player->currentNode()->y();


    // Get target node
    // ---------------

    // Verif inferior limit
    if ((iXCurrent == 0 && xMove == E_MOVE::BACKWARD) ||
            (iYCurrent == 0 && yMove == E_MOVE::BACKWARD))
        return false;

    iXTarget = iXCurrent;
    iYTarget = iYCurrent;

    if (xMove == E_MOVE::BACKWARD) --iXTarget;
    if (xMove == E_MOVE::FORWARD) ++iXTarget;
    if (yMove == E_MOVE::BACKWARD) --iYTarget;
    if (yMove == E_MOVE::FORWARD) ++iYTarget;

  // Verif superior limit
    iGridSize = m_map->grid()->size();
    if (iXTarget >= iGridSize || iYTarget >= iGridSize)
        return false;

    targetNode = m_map->grid()->get(iXTarget, iYTarget);

    // Verification edge exists
    // ------------------------
    if(m_map->graph()->edgeExists(m_player->currentNode(), targetNode) == false)
        return false;

    // Player move
    // ------------
    m_player->setCurrentNode(targetNode);
    return true;
}

/**
 * Ask the player to pick the item number iItem from the current node.
 * @param [in] iItem Number of the item
 * @return True if achieved
 */
bool CollectGame::playerPickItem(unsigned int iItem)
{
    Items pickableItems;
    m_items->getItemBatchOfHolder(m_player->currentNode(), pickableItems);

    if (iItem >= pickableItems.count())
        return false;

    pickableItems.item(iItem)->setHolder(m_player);

    return true;
}

/**
 * Retrieve the string to be displayed to print model's view
 * @param [out] sStringToPrint
 */
void CollectGame::getConsolePrint(std::string &sStringToPrint) const
{

    unsigned long iXCurrent, iYCurrent, iNodeCount;
    Items pickedItems, nodeItems;
    sStringToPrint.clear();

    //Map
    //---
    sStringToPrint += "MAP";
    sStringToPrint += "===";
    sStringToPrint += m_map->consolePrint();
    sStringToPrint += "\n";

    //Player
    //------
    iXCurrent = m_player->currentNode()->x();
    iYCurrent = m_player->currentNode()->y();

    sStringToPrint += "PLAYER";
    sStringToPrint += "======";
    m_items->getItemBatchOfHolder(m_player, pickedItems);
    sStringToPrint += "• Hold: " + pickedItems.consolePrint() + "\n";
    sStringToPrint += "• location: X=" + std::to_string(iXCurrent) + " , Y= " + std::to_string(iYCurrent) + " (marked @ in the map)\n";
    m_items->getItemBatchOfHolder(m_player->currentNode(), nodeItems);
    sStringToPrint += "• Pickable in that location: " + pickedItems.consolePrint() + "\n";

    //Nodes
    //-----
    sStringToPrint += "NODES";
    sStringToPrint += "=====";
    iNodeCount = m_map->graph()->nodeCount();
    for (unsigned long i = 0 ; i < iNodeCount ; ++i)
    {
        m_items->getItemBatchOfHolder(m_map->graph()->node(i), nodeItems);
        sStringToPrint += "• " +m_map->graph()->node(i)->consoleFullPrint() + ": " + nodeItems.consolePrint();
    }

}


