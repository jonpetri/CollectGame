#include "consolecommandbaseInheritance.h"

//-----------------------------------------------------------------------------------------------------------------------
// ConsoleCommandBaseInheritance :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
ConsoleCommandBaseInheritance::ConsoleCommandBaseInheritance()
{

}

ConsoleCommandBaseInheritance::~ConsoleCommandBaseInheritance()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// ConsoleCommandBaseInheritance :: Getters
//-----------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
// ConsoleCommandBaseInheritance :: Setters
//-----------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
// ConsoleCommandBaseInheritance :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * Execute the action of the command.
 */
void ConsoleCommandBaseInheritance::execute()
{
    this->setDescription("OK");
}
