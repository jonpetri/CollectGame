#include "setitemmaxweightcmd.h"

#include "model/game/collectgame.h"
#include "model/game/gameparameters.h"

//-----------------------------------------------------------------------------------------------------------------------
// SetItemMaxWeightCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
SetItemMaxWeightCmd::SetItemMaxWeightCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("IMW");
    this->setDescription("Modify item's maximum weight");
    this->setExpectedParameterCount(1);
}
SetItemMaxWeightCmd::~SetItemMaxWeightCmd()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// SetItemMaxWeightCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * set item's maximum weight parameter
 */
void SetItemMaxWeightCmd::execute()
{
    unsigned int iPara;

    if (this->checkParameterIsUnsignedInt(0, iPara) == false)
        return;

    if (this->m_model->gameParameters()->setItemMaxWeight(iPara) == false)
    {
        this->sendMessageToUser("Incorrect entry\n");
        return;
    }

    this->modelModified();
}
