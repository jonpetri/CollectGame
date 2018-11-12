#include "parametersviewcmd.h"

#include "model/game/collectgame.h"
#include "model/game/gameparameters.h"

//-----------------------------------------------------------------------------------------------------------------------
// MenuGamaParametersCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
ParametersViewCmd::ParametersViewCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("DISPLAY");
    this->setDescription("Display parameters values");
    this->setExpectedParameterCount(0);
}
ParametersViewCmd::~ParametersViewCmd()
{

}


//-----------------------------------------------------------------------------------------------------------------------
// MenuGamaParametersCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------

/**
 * Display game's parameters in the console
 */
void ParametersViewCmd::execute()
{
    this->sendMessageToUser("\n");
    this->sendMessageToUser("GAME PARAMETERS\n");
    this->sendMessageToUser("---------------\n");
    this->sendMessageToUser(m_model->gameParameters()->getConsolePrint());
}
