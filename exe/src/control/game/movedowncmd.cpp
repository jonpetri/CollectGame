#include "movedowncmd.h"

#include "model/game/collectgame.h"


//-----------------------------------------------------------------------------------------------------------------------
// MoveDownCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
MoveDownCmd::MoveDownCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("DOWN");
    this->setDescription("Move the player Down");
    this->setExpectedParameterCount(0);
}
MoveDownCmd::~MoveDownCmd()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// MoveDownCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * Move the player Down
 */
void MoveDownCmd::execute()
{
    if (m_model->movePlayer(E_MOVE::HOLD_ON, E_MOVE::FORWARD))
        this->modelModified();
    else
        this->sendMessageToUser("There is nothing this way   :-<\n");
}
