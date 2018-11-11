#include "setplayeritemcountlimitcmd.h"

#include "model/game/collectgame.h"
#include "model/game/gameparameters.h"

//-----------------------------------------------------------------------------------------------------------------------
// SetPlayerItemCountLimitCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
SetPlayerItemCountLimitCmd::SetPlayerItemCountLimitCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("PIL");
    this->setDescription("Modify the player's item count limit");
    this->setExpectedParameterCount(1);
}
SetPlayerItemCountLimitCmd::~SetPlayerItemCountLimitCmd()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// SetPlayerItemCountLimitCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * set player item count limit parameter
 */
void SetPlayerItemCountLimitCmd::execute()
{
    unsigned int iPara;

    if (this->checkParameterIsUnsignedInt(0, iPara) == false)
        return;

    if (this->m_model->gameParameters()->setPlayerItemCountLimit(iPara) == false)
    {
        this->sendMessageToUser("Incorrect entry");
        return;
    }

    this->modelModified();
}
