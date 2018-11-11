#include "startnewcmd.h"

#include "model/game/collectgame.h"

//-----------------------------------------------------------------------------------------------------------------------
// StartNewCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
StartNewCmd::StartNewCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("NEW");
    this->setDescription("Start a new game: new map generation");
    this->setExpectedParameterCount(0);
}
StartNewCmd::~StartNewCmd()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// StartNewCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * Command class: Start a new game: new map generation
 */
void StartNewCmd::execute()
{
    m_model->createNewGame();
    this->modelModified();
}
