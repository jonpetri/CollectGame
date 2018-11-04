#include "commandquitdefault.h"

//-----------------------------------------------------------------------------------------------------------------------
// CommandQuitDefault :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
CommandQuitDefault::CommandQuitDefault()
{
    // Command's terms/arguments definition
    this->addCommandTerm("exit");
    this->addCommandTerm("quit");
    this->addCommandTerm("q");

    this->setDescription("Quit the program");
}

CommandQuitDefault::~CommandQuitDefault()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// CommandQuitDefault :: Getters
//-----------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
// CommandQuitDefault :: Setters
//-----------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
// CommandQuitDefault :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * Execute the action of the command.
 */
void CommandQuitDefault::execute()
{
    this->quitAssociatedViews();
}
