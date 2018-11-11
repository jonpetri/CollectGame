#include "submenugamecmd.h"

#include <vector>

#include "consoleview.h"
#include "gameviewcmd.h"

#include "moveupcmd.h"
#include "moveuprightcmd.h"
#include "moverightcmd.h"
#include "movedownrightcmd.h"
#include "movedowncmd.h"
#include "movedownleftcmd.h"
#include "moveleftcmd.h"
#include "moveupleftcmd.h"

#include "pickfirstitemcmd.h"
#include "pickitemncmd.h"
#include "donecmd.h"
#include "startnewcmd.h"

#include "model/game/collectgame.h"
//-----------------------------------------------------------------------------------------------------------------------
// SubMenuGameCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
SubMenuGameCmd::SubMenuGameCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("START");
    this->setDescription("Start the game");
    this->setExpectedParameterCount(0);
}
SubMenuGameCmd::~SubMenuGameCmd()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// SubMenuGameCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * Run a new ConsoleView with all the commands to play the game.
 * The new ConsoleView act like a submenu.
 * A new game game is generated straight away.
 */
void SubMenuGameCmd::execute()
{
    std::shared_ptr<Command> cmdView ;
    std::vector<std::shared_ptr<Command>> commands(12) ;
    // View
    std::shared_ptr<ConsoleView> subMenu = ConsoleView::create();

    // Display Model View Command
    cmdView = std::make_shared<GameViewCmd>();
    cmdView->setModel(m_model);
    subMenu->setDisplayModelViewCommand(cmdView);

    // Other commands
    commands[0] = std::make_shared<MoveUpCmd>();
    commands[1] = std::make_shared<MoveUpRightCmd>();
    commands[2] = std::make_shared<MoveRightCmd>();
    commands[3] = std::make_shared<MoveDownRightCmd>();
    commands[4] = std::make_shared<MoveDownCmd>();
    commands[5] = std::make_shared<MoveDownLeftCmd>();
    commands[6] = std::make_shared<MoveLeftCmd>();
    commands[7] = std::make_shared<MoveUpLeftCmd>();

    commands[8] = std::make_shared<PickFirstItemCmd>();
    commands[9] = std::make_shared<PickItemNCmd>();
    commands[10] = std::make_shared<DoneCmd>();
    commands[11] = std::make_shared<StartNewCmd>();


    for (auto const & cmd : commands)
    {
        cmd->setModel(m_model);
        subMenu->addCommand(cmd);
    }

    // View set up
    subMenu->setMenuDescrition("GAME: Pick a maximum of valuable item, and return to your start point");

    // quit command becomes return to main menu:
    std::shared_ptr<ConsoleCommandBase> quitCmd = subMenu->quitCommand();
    quitCmd->clearCommandTermList();
    quitCmd->addCommandTerm("x");
    quitCmd->addCommandTerm("ret");
    quitCmd->setDescription("Return to main menu");


    // new game generation
    m_model->createNewGame();

    subMenu->displayMenu();
    subMenu->displayModelView();

    // run the view
    subMenu->run();

    this->sendMessageToUser("\n");
    this->sendMessageToUser("You are back in the main menu.\n");
}
