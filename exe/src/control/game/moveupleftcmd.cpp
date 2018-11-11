#include "moveupleftcmd.h"

#include "model/game/collectgame.h"


//-----------------------------------------------------------------------------------------------------------------------
// MoveUpLeftCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
MoveUpLeftCmd::MoveUpLeftCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("UP LEFT");
    this->setDescription("Move the player up left");
    this->setExpectedParameterCount(0);
}
MoveUpLeftCmd::~MoveUpLeftCmd()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// MoveUpLeftCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * Move the player up left
 */
void MoveUpLeftCmd::execute()
{
    if (m_model->movePlayer(E_MOVE::BACKWARD, E_MOVE::BACKWARD))
        this->modelModified();
    else
        this->sendMessageToUser("There is nothing this way   :-<\n");
}
