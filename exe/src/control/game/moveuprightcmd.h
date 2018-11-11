/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: MoveUpRightCmd
 * Command class:  Move the player UpRight
 */
#ifndef MOVEUPRIGHTCMD_H
#define MOVEUPRIGHTCMD_H

// Includes:
#include "consolecommand.h"

class CollectGame;


class MoveUpRightCmd : public ConsoleCommand<CollectGame>
{
public:
    MoveUpRightCmd();
    ~MoveUpRightCmd() override;

    // Methods:
    virtual void execute() override;
};

#endif // MOVEUPRIGHTCMD_H
