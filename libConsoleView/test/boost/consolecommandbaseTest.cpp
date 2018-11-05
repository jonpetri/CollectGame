#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE libConsoleView

#include "mockup/consolecommandbaseInheritance.h"

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <string>
#include <boost/bind.hpp>

BOOST_AUTO_TEST_SUITE( ConsoleCommandBase_suite )

/**
 * ConsoleCommandBase is an abstract class but has some features to be tested.
 * So the test is done through the mockup ConsoleCommandBaseInheritance, inheriting from ConsoleCommandBase
 */

BOOST_AUTO_TEST_CASE(constructor)
{
    ConsoleCommandBaseInheritance c;
    BOOST_CHECK_EQUAL(c.commandTermsString(),"");
    BOOST_CHECK_EQUAL(c.description(),"");
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry(""),false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("test"),false);
}

BOOST_AUTO_TEST_CASE(term_set)
{
    ConsoleCommandBaseInheritance c;
    c.addCommandTerm("");
    BOOST_CHECK_EQUAL(c.commandTermsString(),"");
    c.addCommandTerm("cmd1");
    BOOST_CHECK_EQUAL(c.commandTermsString(),"CMD1");
    c.addCommandTerm("CM2");
    BOOST_CHECK_EQUAL(c.commandTermsString(),"CMD1 / CM2");
    c.addCommandTerm("c3");
    BOOST_CHECK_EQUAL(c.commandTermsString(),"CMD1 / CM2 / C3");
    c.addCommandTerm("");
    BOOST_CHECK_EQUAL(c.commandTermsString(),"CMD1 / CM2 / C3");
}

BOOST_AUTO_TEST_CASE(parameterCountSet)
{
    ConsoleCommandBaseInheritance c;
    c.addCommandTerm("cmd1");
    c.addCommandTerm("CM2");

    c.setExpectedParameterCount(1);
    BOOST_CHECK_EQUAL(c.commandTermsString(),"CMD1 / CM2 <arg>");
    c.setExpectedParameterCount(2);
    BOOST_CHECK_EQUAL(c.commandTermsString(),"CMD1 / CM2 <arg> <arg>");

    c.setExpectedParameterCount(3);
    BOOST_CHECK_EQUAL(c.commandTermsString(),"CMD1 / CM2 <arg> <arg> <arg>");
}

BOOST_AUTO_TEST_CASE(description_set)
{
    ConsoleCommandBaseInheritance c;
    c.setDescription("");
    BOOST_CHECK_EQUAL(c.description(),"");
    c.setDescription("A description");
    BOOST_CHECK_EQUAL(c.description(),"A description");
    c.setDescription("");
    BOOST_CHECK_EQUAL(c.description(),"");
}






BOOST_AUTO_TEST_CASE(signal_modelModified)
{
    ConsoleCommandBaseInheritance c1, c2;
    c1.modelModified.connect( boost::bind( &ConsoleCommandBaseInheritance::execute, &c2 ));
    BOOST_CHECK_EQUAL(c2.description(),"");
    c1.modelModified();
    BOOST_CHECK_EQUAL(c2.description(),"OK");
}
BOOST_AUTO_TEST_CASE(signal_sendMessageToUser)
{
    ConsoleCommandBaseInheritance c1, c2;
    c1.sendMessageToUser.connect( boost::bind( &ConsoleCommandBaseInheritance::setDescription, &c2, _1 ));
    BOOST_CHECK_EQUAL(c2.description(),"");
    c1.sendMessageToUser("OK");
    BOOST_CHECK_EQUAL(c2.description(),"OK");
}
BOOST_AUTO_TEST_CASE(signal_displayAssociatedHelpToUser)
{
    ConsoleCommandBaseInheritance c1, c2;
    c1.displayAssociatedHelpToUser.connect( boost::bind( &ConsoleCommandBaseInheritance::execute, &c2 ));
    BOOST_CHECK_EQUAL(c2.description(),"");
    c1.displayAssociatedHelpToUser();
    BOOST_CHECK_EQUAL(c2.description(),"OK");
}
BOOST_AUTO_TEST_CASE(signal_quitAssociatedViews)
{
    ConsoleCommandBaseInheritance c1, c2;
    c1.quitAssociatedViews.connect( boost::bind( &ConsoleCommandBaseInheritance::execute, &c2 ));
    BOOST_CHECK_EQUAL(c2.description(),"");
    c1.quitAssociatedViews();
    BOOST_CHECK_EQUAL(c2.description(),"OK");
}

BOOST_AUTO_TEST_CASE(isMatchingUserEntryTotally)
{
    ConsoleCommandBaseInheritance c;
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TE"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry(""), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TEST"), false);

    c.addCommandTerm("");
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TE"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry(""), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TEST"), false);

    c.addCommandTerm("TEST");
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TE"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry(""), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TEST"), true);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TESTTROP"), false);

    c.addCommandTerm("TEST2");
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TE"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry(""), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TEST"), true);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TEST2"), true);
    BOOST_CHECK_EQUAL(c.commandsParameter(0), "");
}

BOOST_AUTO_TEST_CASE(isMatchingUserEntryFirstArgument_Parameters)
{
    ConsoleCommandBaseInheritance c;
    c.setExpectedParameterCount(1);

    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TE"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry(""), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TEST"), false);

    c.addCommandTerm("");
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TE"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry(""), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TEST"), false);

    c.addCommandTerm("TEST");
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TE"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry(""), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TEST"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TESTTROP"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TEST OK"), true);
    BOOST_CHECK_EQUAL(c.commandsParameter(0), "OK");
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("INV TEST OK"), false);
    BOOST_CHECK_EQUAL(c.commandsParameter(0), "");

    c.addCommandTerm("TEST 2");
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TE"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry(""), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TESTTROP"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TEST"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TEST 2"), true);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TEST OK"), true);
    BOOST_CHECK_EQUAL(c.commandsParameter(0), "OK");


    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("INV TEST OK"), false);
    BOOST_CHECK_EQUAL(c.commandsParameter(0), "");
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("INV TEST 2 OK"), false);

    c.setExpectedParameterCount(2);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("INV TEST 2 OK"), false);
    BOOST_CHECK_EQUAL(c.commandsParameter(0), "");
    BOOST_CHECK_EQUAL(c.isMatchingUserEntry("TEST 2 1 2"), true);
    BOOST_CHECK_EQUAL(c.commandsParameter(0), "1");
    BOOST_CHECK_EQUAL(c.commandsParameter(1), "2");
    BOOST_CHECK_EQUAL(c.commandsParameter(2), "");

}

BOOST_AUTO_TEST_CASE(clearCommandTermList)
{
    ConsoleCommandBaseInheritance c;

    BOOST_CHECK_EQUAL(c.commandTermsString(),"");
    c.clearCommandTermList();
    BOOST_CHECK_EQUAL(c.commandTermsString(),"");

    c.addCommandTerm("cmd1");
    c.addCommandTerm("CM2");
    BOOST_CHECK_EQUAL(c.commandTermsString(),"CMD1 / CM2");

    c.clearCommandTermList();
    BOOST_CHECK_EQUAL(c.commandTermsString(),"");
}
BOOST_AUTO_TEST_SUITE_END()
