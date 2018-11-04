/*----------------------------------------------------------------*/
/*  PROJECT:    Console View                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: CommandQuitDefault
 * Action of exit from a ConsoleView menu.
 */
#ifndef COMMANDQUITDEFAULT_H
#define COMMANDQUITDEFAULT_H

// Includes:
#include "consolecommandbase.h"

class CommandQuitDefault : public ConsoleCommandBase
{
public:
    CommandQuitDefault();

    ~CommandQuitDefault()override;

    // Getters:

    // Setters:

    // Methods:
    virtual void execute() override;

private:
    // Methods:

    // Members:

};

#endif // COMMANDQUITDEFAULT_H
