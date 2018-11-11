/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: PickItemNCmd
 * Command class: Pick the item number N in the current node of the player
 */
#ifndef PICKITEMNCMD_H
#define PICKITEMNCMD_H

// Includes:
#include "consolecommand.h"

class CollectGame;


class PickItemNCmd : public ConsoleCommand<CollectGame>
{
public:
    PickItemNCmd();
    ~PickItemNCmd() override;

    // Methods:
    virtual void execute() override;
};

#endif // PICKITEMNCMD_H
