/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                       */
/*----------------------------------------------------------------*/


#include  <memory>
#include "consoleview.h"
#include "model/game/collectgame.h"
#include "control/parametersModification/submenuparameterscmd.h"
#include "control/game/submenugamecmd.h"


/**
 * Collect Game Main
 * @return 0 if success
 */
int main()
{
    // Model
    std::shared_ptr<CollectGame> gameModel = std::make_shared<CollectGame>();

    // View
    std::shared_ptr<ConsoleView> mainMenu = ConsoleView::create();

    // Commands
    std::shared_ptr<Command> cmdGame= std::make_shared<SubMenuGameCmd>();
    cmdGame->setModel(gameModel);
    mainMenu->addCommand(cmdGame);

    std::shared_ptr<Command> cmdParametersView = std::make_shared<SubMenuParametersCmd>();
    cmdParametersView->setModel(gameModel);
    mainMenu->addCommand(cmdParametersView);

    // View set up
    mainMenu->setMenuDescrition("Main menu");
    mainMenu->displayAppName("COLLECT GAME");


    // run the view
    mainMenu->displayMenu();
    mainMenu->run();
    return 0;
}
