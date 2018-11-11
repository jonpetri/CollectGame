/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: SetRatioItemCountVsNodeCountCmd
 * Command class: Set the ratio item count / node count
 */
#ifndef SETRATIOITEMCOUNTVSNODECOUNTCMD_H
#define SETRATIOITEMCOUNTVSNODECOUNTCMD_H

// Includes:
#include "consolecommand.h"

class CollectGame;


class SetRatioItemCountVsNodeCountCmd : public ConsoleCommand<CollectGame>
{
public:
    SetRatioItemCountVsNodeCountCmd();
    ~SetRatioItemCountVsNodeCountCmd() override;

    // Methods:
    virtual void execute() override;

private:
    // Methods:

    // Members:

};

#endif // SETRATIOITEMCOUNTVSNODECOUNTCMD_H
