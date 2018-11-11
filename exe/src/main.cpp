/*----------------------------------------------------------------*/
/*  PROJECT:    Collect Game                                       */
/*----------------------------------------------------------------*/


#include  <memory>
#include "consoleview.h"
#include "model/game/collectgame.h"
#include "control/parametersModification/submenuparameterscmd.h"
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
    std::shared_ptr<Command> cmdParametersView = std::make_shared<SubMenuParametersCmd>();
    cmdParametersView->setModel(gameModel);
    mainMenu->addCommand(cmdParametersView);
/*
    std::shared_ptr<ConsoleCommand<ModelMockup>> cSetValueMockupModel = std::make_shared<CommandSetValueMockupModel>();
    cSetValueMockupModel->setModel(m);
    v->addCommand(cSetValueMockupModel);
*/
    mainMenu->setMenuDescrition("Main menu");

    mainMenu->displayAppName("COLLECT GAME");
    mainMenu->displayMenu();

    // run the view
    mainMenu->run();
    return 0;
}
