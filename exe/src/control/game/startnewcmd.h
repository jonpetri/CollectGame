/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: StartNewCmd
 * Command class: Start a new game: new map generation
 */
#ifndef STARTNEWCMD_H
#define STARTNEWCMD_H

// Includes:
#include "consolecommand.h"

class CollectGame;


class StartNewCmd : public ConsoleCommand<CollectGame>
{
public:
    StartNewCmd();
    ~StartNewCmd() override;

    // Methods:
    virtual void execute() override;
};

#endif // STARTNEWCMD_H
