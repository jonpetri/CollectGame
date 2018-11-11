/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: SetPlayerWeightLimitCmd
 * Command class: set PlayerItemWeightLimit
 */
#ifndef SETPLAYERWEIGHTLIMITCMD_H
#define SETPLAYERWEIGHTLIMITCMD_H

// Includes:
#include "consolecommand.h"

class CollectGame;


class SetPlayerWeightLimitCmd : public ConsoleCommand<CollectGame>
{
public:
    SetPlayerWeightLimitCmd();
    ~SetPlayerWeightLimitCmd() override;

    // Methods:
    virtual void execute() override;

private:
    // Methods:

    // Members:

};

#endif // SETPLAYERWEIGHTLIMITCMD_H
