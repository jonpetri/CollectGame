/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: SetPlayerItemCountLimitCmd
 * Command class: set player item count limit
 */
#ifndef SETPLAYERITEMCOUNTLIMITCMD_H
#define SETPLAYERITEMCOUNTLIMITCMD_H

// Includes:
#include "consolecommand.h"

class CollectGame;


class SetPlayerItemCountLimitCmd : public ConsoleCommand<CollectGame>
{
public:
    SetPlayerItemCountLimitCmd();
    ~SetPlayerItemCountLimitCmd() override;

    // Methods:
    virtual void execute() override;

private:
    // Methods:

    // Members:

};

#endif // SETPLAYERITEMCOUNTLIMITCMD_H
