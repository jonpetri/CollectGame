#include "setplayerweightlimitcmd.h"

#include "model/game/collectgame.h"
#include "model/game/gameparameters.h"

//-----------------------------------------------------------------------------------------------------------------------
// SetPlayerWeightLimitCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
SetPlayerWeightLimitCmd::SetPlayerWeightLimitCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("PWL");
    this->setDescription("Modify the player's total Weight limit");
    this->setExpectedParameterCount(1);
}
SetPlayerWeightLimitCmd::~SetPlayerWeightLimitCmd()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// SetPlayerWeightLimitCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * set Player Item Weight Limit parameter
 */
void SetPlayerWeightLimitCmd::execute()
{
    unsigned int iPara;

    if (this->checkParameterIsUnsignedInt(0, iPara) == false)
        return;

    if (this->m_model->gameParameters()->setPlayerWeightLimit(iPara) == false)
    {
        this->sendMessageToUser("Incorrect entry\n");
        return;
    }

    this->modelModified();
}
