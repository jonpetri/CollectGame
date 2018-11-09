#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include "model/game/player.h"
#include "model/node/node.h"
#include <iostream>
#include <string>


BOOST_AUTO_TEST_SUITE( player_suite )



BOOST_AUTO_TEST_CASE(get_set)
{
    Player p;
    std::shared_ptr<Node> n1 = Node::create();
    std::shared_ptr<Node> n2 = Node::create();
    BOOST_CHECK(p.currentNode() == nullptr);
    BOOST_CHECK_EQUAL(n1->hostThePlayer(), false);

    p.setCurrentNode(n1);
    BOOST_CHECK_EQUAL(p.currentNode(),n1);
    BOOST_CHECK_EQUAL(n1->hostThePlayer(), true);

    p.setCurrentNode(n2);
    BOOST_CHECK_EQUAL(p.currentNode(),n2);
    BOOST_CHECK_EQUAL(n2->hostThePlayer(), true);
    BOOST_CHECK_EQUAL(n1->hostThePlayer(), false);
}

BOOST_AUTO_TEST_SUITE_END()
