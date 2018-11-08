#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include "model/game/gameparameters.h"
#include <iostream>
#include <string>


BOOST_AUTO_TEST_SUITE( gameproperties_suite )



BOOST_AUTO_TEST_CASE(nodeCount)
{
    GameParameters p;
    p.setGridSize(10);
    p.setRatio_NodeCountVsGridSize(2);
    BOOST_CHECK_EQUAL(p.nodeCount(),20);
    p.setRatio_NodeCountVsGridSize(0.5);
    BOOST_CHECK_EQUAL(p.nodeCount(),5);

    p.setGridSize(5);
    p.setRatio_NodeCountVsGridSize(0.5);
    BOOST_CHECK_EQUAL(p.nodeCount(),2);
}
BOOST_AUTO_TEST_CASE(edgeTargetCount)
{
    GameParameters p;
    p.setGridSize(10);
    p.setRatio_EdgeCountVsGridSize(2);
    BOOST_CHECK_EQUAL(p.edgeTargetCount(),20);
    p.setRatio_EdgeCountVsGridSize(0.5);
    BOOST_CHECK_EQUAL(p.edgeTargetCount(),5);

    p.setGridSize(5);
    p.setRatio_EdgeCountVsGridSize(0.5);
    BOOST_CHECK_EQUAL(p.edgeTargetCount(),2);
}
BOOST_AUTO_TEST_CASE(itemCount)
{
    GameParameters p;
    p.setGridSize(10);
    p.setRatio_NodeCountVsGridSize(2);
    p.setRatio_ItemCountVsNodeCount(2);
    BOOST_CHECK_EQUAL(p.itemCount(),40);
    p.setRatio_ItemCountVsNodeCount(0.5);
    BOOST_CHECK_EQUAL(p.itemCount(),10);
}

BOOST_AUTO_TEST_SUITE_END()
