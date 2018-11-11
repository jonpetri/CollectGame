/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: SubMenuParametersCmd
 *
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
