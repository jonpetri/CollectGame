#include "setgridsizecmd.h"

#include "model/game/collectgame.h"
#include "model/game/gameparameters.h"

//-----------------------------------------------------------------------------------------------------------------------
// MenuGamaParametersCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
SetGridSizeCmd::SetGridSizeCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("GW");
    this->setDescription("Modify the grid width.");
    this->setExpectedParameterCount(1);
}
SetGridSizeCmd::~SetGridSizeCmd()
{

}


//-----------------------------------------------------------------------------------------------------------------------
// MenuGamaParametersCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------

/**
 * set the GridSize parameter
 */
void SetGridSizeCmd::execute()
{
    unsigned int iPara;

    if (this->checkParameterIsUnsignedInt(0, iPara) == false)
        return;

    if (this->m_model->gameParameters()->setGridSideSize(iPara) == false)
    {
        this->sendMessageToUser("Incorrect entry");
        return;
    }

    this->modelModified();
}
