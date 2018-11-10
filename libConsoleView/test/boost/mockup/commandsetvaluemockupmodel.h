/*----------------------------------------------------------------*/
/*  PROJECT:    Console View                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: CommandSetValueMockupModel
 *
 */
#ifndef CommandSetValueMockupModel_H
#define CommandSetValueMockupModel_H

// Includes:
#include "consolecommand.h"
#include "modelMockup.h"


class CommandSetValueMockupModel : public ConsoleCommand<ModelMockup>
{
public:
    CommandSetValueMockupModel()
    {
        // Command's terms/arguments definition
        this->addCommandTerm("SET");

        this->setDescription("Set model's string value. To set the string 'val', enter 'SET value'.");
        this->setExpectedParameterCount(1);
    }
    //~CommandSetValueMockupModel()override;

    // Getters:

    // Setters:

    // Methods:
    virtual void execute() override
    {
        m_model->setValue(this->commandsParameter(0));
        this->modelModified();
    }


private:
    // Methods:

    // Members:

};

#endif // CommandSetValueMockupModel_H
