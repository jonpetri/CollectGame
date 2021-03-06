#include "consoleview.h"

#include <iostream>
#include <limits>
#include <boost/bind.hpp>

#include "commanddisplaymenudefault.h"
#include "commandquitdefault.h"
//#include "consolecommandbase.h"

//-----------------------------------------------------------------------------------------------------------------------
// ConsoleView :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
ConsoleView::ConsoleView()
    : m_commands(0)
    , m_commandDisplayModelView {nullptr}
    , m_commandDisplayMenu {nullptr}
    , m_commandQuit {nullptr}
    , m_sMenuDescrition("")
    , m_bQuit(false)
{
    m_sMenuDescrition = "Main menu:";
}

ConsoleView::~ConsoleView()
{

}

/**
 * The class has enable_shared_from_this,
 * so we have to make sure the class will always be stored in a std::shared_ptr<ConsoleView>.
 * The constructor is private, must use that method instead.
 * @return properly build Class
 */
std::shared_ptr<ConsoleView> ConsoleView::create()
{
    struct make_shared_enabler : public ConsoleView {};
    std::shared_ptr<ConsoleView> v =std::make_shared<make_shared_enabler>();
    v->setDisplayMenuCommand(std::make_shared<CommandDisplayMenuDefault>());
    v->setQuitCommand(std::make_shared<CommandQuitDefault>());
    return v;
}



//-----------------------------------------------------------------------------------------------------------------------
// ConsoleView :: Getters
//-----------------------------------------------------------------------------------------------------------------------

std::shared_ptr<ConsoleCommandBase> ConsoleView::quitCommand() const
{
    return m_commandQuit;
}

std::shared_ptr<ConsoleCommandBase> ConsoleView::displayMenuCommand() const
{
   return m_commandDisplayMenu;
}

//-----------------------------------------------------------------------------------------------------------------------
// ConsoleView :: Setters
//-----------------------------------------------------------------------------------------------------------------------

void ConsoleView::setQuitCommand(const std::shared_ptr<ConsoleCommandBase> &quitCommand)
{
    this->removeCommand(m_commandQuit);
    m_commandQuit = quitCommand;
    this->addCommand(quitCommand);
}

void ConsoleView::setDisplayMenuCommand(const std::shared_ptr<ConsoleCommandBase> &displayMenuCommand)
{
    this->removeCommand(m_commandDisplayMenu);
    m_commandDisplayMenu = displayMenuCommand;
    this->addCommand(displayMenuCommand);
}

void ConsoleView::setDisplayModelViewCommand(const std::shared_ptr<ConsoleCommandBase> displayModelViewCommand)
{
    this->removeCommand(m_commandDisplayModelView);
    m_commandDisplayModelView = displayModelViewCommand;
    this->addCommand(displayModelViewCommand);
}

void ConsoleView::setMenuDescrition(const std::string &sMenuDescrition)
{
    m_sMenuDescrition = sMenuDescrition;
}



//-----------------------------------------------------------------------------------------------------------------------
// ConsoleView :: Methods
//-----------------------------------------------------------------------------------------------------------------------

/**
 * Display sName in a frame
 * @param sName
 */
void ConsoleView::displayAppName(const std::string &sName)
{
    std::string sSpacer(sName.length(), '/');

    std::cout << "   ////////////////////////" << sSpacer << std::endl;
    std::cout << "   ////////////////////////" << sSpacer << std::endl;
    std::cout << "   ///         " + sName + "         ///" << std::endl;
    std::cout << "   ////////////////////////" << sSpacer << std::endl;
    std::cout << "   ////////////////////////" << sSpacer << std::endl;
}
/**
 * Add a command to the view.
 * @param [in] newCommand
 */
void ConsoleView::addCommand(const std::shared_ptr<ConsoleCommandBase> &newCommand)
{
    newCommand->modelModified.connect(                  boost::bind( &ConsoleView::displayModelView,     shared_from_this() ));
    newCommand->sendMessageToUser.connect(              boost::bind( &ConsoleView::printText,            shared_from_this(), _1 ));
    newCommand->displayAssociatedHelpToUser.connect(    boost::bind( &ConsoleView::displayMenu,          shared_from_this() ));
    newCommand->quitAssociatedViews.connect(            boost::bind( &ConsoleView::quit,                 shared_from_this() ));

    m_commands.push_back(newCommand);
}
/**
 * Remove a command from the view.
 * @param [in] cmd
 */
