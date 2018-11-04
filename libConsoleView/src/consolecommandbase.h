/*----------------------------------------------------------------*/
/*  PROJECT:    Console View                                  */
/*----------------------------------------------------------------*/
/**
 * CLASS: ConsoleCommandBase
 * ConsoleCommandBase is an abstract class.
 * Once inherited, the child class contains a code corresponding to a specific action, in the .execute() method.
 * It also contains the argument/commands to be entered bay the user to call the command.
 * Its different signals are to be connected to a view.
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
    std::string commandsParameter();
    // Setters:

    // Signals
    boost::signals2::signal<void ()> modelModified;
    boost::signals2::signal<void (const std::string &)> sendMessageToUser;
    boost::signals2::signal<void ()> displayAssociatedHelpToUser;
    boost::signals2::signal<void ()> quitAssociatedViews;

    // Methods:
    virtual void execute() = 0;


    void setDescription(const std::string &sDescription);
    void addCommandTerm(std::string sTerm);

    bool isMatchingUserEntryTotally(const std::string &sUserEntry);
    bool isMatchingUserEntryFirstArgument(const std::string &sUserEntry);

protected:

private:
    // Methods:

    // Members:
    std::string m_sDescription;                 ///< Command's purpose description text, displayed in the menu
    std::vector<std::string> m_commandTerms;    ///< list of strings usable by the user to call the command
    std::string m_sUserEntryMemo;               ///< Last User's entry memo, in case it contains parameters
    std::string m_sUserEntryParameter;          ///< Last User's entry's parameter, if any


};

#endif // CONSOLECOMMANDBASE_H
