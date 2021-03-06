#include "consolecommandbase.h"

#include <algorithm>
#include <sstream>      // std::istringstream

//-----------------------------------------------------------------------------------------------------------------------
// ConsoleCommandBase :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
ConsoleCommandBase::ConsoleCommandBase()
    : modelModified()
    , sendMessageToUser()
    , displayAssociatedHelpToUser()
    , quitAssociatedViews()
    , m_sDescription("")
    , m_commandTerms(0)
    , m_iExpectedParameterCount(0)
    , m_parameters(0)
{

}

ConsoleCommandBase::~ConsoleCommandBase()
{

}



//-----------------------------------------------------------------------------------------------------------------------
// ConsoleCommandBase :: Getters
//-----------------------------------------------------------------------------------------------------------------------
/**
 * Retrieve the list of the command's terms, separated by a '-', plus a <arg> for each needed argument
 * @return The list of the command's terms.
 */
std::string ConsoleCommandBase::commandTermsString() const
{
    std::string sRet("");

    // Terms chaining with " / "
    for (auto const & sCommandTerm : m_commandTerms)
    {
        sRet += (sCommandTerm + " / ");
    }

    // remove of the last "- "
    if (sRet.size() != 0)
    {
        sRet.pop_back();
        sRet.pop_back();
        sRet.pop_back();
    }

    // Add of an <arg> for each parameter
    if (m_iExpectedParameterCount != 0)
    {
        for (unsigned int i = 0 ; i < m_iExpectedParameterCount ; ++i)
            sRet += " <arg>";
    }


    return sRet;
}

/**
 * Retrieve command's description
 * @return Command's description
 */
std::string ConsoleCommandBase::description() const
{
    return m_sDescription;
}

/**
 * Retrieve the second part of the command line, if any.
 * @param iIndex Index from 0
 * @return The parameter par of the command line.
 */
std::string ConsoleCommandBase::commandsParameter(unsigned int iIndex) const
{
    if (iIndex < m_parameters.size())
        return m_parameters[iIndex];
    else
        return "";
}

//-----------------------------------------------------------------------------------------------------------------------
// ConsoleCommandBase :: Setters
//-----------------------------------------------------------------------------------------------------------------------

/**
 * Define command's description.
 * The description will be displayed in ConsoleView menu.
 * @param [in] sDescription
 */
void ConsoleCommandBase::setDescription(const std::string &sDescription)
{
    m_sDescription = sDescription;
}

void ConsoleCommandBase::setExpectedParameterCount(unsigned int iExpectedParameterCount)
{
    m_iExpectedParameterCount = iExpectedParameterCount;
}

//-----------------------------------------------------------------------------------------------------------------------
// ConsoleCommandBase :: Methods
//-----------------------------------------------------------------------------------------------------------------------

/**
 * Add a term (or word) as possible command to call this command.
 * Then the command can be recognized testing the match with user typed command line.
 * The term will be displayed in ConsoleView menu.
 * @param [in] sTerm command / term / word to be added
 */
void ConsoleCommandBase::addCommandTerm(std::string sTerm)
{
    if (sTerm.size() != 0)
    {
        transform(sTerm.begin(), sTerm.end(),sTerm.begin(), ::toupper);
        m_commandTerms.push_back(sTerm);
    }
}
/**
 * Erase command term list
 */
void ConsoleCommandBase::clearCommandTermList()
{
    this->m_commandTerms.clear();
}

/**
 * Test if users input / entry match with this command, and save it.
 * @param [in] sUserEntry Entry to be tested.
 * @return True if matches
 */
bool ConsoleCommandBase::setUserEntry(const std::string &sUserEntry)
{
    if (m_iExpectedParameterCount == 0)
    {
        return this->isMatchingUserEntryWithoutParam(sUserEntry);
    }
    else
    {
        return this->isMatchingUserEntryWithParam(sUserEntry);
    }
}

/**
 * Check if the user entry is an Unsigned Int
 * @param [in] iPara Number of para to check
 * @param [out] iRet Parameter in Unsigned Int if success
 * @return True if success
 */
bool ConsoleCommandBase::checkParameterIsUnsignedInt(unsigned int iParaIndex, unsigned int & uiValuePara) const
{
    int iValuePara;

    try {
       iValuePara = std::stoi(commandsParameter(iParaIndex));  // throw error is the entry is a string, or above integer limit
    }catch(...){
       this->sendMessageToUser("Incorrect entry, must be a number.\n");
       return false;
    }

    if (iValuePara < 0)
    {
        this->sendMessageToUser("Incorrect entry, must be a positive number.\n");
        return false;
    }

    uiValuePara = static_cast<unsigned int>(iValuePara); // safe cast as iValuePara > 0

    return true;
}

/**
 * Check if the user entry is a positive float
 * @param [in] iPara Number of para to check
 * @param [out] iRet Parameter in float if success
 * @return True if success
 */
bool ConsoleCommandBase::checkParameterIsPositiveFloat(unsigned int iParaIndex, float & fValuePara) const
{

    try {
       fValuePara = std::stof(commandsParameter(iParaIndex));  // throw error is the entry is a string, or above float limit
    }catch(...){
       this->sendMessageToUser("Incorrect entry, must be a number.\n");
       return false;
    }

    if (fValuePara < 0)
    {
        this->sendMessageToUser("Incorrect entry, must be a positive number.\n");
        return false;
    }

    return true;
}

/**
 * (private)
 * Test if users input / entry entirely match with this command.
 * @param [in] sUserEntry Entry to be tested.
 * @return True if matches
 */
bool ConsoleCommandBase::isMatchingUserEntryWithoutParam(std::string sUserEntry)
{
    transform(sUserEntry.begin(), sUserEntry.end(),sUserEntry.begin(), ::toupper);
    for (auto const & sCommandTerm : m_commandTerms)
    {
        if (sCommandTerm == sUserEntry)
        {
            m_parameters.clear();
            return true;
        }
    }

    m_parameters.clear();
    return false;
}

/**
 * (private)
 * Test if users input / entry's first argument match with this command.
 * @param [in] sUserEntry Entry to be tested.
 * @return True if matches
 */
bool ConsoleCommandBase::isMatchingUserEntryWithParam(const std::string &sUserEntry)
{
    std::string sCommandTermPlusSpace;
    std::string sUserEntryUpperCase(sUserEntry);
    std::string sUserEntryParameters;

    transform(sUserEntryUpperCase.begin(), sUserEntryUpperCase.end(),sUserEntryUpperCase.begin(), ::toupper);

    for (auto const & sCommandTerm : m_commandTerms)
    {
        // Check if the cmd term matches
        sCommandTermPlusSpace = sCommandTerm + " "; // in order to check if the cmd term is separated from the parameters with a space

        if ( sUserEntryUpperCase.find(sCommandTermPlusSpace) == 0
             &&
             sUserEntry.length() > sCommandTerm.length() + 1
            )
        { // then the cmd term matches:
            sUserEntryParameters = sUserEntry.substr(sCommandTerm.length()+1);

            // check if the parameter count matches

            // tokenize
            std::istringstream iss(sUserEntryParameters);
            m_parameters.clear();
            m_parameters.assign(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

            if (m_parameters.size() == m_iExpectedParameterCount)
                return true;
            else
                 m_parameters.clear();
        }
        m_parameters.clear();
    }

    return false;
}





