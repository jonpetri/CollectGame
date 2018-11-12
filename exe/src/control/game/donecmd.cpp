#include "donecmd.h"

#include "model/game/collectgame.h"
#include "model/game/player.h"
#include "model/item/items.h"

//-----------------------------------------------------------------------------------------------------------------------
// DoneCmd :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
DoneCmd::DoneCmd()
{
    // Command's terms/arguments definition
    this->addCommandTerm("DONE");
    this->setDescription("Game completed");
    this->setExpectedParameterCount(0);
}
DoneCmd::~DoneCmd()
{

}

//-----------------------------------------------------------------------------------------------------------------------
// DoneCmd :: Methods
//-----------------------------------------------------------------------------------------------------------------------
/**
 * Command class: End of the game.
 * Check if the player is back to the start node, and congratulate.
 * back to main menu.
 */
void DoneCmd::execute()
{
    Items pickedItems;

    if (m_model->player()->isAtStartNode())
    {
        m_model->items()->getItemBatchOfHolder(m_model->player(), pickedItems);
        this->sendMessageToUser("\n");
        this->sendMessageToUser("CONGRATULATION!\n");
        this->sendMessageToUser("===============\n");
        this->sendMessageToUser(";-)\n");
        this->sendMessageToUser("\n");
        this->sendMessageToUser("You have finish with :\n");
        this->sendMessageToUser("   - a total value of " + std::to_string(pickedItems.value()) + "\n");
        this->sendMessageToUser("   - and a total weight of " + std::to_string(pickedItems.weight()) + "\n");
        this->sendMessageToUser("   - within " + std::to_string(pickedItems.count())  + " items\n");
        this->sendMessageToUser("\n");

        this->quitAssociatedViews();
        // The game is cleared when the game submenu and
    }
    else
    {
        this->sendMessageToUser("Game is not complete, you have to go back the start node to terminate.\n");
    }


}
