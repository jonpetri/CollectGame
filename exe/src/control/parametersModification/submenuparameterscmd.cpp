#include "submenuparameterscmd.h"

#include <vector>

#include "consoleview.h"
#include "parametersviewcmd.h"
#include "setgridsizecmd.h"
#include "setitemmaxvaluecmd.h"
#include "setitemmaxweightcmd.h"
#include "setplayeritemcountlimitcmd.h"
#include "setplayerweightlimitcmd.h"
#include "setratioedgecountvsgridspotcountcmd.h"
#include "setratioitemcountvsnodecountcmd.h"
#include "setrationodecountvsgridspotcountcmd.h"



//-----------------------------------------------------------------------------------------------------------------------
// MenuGamaParametersCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
SubMenuParametersCmd::SubMenuParametersCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("PARAM");
    this->setDescription("Go to the game parameters modification menu (grid size...).");
    this->setExpectedParameterCount(0);
}
SubMenuParametersCmd::~SubMenuParametersCmd()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// MenuGamaParametersCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------

/**
 * Run a new ConsoleView with all the commands to modify game parameters.
 * The new ConsoleView act like a submenu about game parameters.
 */
void SubMenuParametersCmd::execute()
{
    std::shared_ptr<Command> cmdView ;
    std::vector<std::shared_ptr<Command>> commands(8) ;
    // View
    std::shared_ptr<ConsoleView> subMenu = ConsoleView::create();

    // Display Model View Command
    cmdView = std::make_shared<ParametersViewCmd>();
    cmdView->setModel(m_model);
    subMenu->setDisplayModelViewCommand(cmdView);

    // Other commands
    commands[0] = std::make_shared<SetGridSizeCmd>();
    commands[1] = std::make_shared<SetRatioNodeCountVsGridSpotCountCmd>();
    commands[2] = std::make_shared<SetRatioEdgeCountVsGridSpotCountCmd>();
    commands[3] = std::make_shared<SetRatioItemCountVsNodeCountCmd>();
    commands[4] = std::make_shared<SetItemMaxWeightCmd>();
    commands[5] = std::make_shared<SetItemMaxValueCmd>();
    commands[6] = std::make_shared<SetPlayerWeightLimitCmd>();
    commands[7] = std::make_shared<SetPlayerItemCountLimitCmd>();

    for (auto const & cmd : commands)
    {
        cmd->setModel(m_model);
        subMenu->addCommand(cmd);
    }

    // View set up
    subMenu->setMenuDescrition("Game parameters modification menu");

    // quit command becomes return to main menu:
    std::shared_ptr<ConsoleCommandBase> quitCmd = subMenu->quitCommand();
    quitCmd->clearCommandTermList();
    quitCmd->addCommandTerm("x");
    quitCmd->addCommandTerm("ret");
    quitCmd->setDescription("Return to main menu");

    subMenu->displayMenu();
    subMenu->displayModelView();

    // run the view
    subMenu->run();

    this->sendMessageToUser("\n");
    this->sendMessageToUser("You are back in the main menu.\n");
}
