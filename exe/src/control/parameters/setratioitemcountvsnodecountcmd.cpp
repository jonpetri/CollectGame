#include "setratioitemcountvsnodecountcmd.h"

#include "model/game/collectgame.h"
#include "model/game/gameparameters.h"

//-----------------------------------------------------------------------------------------------------------------------
// SetRatioItemCountVsNodeCountCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
SetRatioItemCountVsNodeCountCmd::SetRatioItemCountVsNodeCountCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("IC");
    this->setDescription("Modify the ratio item count / node count");
    this->setExpectedParameterCount(1);
}
SetRatioItemCountVsNodeCountCmd::~SetRatioItemCountVsNodeCountCmd()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// SetRatioItemCountVsNodeCountCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * Set the ratio item count / node count
 */
void SetRatioItemCountVsNodeCountCmd::execute()
{
    float fParaValue;

    if (this->checkParameterIsPositiveFloat(0, fParaValue) == false)
        return;

    if (this->m_model->gameParameters()->setRatio_ItemCountVsNodeCount(fParaValue) == false)
    {
        this->sendMessageToUser("Incorrect entry.\n");
        return;
    }

    this->modelModified();
}
