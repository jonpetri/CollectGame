#include "movedownrightcmd.h"

#include "model/game/collectgame.h"


//-----------------------------------------------------------------------------------------------------------------------
// MoveDownRightCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
MoveDownRightCmd::MoveDownRightCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("DOWN RIGHT");
    this->setDescription("Move the player Down-Right");
    this->setExpectedParameterCount(0);
}
MoveDownRightCmd::~MoveDownRightCmd()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// MoveDownRightCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * Move the player DownRight
 */
void MoveDownRightCmd::execute()
{
    if (m_model->movePlayer(E_MOVE::FORWARD, E_MOVE::FORWARD))
        this->modelModified();
    else
        this->sendMessageToUser("There is nothing this way   :-<\n");
}
