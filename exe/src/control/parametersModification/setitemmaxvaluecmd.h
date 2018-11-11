/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: SetItemMaxValueCmd
 * Command class: set item's maximum value parameter
 */
#ifndef SETITEMMAXVALUECMD_H
#define SETITEMMAXVALUECMD_H

// Includes:
#include "consolecommand.h"

class CollectGame;


class SetItemMaxValueCmd : public ConsoleCommand<CollectGame>
{
public:
    SetItemMaxValueCmd();
    ~SetItemMaxValueCmd() override;

    // Methods:
    virtual void execute() override;

private:
    // Methods:

    // Members:

};

#endif // SETITEMMAXVALUECMD_H
