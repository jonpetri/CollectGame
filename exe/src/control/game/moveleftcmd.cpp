#include "moveleftcmd.h"

#include "model/game/collectgame.h"


//-----------------------------------------------------------------------------------------------------------------------
// MoveLeftCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
MoveLeftCmd::MoveLeftCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("LEFT");
    this->setDescription("Move the player Left");
    this->setExpectedParameterCount(0);
}
MoveLeftCmd::~MoveLeftCmd()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// MoveLeftCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * Move the player
 */
void MoveLeftCmd::execute()
{
    if (m_model->movePlayer(E_MOVE::BACKWARD, E_MOVE::HOLD_ON))
        this->modelModified();
    else
        this->sendMessageToUser("There is nothing this way   :-<\n");
}
