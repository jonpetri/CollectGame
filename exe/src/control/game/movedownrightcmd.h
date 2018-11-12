/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: MoveDownRightCmd
 * Command class:  Move the player DownRight
 */
#ifndef MOVEDOWNRIGHTCMD_H
#define MOVEDOWNRIGHTCMD_H

// Includes:
#include "consolecommand.h"

class CollectGame;


class MoveDownRightCmd : public ConsoleCommand<CollectGame>
{
public:
    MoveDownRightCmd();
    ~MoveDownRightCmd() override;

    // Methods:
    virtual void execute() override;
};

#endif // MOVEDOWNRIGHTCMD_H
