/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: SetItemMaxWeightCmd
 * Command class: set ItemMaxWeight parameter
 */
#ifndef SETITEMMAXWEIGHTCMD_H
#define SETITEMMAXWEIGHTCMD_H

// Includes:
#include "consolecommand.h"

class CollectGame;


class SetItemMaxWeightCmd : public ConsoleCommand<CollectGame>
{
public:
    SetItemMaxWeightCmd();
    ~SetItemMaxWeightCmd() override;

    // Methods:
    virtual void execute() override;
};

#endif // SETITEMMAXWEIGHTCMD_H
