/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: GameViewCmd
 * Command class: display game state in the console.
 */
#ifndef GAMEVIEWCMD_H
#define GAMEVIEWCMD_H

// Includes:
#include "consolecommand.h"

class CollectGame;


class GameViewCmd : public ConsoleCommand<CollectGame>
{
public:
    GameViewCmd();
    ~GameViewCmd() override;

    // Methods:
    virtual void execute() override;
};

#endif // GAMEVIEWCMD_H
