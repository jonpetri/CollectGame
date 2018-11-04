/*----------------------------------------------------------------*/
/*  PROJECT:    Console View                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: ConsoleCommand
 *
 */
#ifndef CONSOLECOMMAND_H
#define CONSOLECOMMAND_H

// Includes:
#include "consolecommandbase.h"
#include <memory>

template  <class M>  // M for model
class ConsoleCommand : public ConsoleCommandBase
{
public:
    ConsoleCommand();

    ~ConsoleCommand();

    // Getters:

    // Setters:
    void setModel(const std::shared_ptr<M> & modelHead);

    // Methods:
    virtual void execute() override = 0;

protected:
    // Methods:

    // Members:

    std::shared_ptr<M> m_model;

};




// Methodes definitions (equivalent to .cpp)



//-----------------------------------------------------------------------------------------------------------------------
// ConsoleCommand :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
template<class M>
ConsoleCommand<M>::ConsoleCommand()
{

}
template<class M>
ConsoleCommand<M>::~ConsoleCommand()
{

}


//-----------------------------------------------------------------------------------------------------------------------
// ConsoleCommand :: Getters
//-----------------------------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------------------------
// ConsoleCommand :: Setters
//-----------------------------------------------------------------------------------------------------------------------
template<class M>
void ConsoleCommand<M>::setModel(const std::shared_ptr<M> & modelHead)
{
    m_modelHead = modelHead;
}

//-----------------------------------------------------------------------------------------------------------------------
// ConsoleCommand :: Methods
//-----------------------------------------------------------------------------------------------------------------------

#endif // CONSOLECOMMAND_H
