/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: DoneCmd
 * Command class: End of the game.
 * Check if the player is back to the start node, and congratulate.
 * back to main menu.
 */
#ifndef DONECMD_H
#define DONECMD_H

// Includes:
#include "consolecommand.h"

class CollectGame;


class DoneCmd : public ConsoleCommand<CollectGame>
{
public:
    DoneCmd();
    ~DoneCmd() override;

    // Methods:
    virtual void execute() override;
};

#endif // DONECMD_H
