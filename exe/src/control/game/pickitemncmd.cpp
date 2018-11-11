#include "pickitemncmd.h"

#include "model/game/collectgame.h"

//-----------------------------------------------------------------------------------------------------------------------
// PickItemNCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
PickItemNCmd::PickItemNCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("PICK");
    this->setDescription("Pick the item number N in the current node");
    this->setExpectedParameterCount(1);
}
PickItemNCmd::~PickItemNCmd()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// PickItemNCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * Pick the item number N in the current node of the player
 */
void PickItemNCmd::execute()
{
    unsigned int iN;
    bool bWeightLimitReached, bItemCountLimitReached;

    if (this->checkParameterIsUnsignedInt(0, iN) == false)
        return;

    if (iN == 0)
    {
        this->sendMessageToUser("Incorrect entry, the first item is the item number 1.\n");
        return;
    }


   if (m_model->playerPickItem(iN, bWeightLimitReached,  bItemCountLimitReached))
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
