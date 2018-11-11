/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: ParametersViewCmd
 * Command that display game's parameters in the console.
 */
#ifndef ParametersViewCmd_H
#define ParametersViewCmd_H

// Includes:
#include "consolecommand.h"

class CollectGame;

class ParametersViewCmd : public ConsoleCommand<CollectGame>
{
public:
    ParametersViewCmd();
    ~ParametersViewCmd() override;

    // Methods:
    virtual void execute() override;

};

#endif // ParametersViewCmd_H
