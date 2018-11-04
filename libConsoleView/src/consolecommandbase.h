/*----------------------------------------------------------------*/
/*  PROJECT:    Console View                                  */
/*----------------------------------------------------------------*/
/**
 * CLASS: ConsoleCommandBase
 *
 */
#ifndef CONSOLECOMMANDBASE_H
#define CONSOLECOMMANDBASE_H

// Includes:
#include <string>
#include <vector>
#include <memory>
#include <boost/signals2.hpp>

// boost::signals2 typedefs
//typedef boost::signals2::signal<void(double)>   registration_manager;
//typedef registration_manager::slot_type         registration_request;

class ConsoleCommandBase
{
public:
    ConsoleCommandBase();

    virtual ~ConsoleCommandBase();

    // Getters:
    std::string commandTermsString();
    std::string description();

    // Setters:

    // Signals
    boost::signals2::signal<void ()> modelModified;
    boost::signals2::signal<void (std::string)> sendMessageToUser;

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


};

#endif // CONSOLECOMMANDBASE_H
