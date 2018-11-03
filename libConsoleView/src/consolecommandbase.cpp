#include "consolecommandbase.h"

#include <algorithm>

//-----------------------------------------------------------------------------------------------------------------------
// ConsoleCommandBase :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
ConsoleCommandBase::ConsoleCommandBase()
    : m_sDescription("")
    , m_commandTerms(0)
    , m_sUserEntryMemo("")
{

}





//-----------------------------------------------------------------------------------------------------------------------
// ConsoleCommandBase :: Getters
//-----------------------------------------------------------------------------------------------------------------------
/**
 * Retrieve the list of the command's terms, separated by a '-'
 * @return The list of the command's terms, separated by a '-'
 */
std::string ConsoleCommandBase::commandTermsString()
{
    std::string sRet;

    for (auto const & sCommandTerm : m_commandTerms)
    {
        sRet += (sCommandTerm + "-");
    }
    // remove of the last "-"
    sRet.pop_back();
    return sRet;
}

/**
 * Retrieve command's description
 * @return Command's description
 */
std::string ConsoleCommandBase::description()
{
    return m_sDescription;
}

//-----------------------------------------------------------------------------------------------------------------------
// ConsoleCommandBase :: Setters
//-----------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
// ConsoleCommandBase :: Methods
//-----------------------------------------------------------------------------------------------------------------------

/**
 * Define command's description.
 * The description will be displayed in ConsoleView menu.
 * @param sDescription
 */
void ConsoleCommandBase::setDescription(const std::string &sDescription)
{
    m_sDescription = sDescription;
}

/**
 * Add a term (or word) as possible command to call this command.
 * Then the command can be recognized testing the match with user typed command line.
 * The term will be displayed in ConsoleView menu.
 * @param sTerm command / term / word to be added
 */
void ConsoleCommandBase::addCommandTerm(std::string sTerm)
{
    transform(sTerm.begin(), sTerm.end(),sTerm.begin(), ::toupper);
    m_commandTerms.push_back(sTerm);
}

/**
 * Test if users input / entry match with this command.
 * The user entry has to be up-cased before.
 * @param sUserEntry Entry to be tested.
 * @return True if matches
 */
bool ConsoleCommandBase::isMatchingUserEntryTotally(const std::string &sUserEntry)
{
    for (auto const & sCommandTerm : m_commandTerms)
    {
        if (sCommandTerm == sUserEntry)
        {
            m_sUserEntryMemo = sUserEntry;
            return true;
        }
    }
    return false;
}

/**
 * Test if users input / entry's first argument match with this command.
 * The user entry has to be up-cased before.
 * @param sUserEntry Entry to be tested.
 * @return True if matches
 */
bool ConsoleCommandBase::isMatchingUserEntryFirstArgument(const std::string &sUserEntry)
{
    std::string sCommandTermPlusSpace;
    for (auto const & sCommandTerm : m_commandTerms)
    {
        sCommandTermPlusSpace = sCommandTerm + " "; // in order to check if the argument is separated with a space
        if ( sUserEntry.find(sCommandTerm) == 0)
        {
            m_sUserEntryMemo = sUserEntry;
            return true;
        }
    }
    return false;
}


