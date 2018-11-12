/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: SubMenuGameCmd
 * Command class: Run a new ConsoleView with all the commands to play the game.
 * The new ConsoleView act like a submenu.
 * A new game game is generated straight away.
 */
#ifndef SUBMENUGAMECMD_H
#define SUBMENUGAMECMD_H

// Includes:
#include "consolecommand.h"

class CollectGame;

typedef ConsoleCommand<CollectGame> Command;

class SubMenuGameCmd : public ConsoleCommand<CollectGame>
{
public:
    SubMenuGameCmd();
    ~SubMenuGameCmd() override;

    // Methods:
    virtual void execute() override;
};

#endif // SUBMENUGAMECMD_H
