/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: SetRatioEdgeCountVsGridSpotCountCmd
 * Command class: set the ratioa Edge count / grid spot count
 */
#ifndef SETRATIOEDGECOUNTVSGRIDSPOTCOUNTCMD_H
#define SETRATIOEDGECOUNTVSGRIDSPOTCOUNTCMD_H

// Includes:
#include "consolecommand.h"

class CollectGame;


class SetRatioEdgeCountVsGridSpotCountCmd : public ConsoleCommand<CollectGame>
{
public:
    SetRatioEdgeCountVsGridSpotCountCmd();
    ~SetRatioEdgeCountVsGridSpotCountCmd() override;

    // Methods:
    virtual void execute() override;

private:
    // Methods:

    // Members:

};

#endif // SETRATIOEDGECOUNTVSGRIDSPOTCOUNTCMD_H
