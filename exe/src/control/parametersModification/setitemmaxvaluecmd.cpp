#include "setitemmaxvaluecmd.h"

#include "model/game/collectgame.h"
#include "model/game/gameparameters.h"

//-----------------------------------------------------------------------------------------------------------------------
// SetItemMaxValueCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
SetItemMaxValueCmd::SetItemMaxValueCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("IMV");
    this->setDescription("Modify item's maximum value");
    this->setExpectedParameterCount(1);
}
SetItemMaxValueCmd::~SetItemMaxValueCmd()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// SetItemMaxValueCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * set item's maximum value parameter
 */
void SetItemMaxValueCmd::execute()
{
    unsigned int iPara;

    if (this->checkParameterIsUnsignedInt(0, iPara) == false)
        return;

    if (this->m_model->gameParameters()->setItemMaxValue(iPara) == false)
    {
        this->sendMessageToUser("Incorrect entry");
        return;
    }

    this->modelModified();
}
