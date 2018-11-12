#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include "control/parametersModification/setgridsizecmd.h"
#include "model/game/collectgame.h"
#include "model/game/gameparameters.h"


#include <string>
#include <memory>


BOOST_AUTO_TEST_SUITE(setgridsizecmd)

/**
 * attention: the features of the base class ConsoleCommand are not re-tested.
 */

/*
BOOST_AUTO_TEST_CASE(entry_ok)
{
    SetGridSizeCmd c;
    std::shared_ptr<CollectGame> g = std::make_shared<CollectGame>();
    std::string sEntry;
    c.setModel(g);

    sEntry = "GRID WIDTH 6";
    BOOST_CHECK(c.setUserEntry(sEntry));
    c.execute();
    BOOST_CHECK_EQUAL(g->gameParameters()->gridSideSize(), 6);

    sEntry = "GRID WIDTH 15";
    BOOST_CHECK(c.setUserEntry(sEntry));
    c.execute();
    BOOST_CHECK_EQUAL(g->gameParameters()->gridSideSize(), 15);
}

BOOST_AUTO_TEST_CASE(string_entry)
{
    SetGridSizeCmd c;
    std::shared_ptr<CollectGame> g = std::make_shared<CollectGame>();
    c.setModel(g);

    BOOST_CHECK(c.setUserEntry("GRID WIDTH 15"));
    c.execute();
    BOOST_CHECK_EQUAL(g->gameParameters()->gridSideSize(), 15);

    BOOST_CHECK(c.setUserEntry("GRID WIDTH K"));
    c.execute();
    BOOST_CHECK_EQUAL(g->gameParameters()->gridSideSize(), 15);

}
BOOST_AUTO_TEST_CASE(negative_entry)
{
    SetGridSizeCmd c;
    std::shared_ptr<CollectGame> g = std::make_shared<CollectGame>();
    c.setModel(g);

    BOOST_CHECK(c.setUserEntry("GRID WIDTH 15"));
    c.execute();
    BOOST_CHECK_EQUAL(g->gameParameters()->gridSideSize(), 15);

    BOOST_CHECK(c.setUserEntry("GRID WIDTH -1"));
    c.execute();
    BOOST_CHECK_EQUAL(g->gameParameters()->gridSideSize(), 15);
}

*/

BOOST_AUTO_TEST_SUITE_END()

