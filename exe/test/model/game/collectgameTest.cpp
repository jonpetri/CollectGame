#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include "model/game/collectgame.h"
#include "model/game/gameparameters.h"
#include "model/game/player.h"
#include "model/node/node.h"
#include "model/item/items.h"

#include <iostream>
#include <string>


BOOST_AUTO_TEST_SUITE( player_suite )



BOOST_AUTO_TEST_CASE(move_limits)
{
    CollectGame g;
    std::string sPrint;
    BOOST_CHECK(g.gameParameters()->setGridSideSize(4));
    g.createNewGame();
    g.getConsolePrint(sPrint);
    std::cout << sPrint;

    int bMoveImpossibleCount(0);
    for (unsigned int i = 0 ; i < g.gameParameters()->gridSideSize() ; ++i)
    {
        if (g.movePlayer(E_MOVE::FORWARD, E_MOVE::HOLD_ON) == false )
            ++bMoveImpossibleCount;
    }

    BOOST_CHECK(bMoveImpossibleCount > 0);
}

BOOST_AUTO_TEST_CASE(move_and_pick_possible)
{
    CollectGame g;
    std::string sPrint;
    BOOST_CHECK(g.gameParameters()->setGridSideSize(4));
    BOOST_CHECK(g.gameParameters()->setRatio_NodeCountVsGridSpotCount(1)); //make there are nodes everywhere
    BOOST_CHECK(g.gameParameters()->setRatio_EdgeCountVsGridSpotCount(10)); //make there are edges everywhere
    BOOST_CHECK(g.gameParameters()->setRatio_ItemCountVsNodeCount(50));  //make there are items everywhere
    BOOST_CHECK(g.gameParameters()->setPlayerItemCountLimit(3));
    BOOST_CHECK(g.gameParameters()->setPlayerWeightLimit(100));  // big enough

    g.createNewGame();
//    g.getConsolePrint(sPrint);
//    std::cout << sPrint;

    BOOST_CHECK_EQUAL(g.playerPickItem(0), false);

    for (unsigned int i = 1 ; i <= g.gameParameters()->playerItemCountLimit() ; ++i)
        BOOST_CHECK(g.playerPickItem(1));

    BOOST_CHECK_EQUAL(g.playerPickItem(1), false);

    // number of item picked
    Items pickedItems;
    g.items()->getItemBatchOfHolder(g.player(), pickedItems);
     BOOST_CHECK_EQUAL(pickedItems.count(), g.gameParameters()->playerItemCountLimit());

    // move
    if (g.player()->currentNode()->x() != 0)
        BOOST_CHECK(g.movePlayer(E_MOVE::BACKWARD, E_MOVE::HOLD_ON) == true );

    else
         BOOST_CHECK(g.movePlayer(E_MOVE::FORWARD, E_MOVE::HOLD_ON) == true );

}


BOOST_AUTO_TEST_CASE(pick_not_possible)
{
    CollectGame g;
    std::string sPrint;
    BOOST_CHECK(g.gameParameters()->setGridSideSize(4));
    BOOST_CHECK(g.gameParameters()->setRatio_NodeCountVsGridSpotCount(1)); //make there are nodes everywhere
    BOOST_CHECK(g.gameParameters()->setRatio_EdgeCountVsGridSpotCount(10)); //make there are edges everywhere
    BOOST_CHECK(g.gameParameters()->setRatio_ItemCountVsNodeCount(0.0000001f));  //make there are no item

    g.createNewGame();

    BOOST_CHECK_EQUAL(g.playerPickItem(1), false);

}

BOOST_AUTO_TEST_SUITE_END()
