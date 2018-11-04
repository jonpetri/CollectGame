#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "consoleview.h"
#include "mockup/consolecommandbaseInheritance.h"

#include <iostream>
#include <string>
#include <boost/bind.hpp>

BOOST_AUTO_TEST_SUITE( consoleview_suite )

BOOST_AUTO_TEST_CASE(add_execute_command)
{
    std::shared_ptr<ConsoleView> v = ConsoleView::create();
    std::shared_ptr<ConsoleCommandBase> c = std::make_shared<ConsoleCommandBaseInheritance>();

    c->addCommandTerm("CMD");
    v->addCommand(c);

    BOOST_CHECK_EQUAL(c->description(),"");
    v->executeCommand("INEXIST");
    BOOST_CHECK_EQUAL(c->description(),"");
    v->executeCommand("cmd");
    BOOST_CHECK_EQUAL(c->description(),"OK");

    c->setDescription("");

    BOOST_CHECK_EQUAL(c->description(),"");
    v->executeCommand("cmd arg");
    BOOST_CHECK_EQUAL(c->description(),"OK");
}


BOOST_AUTO_TEST_SUITE_END()
