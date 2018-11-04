/*----------------------------------------------------------------*/
/*  PROJECT:    Console View                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: ConsoleCommandBaseInheritance
 *
 */
#ifndef ConsoleCommandBaseInheritance_H
#define ConsoleCommandBaseInheritance_H

// Includes:
#include "consolecommandbase.h"

class ConsoleCommandBaseInheritance : public ConsoleCommandBase
{
public:
    ConsoleCommandBaseInheritance();

    ~ConsoleCommandBaseInheritance()override;

    // Getters:

    // Setters:

    // Methods:
    virtual void execute() override;

private:
    // Methods:

    // Members:

};

#endif // ConsoleCommandBaseInheritance_H
