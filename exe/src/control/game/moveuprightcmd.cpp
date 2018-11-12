#include "moveuprightcmd.h"

#include "model/game/collectgame.h"


//-----------------------------------------------------------------------------------------------------------------------
// MoveUpRightCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
MoveUpRightCmd::MoveUpRightCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("UP RIGHT");
    this->setDescription("Move the player Up-Right");
    this->setExpectedParameterCount(0);
}
MoveUpRightCmd::~MoveUpRightCmd()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// MoveUpRightCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * Move the player UpRight
 */
void MoveUpRightCmd::execute()
{
    if (m_model->movePlayer(E_MOVE::FORWARD, E_MOVE::BACKWARD))
        this->modelModified();
    else
        this->sendMessageToUser("There is nothing this way   :-<\n");
}
