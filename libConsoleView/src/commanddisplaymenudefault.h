/*----------------------------------------------------------------*/
/*  PROJECT:    Console View                                  */
/*----------------------------------------------------------------*/
/**
 * CLASS: CommandDisplayMenuDefault
 * Ask the linked view to display the menu.
 * See all the explanations in the ConsoleCommandBase class.
 */
#ifndef COMMANDDISPLAYMENUDEFAULT_H
#define COMMANDDISPLAYMENUDEFAULT_H

// Includes:
#include "consolecommandbase.h"

class CommandDisplayMenuDefault : public ConsoleCommandBase
{
public:
    CommandDisplayMenuDefault();

    ~CommandDisplayMenuDefault() override;

    // Getters:

    // Setters:

    // Methods:
    virtual void execute() override;

private:
    // Methods:

    // Members:

};

#endif // COMMANDDISPLAYMENUDEFAULT_H