void ConsoleView::removeCommand(const std::shared_ptr<ConsoleCommandBase> &cmd)
{
    for (unsigned int i = 0 ; i < m_commands.size() ; ++i)
    {
        if(m_commands[i] == cmd)
        {
            m_commands.erase(m_commands.begin() + i);
        }
    }
}

/**
 * Run the user interface view in the console.
 * This method continuously catch user's entry in a loop,
 * and process the entered command line.
 * The entry catch is trigered when the user type enter (and not at each space).
 * So sUserEntry can contain spaces.
 */
void ConsoleView::run() const
{
    std::string sUserEntry;
    do
    {
        std::cout << std::endl; // empty line
        std::cout << "Enter a command > " ;
        try
        {
            while ( !( std::getline( std::cin, sUserEntry ) ))  // entry catch trigger. getline is triggered when the user type enter
            {
                if ( std::cin.eof() )
                {
                    // ^D  (^Z on windows) -> End of stream
                    return;
                }
                else if ( std::cin.fail() )
                {
                    std::cerr << "Incorrect entry (std::cin.fail())." << std::endl;
                    std::cin.clear();
                    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                }
                else
                {
                    std::cerr << "Incorrect entry." << std::endl;
                }
            }
        }catch(...){
            std::cerr << "Incorrect entry." << std::endl;
        }

        // Entry success, sUserEntry contain the entire command line, even with spaces in.
        try {
            this->executeCommand(sUserEntry);
        }catch(...){
            std::cerr << "ERROR: the command failed, sorry." << std::endl;
        }

    } while (m_bQuit == false);

}

/**
 * Execute the command corresponding to user's entry.
 * @param [in] sUserEntry
 */
void ConsoleView::executeCommand(std::string sUserEntry) const
{
    // research of a command matching completely with sUserEntry
    for (auto&& command : m_commands)
    {
        if(command->setUserEntry(sUserEntry))
        {
            command->execute();
            return;
        }
    }

    // Any command corresponding
    std::cerr << "The entry doesn't correspond to a command." << std::endl;
}

/**
 * Display all the commands term list with associated description
 */
void ConsoleView::displayMenu() const
{
    std::string sTabulation;
    std::string sCmdTermsString;
    size_t  iMaxCommandLenght = 0, iLenght;
    std::string sUnderline(m_sMenuDescrition.length(), '=');

    //Need iMaxCommandLenght for tabulation size calculation
    for (const auto & command : m_commands)
    {
        iLenght = command->commandTermsString().length();
        if ( iLenght > iMaxCommandLenght)
            iMaxCommandLenght = iLenght;
    }


    std::cout << std::endl; // empty line           //
    std::cout << m_sMenuDescrition << std::endl;    // Menu Descrition
    std::cout << sUnderline << std::endl;           // ===============
    std::cout <<                                      "The commands are:" << std::endl;

    for (const auto & command : m_commands)
    {
        sCmdTermsString = command->commandTermsString();
        sTabulation = std::string(iMaxCommandLenght - sCmdTermsString.length(), ' ');
        std::cout << "   - " << command->commandTermsString() << sTabulation << " :  " << command->description() << std::endl;
    }

    std::cout << std::endl; // empty line
    std::cout <<                                      "-> Slash separated commands are equivalent." << std::endl;
    std::cout <<                                      "-> The commands can be written in lower case as well." << std::endl;

}

/**
 * Print sText in the console
 * @param [in] sText
 */
void ConsoleView::printText(const std::string &sText) const
{
    std::cout << sText ;
}

/**
 * Print model's view int the console.
 * m_commandDisplayModelView has to be set in order to make this work.
 */
void ConsoleView::displayModelView() const
{
    if (m_commandDisplayModelView != nullptr)
    {
        try {
            m_commandDisplayModelView->execute();
        }catch(...){
            std::cerr << "ERROR: Display failed, sorry." << std::endl;
        }
    }
}

/**
 * Trigger m_bQuit to true in order to stop the run() method
 */
void ConsoleView::quit()
{
    m_bQuit = true;
}
