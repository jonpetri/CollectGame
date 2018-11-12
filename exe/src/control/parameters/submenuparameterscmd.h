/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: SubMenuParametersCmd
 * Command: Run a new ConsoleView with all the commands to modify game parameters.
 * The new ConsoleView act like a submenu about game parameters.
 */
#ifndef SubMenuParametersCmd_H
#define SubMenuParametersCmd_H

// Includes:
#include "consolecommand.h"
#include "model/game/collectgame.h"

typedef ConsoleCommand<CollectGame> Command;

class SubMenuParametersCmd : public ConsoleCommand<CollectGame>
{
public:
    SubMenuParametersCmd();
    ~SubMenuParametersCmd() override;

    // Methods:
    virtual void execute() override;

};

#endif // SubMenuParametersCmd_H
