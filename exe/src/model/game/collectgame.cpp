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
    : m_gameParameters (std::make_shared<GameParameters>())
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
    return m_gameParameters;
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
    unsigned long lCreatedNodeCount(0);
    unsigned long lNode(0);
    unsigned int iItemCount(0);

    // Map creation
    // ------------
    this->m_map->createNewMap(m_gameParameters);

    // Items creation
    // --------------
    this->m_items->ceateRandomItems(m_gameParameters);


    // Items random spread in the map
    // ------------------------------
    lCreatedNodeCount = this->m_map->graph()->nodeCount();
    iItemCount = this->m_items->count();
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<unsigned long> nodeRandomDistribution(0, lCreatedNodeCount - 1);
    for (unsigned int i = 0 ; i < iItemCount ; ++i)
    {
        lNode = nodeRandomDistribution(gen);
        m_items->item(i)->setHolder(m_map->graph()->node(lNode));
    }

    // Player random positioning  in the map
    // ------------------------------------
    lNode = nodeRandomDistribution(gen);
    this->m_player->setCurrentNode(m_map->graph()->node(lNode));
    this->m_player->setStartNode(m_map->graph()->node(lNode));

}

/**
 * Move the player according xMove and yMove direction, if possible.
 * @param [in] xMove Description of th move along the X axis
 * @param [in] yMove Description of th move along the Y axis
 * @return true if displacement is possible and achieved
 */
bool CollectGame::movePlayer(E_MOVE xMove, E_MOVE yMove)
{
    unsigned int iXCurrent, iYCurrent, iXTarget, iYTarget, iGridSize ;
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
 * Verify if teh item is within the player's weight / item count limits.
 * @param [in] iItem Number of the item (from 1)
 * @return True if achieved
 */
bool CollectGame::playerPickItem(unsigned int iItem)
{
    Items pickableItems, pickedItems;
    if (iItem < 1)
        return false;

    --iItem;

    m_items->getItemBatchOfHolder(m_player->currentNode(), pickableItems);

    if (iItem >= pickableItems.count())
        return false;

    // Verify if the item is within the player's weight / item count limits.
    m_items->getItemBatchOfHolder(m_player, pickedItems);

    if (m_gameParameters->playerItemCountLimit() < pickedItems.count() + 1)
        return false;
    if (m_gameParameters->playerWeightLimit() < pickedItems.weight() + pickableItems.item(iItem)->weight())
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

    unsigned long lXCurrent, lYCurrent, lNodeCount;
    Items pickedItems, nodeItems;
    sStringToPrint.clear();

    //Map
    //---
    sStringToPrint += "MAP\n";
    sStringToPrint += "===\n";
    sStringToPrint += "  -> Nodes (O) are in a X;Y grid. The player is at the '@' node.\n";
    sStringToPrint += m_map->consolePrint();
    sStringToPrint += "\n";

    //Player
    //------
    lXCurrent = m_player->currentNode()->x();
    lYCurrent = m_player->currentNode()->y();

    sStringToPrint += "PLAYER\n";
    sStringToPrint += "======\n";
    sStringToPrint += "      -> The player is marked @ in the map.\n";
    sStringToPrint += "- He can hold up to a weight of " +std::to_string( m_gameParameters->playerWeightLimit())
                            + ", within " + std::to_string(m_gameParameters->playerItemCountLimit()) + " items.\n";

    m_items->getItemBatchOfHolder(m_player, pickedItems);
    sStringToPrint += "- Currently hold a total value of " + std::to_string(pickedItems.value())
                        + " and a total weight of " + std::to_string(pickedItems.weight())
                        + ", within " + pickedItems.consolePrint();

    sStringToPrint += "- Player's location (@): X=" + std::to_string(lXCurrent+1) + " , Y= " + std::to_string(lYCurrent+1) + "\n";
    m_items->getItemBatchOfHolder(m_player->currentNode(), nodeItems);
    sStringToPrint += "- Pickable in that location: " + nodeItems.consolePrint() + "\n";

    //Nodes/Items
    //-----
    sStringToPrint += "ITEMS\n";
    sStringToPrint += "=====\n";
    sStringToPrint += "      -> The nodes are identified thanks to then coordinates: [X ; Y])\n";
    sStringToPrint += "      -> Only item holding nodes are listed here.\n\n";
    lNodeCount = m_map->graph()->nodeCount();
    for (unsigned long l = 0 ; l < lNodeCount ; ++l)
    {
        m_items->getItemBatchOfHolder(m_map->graph()->node(l), nodeItems);
        if (nodeItems.count() > 0)
            sStringToPrint += "o " +m_map->graph()->node(l)->consoleFullPrint() + " contains " + nodeItems.consolePrint() + "\n";
    }

}

