/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: PickFirstItemCmd
 * Command class: Pick the first item in the current node of the player
 */
#ifndef PICKFIRSTITEMCMD_H
#define PICKFIRSTITEMCMD_H

// Includes:
#include "consolecommand.h"

class CollectGame;


class PickFirstItemCmd : public ConsoleCommand<CollectGame>
{
public:
    PickFirstItemCmd();
    ~PickFirstItemCmd() override;

    // Methods:
    virtual void execute() override;
};

#endif // PICKFIRSTITEMCMD_H
