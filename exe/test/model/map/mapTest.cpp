#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "model/map/map.h"
#include "model/map/array2d.h"
#include "model/map/nodegraph.h"

#include "model/game/gameparameters.h"
#include "model/node/node.h"
#include <iostream>
#include <string>



BOOST_AUTO_TEST_SUITE( map_suite )


int existingNodeCount(const std::shared_ptr<NodeGrid> & g)
{
    int iNodeCount(0);
    int iGridSize = static_cast<int>(g->size());
    for (int x = 0 ; x < iGridSize ; ++x)
    {
        for (int y = 0 ; y < iGridSize ; ++y)
        {
            if (g->get(x, y)->exists() == true)
                ++iNodeCount;
        }
    }
    return iNodeCount;
}

BOOST_AUTO_TEST_CASE(createNewMapDefault)
{

    std::shared_ptr<Map> m = Map::createObject();
    std::shared_ptr<GameParameters> p = std::make_shared<GameParameters>();

    m->createNewMap(p);

    BOOST_CHECK_EQUAL(existingNodeCount(m->grid()), p->nodeCount());
    BOOST_CHECK_EQUAL(m->graph()->nodeCount(), p->nodeCount());

    BOOST_CHECK_EQUAL(m->grid()->size(), p->gridSideSize());
    // BOOST_CHECK(m->graph()->edgeCount() >= p->edgeTargetCount());  --> this not verifiable, as the graph can be constructed with less edge than the target
    BOOST_CHECK(m->graph()->isConnected());

    std::cout << "edge count= " << m->graph()->edgeCount() << std::endl;
    m->graph()->printGraph();
    std::cout << m->consolePrint();

}

BOOST_AUTO_TEST_CASE(createNewMap1)
{

    std::shared_ptr<Map> m = Map::createObject();
    std::shared_ptr<GameParameters> p = std::make_shared<GameParameters>();
    p->setGridSideSize(5);

    m->createNewMap(p);

    BOOST_CHECK_EQUAL(existingNodeCount(m->grid()), p->nodeCount());
    BOOST_CHECK_EQUAL(m->graph()->nodeCount(), p->nodeCount());

    BOOST_CHECK_EQUAL(m->grid()->size(), p->gridSideSize());
    BOOST_CHECK(m->graph()->isConnected());

//    std::cout << "edge count= " << m->graph()->edgeCount() << std::endl;
//    m->graph()->printGraph();
//    std::cout << m->consolePrint();

}
//BOOST_AUTO_TEST_CASE(createNewMap2)
//{

//    std::shared_ptr<Map> m = Map::createObject();
//    std::shared_ptr<GameParameters> p = std::make_shared<GameParameters>();
//    p->setGridSideSize(20);

//    m->createNewMap(p);

//    BOOST_CHECK_EQUAL(existingNodeCount(m->grid()), p->nodeCount());
//    BOOST_CHECK_EQUAL(m->graph()->nodeCount(), p->nodeCount());

//    BOOST_CHECK_EQUAL(m->grid()->size(), p->gridSideSize());
//    BOOST_CHECK(m->graph()->isConnected());

//    std::cout << "edge count= " << m->graph()->edgeCount() << std::endl;
//    m->graph()->printGraph();
//    std::cout << m->consolePrint();

//}




BOOST_AUTO_TEST_SUITE_END()
