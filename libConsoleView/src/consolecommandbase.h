/*----------------------------------------------------------------*/
/*  PROJECT:    Console View                                  */
/*----------------------------------------------------------------*/
/**
 * CLASS: ConsoleCommandBase
 * ConsoleCommandBase is an abstract class.
 * It represent an action proposed to the user in a console program.
 *
 * Action implementation
 * ---------------------
 * Inherit the ConsoleCommand<Model> class, with model's head class as template parameter,
 * and implement the action in the .execute() method.
 * The command terms, description and parameter count variables has to be filled as well.
 * Then the created class has to be linked to the an object ConsoleView, thanks to the method ConsoleView::addCommand().
 *
 * ConsoleCommandBase::modelModified() signal
 * -------------------------------------------
 * This signal work only if a DisplayModelView Command is implemented,
 * and linked to ConsoleView using the method .setDisplayModelViewCommand().
 *
 * Command term/argument
 * ---------------------
 * ConsoleCommandBase manage the user's entry validity.
 * According the command term and the expected parameter count (e.g. CMD <arg1> <arg2>),
 * the class is able to indicate if an entry correspond to itself.
 *
 */
#ifndef CONSOLECOMMANDBASE_H
#define CONSOLECOMMANDBASE_H

// Includes:
#include <string>
#include <vector>
#include <boost/signals2.hpp>


class ConsoleCommandBase
{
public:
    ConsoleCommandBase();

    virtual ~ConsoleCommandBase();

    // Getters:
    std::string commandTermsString();
    std::string description();
    std::string commandsParameter(int iIndex);

    // Setters:
    void setDescription(const std::string &sDescription);
    void setExpectedParameterCount(int iExpectedParameterCount);

    // Signals
    boost::signals2::signal<void ()> modelModified;
    boost::signals2::signal<void (const std::string &)> sendMessageToUser;
    boost::signals2::signal<void ()> displayAssociatedHelpToUser;
    boost::signals2::signal<void ()> quitAssociatedViews;

    // Methods:
    virtual void execute() = 0;
    void addCommandTerm(std::string sTerm);
    void clearCommandTermList();
    bool isMatchingUserEntry(const std::string &sUserEntry);

protected:

private:
    // Methods:
    bool isMatchingUserEntryWithoutParam(std::string sUserEntry);
    bool isMatchingUserEntryWithParam(const std::string &sUserEntry);

    // Members:
    std::string m_sDescription;                     ///< Command's purpose description text, displayed in the menu
    std::vector<std::string> m_commandTerms;        ///< list of strings usable by the user to call the command
    int m_iExpectedParameterCount;                  ///< The number of parameter the command should receive, in addition to the first term
    std::vector<std::string> m_parameters;          ///< Last User's entry's parameters, if any
};

#endif // CONSOLECOMMANDBASE_H
