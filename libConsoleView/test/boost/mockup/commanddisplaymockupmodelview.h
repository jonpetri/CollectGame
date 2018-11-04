/*----------------------------------------------------------------*/
/*  PROJECT:    Console View                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: DisplayMockupModelViewCommand
 *
 */
#ifndef COMMANDDISPLAYMOCKUPMODELVIEW_H
#define COMMANDDISPLAYMOCKUPMODELVIEW_H

// Includes:
#include "consolecommand.h"
#include "modelMockup.h"


class CommandDisplayMockupModelView : public ConsoleCommand<ModelMockup>
{
public:
    CommandDisplayMockupModelView()
    {
        // Command's terms/arguments definition
        this->addCommandTerm("GET");

        this->setDescription("get model's value");
    }
    //~DisplayMockupModelViewCommand()override;

    // Getters:

    // Setters:

    // Methods:
    virtual void execute() override
    {
        this->sendMessageToUser("Model's value is: " + m_model->value() + "\n");
    }


private:
    // Methods:

    // Members:

};

#endif // COMMANDDISPLAYMOCKUPMODELVIEW_H
