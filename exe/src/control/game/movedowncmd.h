/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: MoveDownCmd
 * Command class:  Move the player Down
 */
#ifndef MOVEDOWNCMD_H
#define MOVEDOWNCMD_H

// Includes:
#include "consolecommand.h"

class CollectGame;


class MoveDownCmd : public ConsoleCommand<CollectGame>
{
public:
    MoveDownCmd();
    ~MoveDownCmd() override;

    // Methods:
    virtual void execute() override;
};

#endif // MOVEDOWNCMD_H
