#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include "model/item/item.h"

#include "model/game/gameparameters.h"
#include "model/game/player.h"
#include "model/node/node.h"
#include <iostream>
#include <string>


BOOST_AUTO_TEST_SUITE( item_suite )



BOOST_AUTO_TEST_CASE(weight_value)
{
    Item i;
    std::shared_ptr<GameParameters> p = std::make_shared<GameParameters>();
    p->setItemMaxWeight(100);
    p->setItemMaxValue(5);
    BOOST_CHECK_EQUAL(i.weight(), 0);
    BOOST_CHECK_EQUAL(i.value(), 0);

    i.setRandomWeightAndValue(p);
    //BOOST_CHECK(i.weight() >= 0);  weigh and value are _unsigned
    //BOOST_CHECK(i.value() >= 0);
    BOOST_CHECK(i.value() <= 5);
    BOOST_CHECK(i.value() <= 100);
}
BOOST_AUTO_TEST_CASE(setHoder)
{
    Item i;
    std::shared_ptr<Node> n1 = Node::create();
    std::shared_ptr<Node> n2 = Node::create();
    BOOST_CHECK(i.holder() == nullptr);

    i.setHolder(n1);
    BOOST_CHECK_EQUAL(i.holder(), n1);

    i.setHolder(n2);
    BOOST_CHECK_EQUAL(i.holder(), n2);
}
BOOST_AUTO_TEST_SUITE_END()
