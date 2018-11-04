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
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryFirstArgument(""),false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryTotally(""),false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryFirstArgument("test"),false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryTotally("test"),false);
}

BOOST_AUTO_TEST_CASE(term_set)
{
    ConsoleCommandBaseInheritance c;
    c.addCommandTerm("");
    BOOST_CHECK_EQUAL(c.commandTermsString(),"");
    c.addCommandTerm("cmd1");
    BOOST_CHECK_EQUAL(c.commandTermsString(),"CMD1");
    c.addCommandTerm("CM2");
    BOOST_CHECK_EQUAL(c.commandTermsString(),"CMD1/CM2");
    c.addCommandTerm("c3");
    BOOST_CHECK_EQUAL(c.commandTermsString(),"CMD1/CM2/C3");
    c.addCommandTerm("");
    BOOST_CHECK_EQUAL(c.commandTermsString(),"CMD1/CM2/C3");
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
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryTotally("TE"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryTotally(""), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryTotally("TEST"), false);

    c.addCommandTerm("");
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryTotally("TE"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryTotally(""), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryTotally("TEST"), false);

    c.addCommandTerm("TEST");
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryTotally("TE"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryTotally(""), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryTotally("TEST"), true);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryTotally("TESTTROP"), false);

    c.addCommandTerm("TEST2");
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryTotally("TE"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryTotally(""), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryTotally("TEST"), true);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryTotally("TEST2"), true);
}

BOOST_AUTO_TEST_CASE(isMatchingUserEntryFirstArgument)
{
    ConsoleCommandBaseInheritance c;
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryFirstArgument("TE"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryFirstArgument(""), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryFirstArgument("TEST"), false);

    c.addCommandTerm("");
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryFirstArgument("TE"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryFirstArgument(""), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryFirstArgument("TEST"), false);

    c.addCommandTerm("TEST");
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryFirstArgument("TE"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryFirstArgument(""), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryFirstArgument("TEST"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryFirstArgument("TESTTROP"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryFirstArgument("TEST OK"), true);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryFirstArgument("INV TEST OK"), false);

    c.addCommandTerm("TEST2");
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryFirstArgument("TE"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryFirstArgument(""), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryFirstArgument("TESTTROP"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryFirstArgument("TEST"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryFirstArgument("TEST2"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryFirstArgument("TEST OK"), true);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryFirstArgument("TEST2 OK"), true);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryFirstArgument("INV TEST OK"), false);
    BOOST_CHECK_EQUAL(c.isMatchingUserEntryFirstArgument("INV TEST2 OK"), false);
}

BOOST_AUTO_TEST_SUITE_END()
