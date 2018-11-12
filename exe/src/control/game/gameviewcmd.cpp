#include "gameviewcmd.h"

#include "model/game/collectgame.h"

//-----------------------------------------------------------------------------------------------------------------------
// GameViewCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
GameViewCmd::GameViewCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("DISPLAY");
    this->setDescription("Display game view");
    this->setExpectedParameterCount(0);
}
GameViewCmd::~GameViewCmd()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// GameViewCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * set the XXXX parameter
 */
void GameViewCmd::execute()
{
    std::string sView;
    m_model->getConsolePrint(sView);
    this->sendMessageToUser("\n");
    this->sendMessageToUser(sView);
}
