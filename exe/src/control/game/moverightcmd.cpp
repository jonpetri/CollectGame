#include "moverightcmd.h"

#include "model/game/collectgame.h"


//-----------------------------------------------------------------------------------------------------------------------
// MoveRightCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
MoveRightCmd::MoveRightCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("RIGHT");
    this->setDescription("Move the player Right");
    this->setExpectedParameterCount(0);
}
MoveRightCmd::~MoveRightCmd()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// MoveRightCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * Move the player Right
 */
void MoveRightCmd::execute()
{
    if (m_model->movePlayer(E_MOVE::FORWARD, E_MOVE::HOLD_ON))
        this->modelModified();
    else
        this->sendMessageToUser("There is nothing this way   :-<\n");
}
