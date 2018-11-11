/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: MoveRightCmd
 * Command class:  Move the player Right
 */
#ifndef MOVERIGHTCMD_H
#define MOVERIGHTCMD_H

// Includes:
#include "consolecommand.h"

class CollectGame;


class MoveRightCmd : public ConsoleCommand<CollectGame>
{
public:
    MoveRightCmd();
    ~MoveRightCmd() override;

    // Methods:
    virtual void execute() override;
};

#endif // MOVERIGHTCMD_H
