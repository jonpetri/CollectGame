#include "movedownleftcmd.h"

#include "model/game/collectgame.h"


//-----------------------------------------------------------------------------------------------------------------------
// MoveDownLeftCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
MoveDownLeftCmd::MoveDownLeftCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("DOWN LEFT");
    this->setDescription("Move the player Down-Left");
    this->setExpectedParameterCount(0);
}
MoveDownLeftCmd::~MoveDownLeftCmd()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// MoveDownLeftCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * Move the player DownLeft
 */
void MoveDownLeftCmd::execute()
{
    if (m_model->movePlayer(E_MOVE::BACKWARD, E_MOVE::FORWARD))
        this->modelModified();
    else
        this->sendMessageToUser("There is nothing this way   :-<\n");
}
