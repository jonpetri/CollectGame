/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: MoveUpCmd
 * Command class: Move the player up
 */
#ifndef MOVEUPCMD_H
#define MOVEUPCMD_H

// Includes:
#include "consolecommand.h"

class CollectGame;


class MoveUpCmd : public ConsoleCommand<CollectGame>
{
public:
    MoveUpCmd();
    ~MoveUpCmd() override;

    // Methods:
    virtual void execute() override;
};

#endif // MOVEUPCMD_H
