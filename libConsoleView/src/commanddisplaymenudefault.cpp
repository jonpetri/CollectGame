#include "commanddisplaymenudefault.h"

//-----------------------------------------------------------------------------------------------------------------------
// CommandDisplayMenuDefault :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
CommandDisplayMenuDefault::CommandDisplayMenuDefault()
{
    // Command's terms/arguments definition
    this->addCommandTerm("help");
    this->addCommandTerm("?");

    this->setDescription("Show menu description.");
}

CommandDisplayMenuDefault::~CommandDisplayMenuDefault()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// CommandDisplayMenuDefault :: Getters
//-----------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
// CommandDisplayMenuDefault :: Setters
//-----------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
// CommandDisplayMenuDefault :: Methods
//-----------------------------------------------------------------------------------------------------------------------

/**
 * Execute the action of the command.
 */
void CommandDisplayMenuDefault::execute()
{
    this->displayAssociatedHelpToUser();
}
