/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: MoveDownLeftCmd
 * Command class:  Move the player DownLeft
 */
#ifndef MOVEDOWNLEFTCMD_H
#define MOVEDOWNLEFTCMD_H

// Includes:
#include "consolecommand.h"

class CollectGame;


class MoveDownLeftCmd : public ConsoleCommand<CollectGame>
{
public:
    MoveDownLeftCmd();
    ~MoveDownLeftCmd() override;

    // Methods:
    virtual void execute() override;
};

#endif // MOVEDOWNLEFTCMD_H
