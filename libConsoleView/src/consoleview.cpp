#include "consoleview.h"

#include <iostream>
#include <limits>
#include <boost/bind.hpp>

#include "commanddisplaymenudefault.h"
#include "commandquitdefault.h"

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

/**
 * The class has enable_shared_from_this, and it is not possible to call shared_from_this() within the constructor.
 * So use this method to construct a ConsoleView.
 * @return properly build ConsoleView
 */
std::shared_ptr<ConsoleView> ConsoleView::create()
{
    std::shared_ptr<ConsoleView> v =std::make_shared<ConsoleView>();
    v->setDisplayMenuCommand(std::make_shared<CommandDisplayMenuDefault>());
    v->setQuitCommand(std::make_shared<CommandQuitDefault>());
    return v;
}


ConsoleView::~ConsoleView()
{

}


//-----------------------------------------------------------------------------------------------------------------------
// ConsoleView :: Getters
//-----------------------------------------------------------------------------------------------------------------------

std::shared_ptr<ConsoleCommandBase> ConsoleView::quitCommand()
{
    return m_commandQuit;
}

std::shared_ptr<ConsoleCommandBase> ConsoleView::displayMenuCommand()
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

void ConsoleView::setDisplayModelViewCommand(const std::shared_ptr<ConsoleCommandBase> &displayModelViewCommand)
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
void ConsoleView::run()
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
                    std::cerr << "Incorrect entry (std::cin.fail()), retry." << std::endl;
                    std::cin.clear();
                    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
                }
                else
                {
                    std::cerr << "Incorrect entry, retry." << std::endl;
                }
            }
        }catch(...){
            std::cerr << "Incorrect entry, retry." << std::endl;
        }

        // Entry success, sUserEntry contain the entire command line, even with spaces in.
        this->executeCommand(sUserEntry);

    } while (m_bQuit == false);

}

/**
 * Execute the command corresponding to user's entry.
 * @param [in] sUserEntry
 */
void ConsoleView::executeCommand(std::string sUserEntry)
{
    // research of a command matching completely with sUserEntry
    for (auto&& command : m_commands)
    {
        if(command->isMatchingUserEntry(sUserEntry))
        {
            command->execute();
            return;
        }
    }

    // Any command corresponding
    std::cerr << "The entry doesn't correspond to a command, retry." << std::endl;
}

/**
 * Display all the commands term list with associated description
 */
void ConsoleView::displayMenu()
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
    std::cout <<                                      "-> The commands can be written lower case as well." << std::endl;

}

/**
 * Print sText in the console
 * @param [in] sText
 */
void ConsoleView::printText(const std::string &sText)
{
    std::cout << sText ;
}

/**
 * Print model's view int the console.
 * m_commandDisplayModelView has to be set in order to make this work.
 */
void ConsoleView::displayModelView()
{
    if (m_commandDisplayModelView != nullptr)
        m_commandDisplayModelView->execute();
}

/**
 * Trigger m_bQuit to true in order to stop the run() method
 */
void ConsoleView::quit()
{
    m_bQuit = true;
}
