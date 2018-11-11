#include "setratioedgecountvsgridspotcountcmd.h"

#include "model/game/collectgame.h"
#include "model/game/gameparameters.h"

//-----------------------------------------------------------------------------------------------------------------------
// SetRatioEdgeCountVsGridSpotCountCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
SetRatioEdgeCountVsGridSpotCountCmd::SetRatioEdgeCountVsGridSpotCountCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("EC");
    this->setDescription("Modify the ratio Edge count / grid spot count");
    this->setExpectedParameterCount(1);
}
SetRatioEdgeCountVsGridSpotCountCmd::~SetRatioEdgeCountVsGridSpotCountCmd()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// SetRatioEdgeCountVsGridSpotCountCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * set the ratioa Edge count / grid spot count
 */
void SetRatioEdgeCountVsGridSpotCountCmd::execute()
{
    float fParaValue;

    if (this->checkParameterIsPositiveFloat(0, fParaValue) == false)
        return;

    if (this->m_model->gameParameters()->setRatio_EdgeCountVsGridSpotCount(fParaValue) == false)
    {
        this->sendMessageToUser("Incorrect entry\n");
        return;
    }

    this->modelModified();
}
