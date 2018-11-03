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

class ConsoleCommandBase
{
public:
    ConsoleCommandBase();

    virtual ~ConsoleCommandBase() = 0;

    // Getters:

    // Setters:

    // Methods:
    virtual bool execute() = 0;


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
