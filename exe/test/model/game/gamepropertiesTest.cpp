#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include "model/game/gameparameters.h"
#include <iostream>
#include <string>


BOOST_AUTO_TEST_SUITE( gameproperties_suite )



BOOST_AUTO_TEST_CASE(nodeCount)
{
    GameParameters p;
    BOOST_CHECK(p.setGridSideSize(10));
    BOOST_CHECK(p.setRatio_NodeCountVsGridSpotCount(0.5));
    BOOST_CHECK_EQUAL(p.nodeCount(),50);
    BOOST_CHECK(p.setRatio_NodeCountVsGridSpotCount(1));
    BOOST_CHECK_EQUAL(p.nodeCount(),100);

    BOOST_CHECK(p.setGridSideSize(5));
    BOOST_CHECK(p.setRatio_NodeCountVsGridSpotCount(0.5));
    BOOST_CHECK_EQUAL(p.nodeCount(),13);

    BOOST_CHECK(p.setGridSideSize(150) == false);
    BOOST_CHECK(p.setRatio_NodeCountVsGridSpotCount(2) == false);
    BOOST_CHECK(p.setRatio_NodeCountVsGridSpotCount(0) == false);
    BOOST_CHECK_EQUAL(p.nodeCount(),13);
}
BOOST_AUTO_TEST_CASE(edgeTargetCount)
{
    GameParameters p;
    BOOST_CHECK(p.setGridSideSize(10));
    BOOST_CHECK(p.setRatio_EdgeCountVsGridSpotCount(2));
    BOOST_CHECK_EQUAL(p.edgeTargetCount(),200);
    BOOST_CHECK(p.setRatio_EdgeCountVsGridSpotCount(0.5));
    BOOST_CHECK_EQUAL(p.edgeTargetCount(),50);

    BOOST_CHECK(p.setGridSideSize(5));
    BOOST_CHECK(p.setRatio_EdgeCountVsGridSpotCount(0.5));
    BOOST_CHECK_EQUAL(p.edgeTargetCount(),13);

    BOOST_CHECK(p.setRatio_EdgeCountVsGridSpotCount(0) == false);
    BOOST_CHECK_EQUAL(p.edgeTargetCount(),13);
}
BOOST_AUTO_TEST_CASE(itemCount)
{
    GameParameters p;
    p.setGridSideSize(10);
    p.setRatio_NodeCountVsGridSpotCount(2);
    BOOST_CHECK(p.setRatio_ItemCountVsNodeCount(2));
    BOOST_CHECK_EQUAL(p.itemCount(),100);

    BOOST_CHECK(p.setRatio_ItemCountVsNodeCount(0.5));
    BOOST_CHECK_EQUAL(p.itemCount(),25);

    BOOST_CHECK(p.setRatio_ItemCountVsNodeCount(0) == false);
    BOOST_CHECK_EQUAL(p.itemCount(),25);
}

BOOST_AUTO_TEST_SUITE_END()
