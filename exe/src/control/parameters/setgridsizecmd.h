/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: SetGridSizeCmd
 * Command class: set the GridSize parameter
 */
#ifndef SetGridSizeCmd_H
#define SetGridSizeCmd_H

// Includes:
#include "consolecommand.h"

class CollectGame;

class SetGridSizeCmd : public ConsoleCommand<CollectGame>
{
public:
    SetGridSizeCmd();
    ~SetGridSizeCmd() override;

    // Methods:
    virtual void execute() override;

};

#endif // SetGridSizeCmd_H
