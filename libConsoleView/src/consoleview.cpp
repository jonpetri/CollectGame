#include "consoleview.h"

#include <iostream>
#include <limits>

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

}

ConsoleView::~ConsoleView()
{

}



//-----------------------------------------------------------------------------------------------------------------------
// ConsoleView :: Getters
//-----------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
// ConsoleView :: Setters
//-----------------------------------------------------------------------------------------------------------------------
void ConsoleView::setDisplayModelViewCommand(const std::shared_ptr<ConsoleCommandBase> &displayModelViewCommand)
{
    m_commandDisplayModelView = displayModelViewCommand;
}

//-----------------------------------------------------------------------------------------------------------------------
// ConsoleView :: Methods
//-----------------------------------------------------------------------------------------------------------------------


/**
 * Add a command to the view.
 * @param [in] newCommand
 */
void ConsoleView::addCommand(const std::shared_ptr<ConsoleCommandBase> &newCommand)
{
    m_commands.push_back(newCommand);
}

/**
 * Run the iser interface view in the console
 */
void ConsoleView::run()
{
    std::string sUserEntry;
    do
    {
        //while ( !( std::cin >> sUserEntry ))
        while ( !( std::getline( std::cin, sUserEntry ) ))
        {
            if ( std::cin.eof() )
            {
                // ^D  (^Z on windows) -> End of stream
                return;
            }
            else if ( std::cin.fail() )
            {
                std::cerr << "Incorrect entry (std::cin.fail()), retry : " << std::endl;
                std::cin.clear();
                std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
            }
            else
            {
                std::cerr << "Incorrect entry (std::cin.fail()), retry : " << std::endl;
            }
        }

        // Entry success
        this->executeCommand(sUserEntry);

    } while (m_bQuit);

}

/**
 * Execute the command corresponding to user's entry.
 * @param [in] sUserEntry
 */
void ConsoleView::executeCommand(const std::string &sUserEntry)
{
    // First, research of a command matching completely with sUserEntry
    for (auto&& command : m_commands)
    {
        if(command->isMatchingUserEntryTotally(sUserEntry))
        {
            command->execute();
            return;
        }
    }

    // If no total matching found, research of a command matching with sUserEntry first argument
    for (auto&& command : m_commands)
    {
        if(command->isMatchingUserEntryFirstArgument(sUserEntry))
        {
            command->execute();
            return;
        }
    }

    // Any command corresponding
    std::cerr << "There are no corresponding commands to this entry." << std::endl;
}

/**
 * Display all the commands term list with associated description
 */
void ConsoleView::displayMenu()
{
    std::cout << std::endl; // empty line
    std::cout << "Commands menu:" << std::endl;
    std::cout << "==============" << std::endl;

    for (const auto & command : m_commands)
    {
        std::cout << command->commandTermsString() << " :    " << command->description() << std::endl;
    }
    std::cout << std::endl; // empty line
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
    m_commandDisplayModelView->execute();
}

/**
 * Trigger m_bQuit to true in order to stop the run() method
 */
void ConsoleView::quit()
{
    m_bQuit = true;
}
