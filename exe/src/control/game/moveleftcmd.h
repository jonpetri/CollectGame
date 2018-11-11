/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: MoveLeftCmd
 * Command class:  Move the player Left
 */
#ifndef MOVELEFTCMD_H
#define MOVELEFTCMD_H

// Includes:
#include "consolecommand.h"

class CollectGame;


class MoveLeftCmd : public ConsoleCommand<CollectGame>
{
public:
    MoveLeftCmd();
    ~MoveLeftCmd() override;

    // Methods:
    virtual void execute() override;
};

#endif // MOVELEFTCMD_H
