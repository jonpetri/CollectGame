/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: SetRatioNodeCountVsGridSpotCountCmd
 * Command class: Set the ratio Node count / grid spot count
 */
#ifndef SETRATIONODECOUNTVSGRIDSPOTCOUNTCMD_H
#define SETRATIONODECOUNTVSGRIDSPOTCOUNTCMD_H

// Includes:
#include "consolecommand.h"

class CollectGame;


class SetRatioNodeCountVsGridSpotCountCmd : public ConsoleCommand<CollectGame>
{
public:
    SetRatioNodeCountVsGridSpotCountCmd();
    ~SetRatioNodeCountVsGridSpotCountCmd() override;

    // Methods:
    virtual void execute() override;

private:
    // Methods:

    // Members:

};

#endif // SETRATIONODECOUNTVSGRIDSPOTCOUNTCMD_H
