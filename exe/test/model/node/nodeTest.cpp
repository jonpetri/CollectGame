#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE model
#include <boost/test/unit_test.hpp>


#include "model/node/node.h"
#include "mockup/nodesignaltester.h"

#include <iostream>
#include <string>
#include <boost/bind.hpp>

BOOST_AUTO_TEST_SUITE( node_suite )



BOOST_AUTO_TEST_CASE(constructor)
{

    //for (int i = 0 ; i < 99999 ; ++i)
    //{
        std::shared_ptr<Node> n = Node::create() ;

        BOOST_CHECK_EQUAL(n->graphIndex(),ULONG_MAX);
        BOOST_CHECK_EQUAL(n->x(),-1);
        BOOST_CHECK_EQUAL(n->y(),-1);
        BOOST_CHECK_EQUAL(n->exists(),false);
        BOOST_CHECK_EQUAL(n->isCandidate(),false);
        BOOST_CHECK_EQUAL(n->isAbsent(),true);
        BOOST_CHECK_EQUAL(n->consolePrintCharacter(), " ");
    //}

}
BOOST_AUTO_TEST_CASE(sets)
{
    std::shared_ptr<Node> n = Node::create() ;
    n->setX(5);
    n->setY(6);
    n->setGraphIndex(7);
    BOOST_CHECK_EQUAL(n->graphIndex(),7);
    BOOST_CHECK_EQUAL(n->x(),5);
    BOOST_CHECK_EQUAL(n->y(),6);
}

BOOST_AUTO_TEST_CASE(setIntoCandidateStateFirst_ThenExisting)
{
    std::shared_ptr<Node> n = Node::create() ;
    NodeSignalTester signalTester1, signalTester2;
    n->addToCandidateList.connect(      boost::bind( &NodeSignalTester::slotGetNode, &signalTester1, _1 ));
    n->setAdjacentsAsCandidate.connect( boost::bind( &NodeSignalTester::slotGetNode, &signalTester2, _1 ));

    BOOST_CHECK(signalTester1.node() == nullptr);
    BOOST_CHECK(signalTester2.node() == nullptr);


    n->setIntoCandidateState();

    BOOST_CHECK_EQUAL(n->exists(),false);
    BOOST_CHECK_EQUAL(n->isCandidate(),true);
    BOOST_CHECK_EQUAL(n->isAbsent(),false);
    BOOST_CHECK_EQUAL(n->consolePrintCharacter(), " ");
    BOOST_CHECK_EQUAL(signalTester1.node(), n);
    BOOST_CHECK(signalTester2.node() == nullptr);

    signalTester1.setNode(nullptr);
    n->setIntoExistingState();

    BOOST_CHECK_EQUAL(n->exists(),true);
    BOOST_CHECK_EQUAL(n->isCandidate(),false);
    BOOST_CHECK_EQUAL(n->isAbsent(),false);
    BOOST_CHECK_EQUAL(n->consolePrintCharacter(), "O");
    BOOST_CHECK(signalTester1.node() == nullptr);
    BOOST_CHECK_EQUAL(signalTester2.node(), n);

    // try to go back state
    signalTester2.setNode(nullptr);


    n->setIntoCandidateState();

    BOOST_CHECK_EQUAL(n->exists(),true);
    BOOST_CHECK_EQUAL(n->isCandidate(),false);
    BOOST_CHECK_EQUAL(n->isAbsent(),false);
    BOOST_CHECK_EQUAL(n->consolePrintCharacter(), "O");
    BOOST_CHECK(signalTester1.node() == nullptr);
    BOOST_CHECK(signalTester2.node() == nullptr);

}

BOOST_AUTO_TEST_CASE(setIntoExistingStateDirectly)
{
    std::shared_ptr<Node> n = Node::create() ;
    NodeSignalTester signalTester1, signalTester2;
    n->addToCandidateList.connect(      boost::bind( &NodeSignalTester::slotGetNode, &signalTester1, _1 ));
    n->setAdjacentsAsCandidate.connect( boost::bind( &NodeSignalTester::slotGetNode, &signalTester2, _1 ));

    BOOST_CHECK(signalTester1.node() == nullptr);
    BOOST_CHECK(signalTester2.node() == nullptr);

    n->setIntoExistingState();

    BOOST_CHECK_EQUAL(n->exists(),true);
    BOOST_CHECK_EQUAL(n->isCandidate(),false);
    BOOST_CHECK_EQUAL(n->isAbsent(),false);
    BOOST_CHECK_EQUAL(n->consolePrintCharacter(), "O");
    BOOST_CHECK(signalTester1.node() == nullptr);
    BOOST_CHECK_EQUAL(signalTester2.node(), n);


    // try to go back state
    signalTester2.setNode(nullptr);

    n->setIntoCandidateState();

    BOOST_CHECK_EQUAL(n->exists(),true);
    BOOST_CHECK_EQUAL(n->isCandidate(),false);
    BOOST_CHECK_EQUAL(n->isAbsent(),false);
    BOOST_CHECK_EQUAL(n->consolePrintCharacter(), "O");
    BOOST_CHECK(signalTester1.node() == nullptr);
    BOOST_CHECK(signalTester2.node() == nullptr);

    //set the player
    n->setHostThePlayer(true);
    BOOST_CHECK_EQUAL(n->consolePrintCharacter(), "@");
    n->setHostThePlayer(false);
    BOOST_CHECK_EQUAL(n->consolePrintCharacter(), "O");
}

BOOST_AUTO_TEST_SUITE_END()
