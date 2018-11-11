#include "moveupcmd.h"

#include "model/game/collectgame.h"

//-----------------------------------------------------------------------------------------------------------------------
// MoveUpCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
MoveUpCmd::MoveUpCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("UP");
    this->setDescription("Move the player up");
    this->setExpectedParameterCount(0);
}
MoveUpCmd::~MoveUpCmd()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// MoveUpCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * Move the player up
 */
void MoveUpCmd::execute()
{
    if (m_model->movePlayer(E_MOVE::HOLD_ON, E_MOVE::BACKWARD))
        this->modelModified();
    else
        this->sendMessageToUser("There is nothing this way   :-<\n");
}
