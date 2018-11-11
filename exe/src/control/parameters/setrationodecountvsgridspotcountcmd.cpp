#include "setrationodecountvsgridspotcountcmd.h"

#include "model/game/collectgame.h"
#include "model/game/gameparameters.h"

//-----------------------------------------------------------------------------------------------------------------------
// SetRatioNodeCountVsGridSpotCountCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
SetRatioNodeCountVsGridSpotCountCmd::SetRatioNodeCountVsGridSpotCountCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("NC");
    this->setDescription("Modify the ratio Node count / grid spot count");
    this->setExpectedParameterCount(1);
}
SetRatioNodeCountVsGridSpotCountCmd::~SetRatioNodeCountVsGridSpotCountCmd()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// SetRatioNodeCountVsGridSpotCountCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * Set the parameter Node count / grid spot count ratio
 */
void SetRatioNodeCountVsGridSpotCountCmd::execute()
{
    float fParaValue;

    if (this->checkParameterIsPositiveFloat(0, fParaValue) == false)
        return;

    if (this->m_model->gameParameters()->setRatio_NodeCountVsGridSpotCount(fParaValue) == false)
    {
        this->sendMessageToUser("Incorrect entry\n");
        return;
    }

    this->modelModified();
}
