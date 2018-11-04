

/*----------------------------------------------------------------*/
/*  PROJECT:    Console View                                  */
/*----------------------------------------------------------------*/
/**
 * CLASS: CommandDisplayMenuDefault
 * Ask the linked views to display help.
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
