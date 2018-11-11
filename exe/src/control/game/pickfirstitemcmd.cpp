#include "pickfirstitemcmd.h"

#include "model/game/collectgame.h"

//-----------------------------------------------------------------------------------------------------------------------
// PickFirstItemCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
PickFirstItemCmd::PickFirstItemCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("PICK");
    this->setDescription("Pick the first item in the current node");
    this->setExpectedParameterCount(0);
}
PickFirstItemCmd::~PickFirstItemCmd()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// PickFirstItemCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * Pick the first item in the current node of the player
 */
void PickFirstItemCmd::execute()
{
     bool bWeightLimitReached, bItemCountLimitReached;

    if (m_model->playerPickItem(1, bWeightLimitReached,  bItemCountLimitReached))
        this->modelModified();
    else
    {
        if (!bWeightLimitReached and !bItemCountLimitReached)
            this->sendMessageToUser("There is nothing here  :-/\n");
        else if (!bWeightLimitReached and bItemCountLimitReached)
            this->sendMessageToUser("You can't pick that much item  :-/\n");
        else if (bWeightLimitReached and !bItemCountLimitReached)
            this->sendMessageToUser("You can't pick this item, it's too heavy  :-/\n");
        else
            this->sendMessageToUser("You can't pick that much item, and it's also too heavy!!  :-S\n");
    }
}
