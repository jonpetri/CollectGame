/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: MoveUpLeftCmd
 * Command class:  Move the player up left
 */
#ifndef MOVEUPLEFTCMD_H
#define MOVEUPLEFTCMD_H

// Includes:
#include "consolecommand.h"

class CollectGame;


class MoveUpLeftCmd : public ConsoleCommand<CollectGame>
{
public:
    MoveUpLeftCmd();
    ~MoveUpLeftCmd() override;

    // Methods:
    virtual void execute() override;
};

#endif // MOVEUPLEFTCMD_H
