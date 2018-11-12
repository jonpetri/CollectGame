/*----------------------------------------------------------------*/
/*  PROJECT:    Console View                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: ConsoleCommand
 * See all the explanations about ConsoleCommand in the ConsoleCommandBase class.
 * The only purpose of this inheritance is to make ConsoleCommandBase hold a Model (or anything to operate).
 * To use ConsoleCommand<Model>, inherit it in a class, with model's head class as template parameter,
 * and implement the action in the .execute() method.
 */
#ifndef CONSOLECOMMAND_H
#define CONSOLECOMMAND_H

// Includes:
#include "consolecommandbase.h"
#include <memory>

template <class M>  // M for model
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
    std::shared_ptr<M> m_model;  ///< The head class of a model to be operate by the command
};


// Methods definitions (equivalent to .cpp)
// =========================================

//-----------------------------------------------------------------------------------------------------------------------
// ConsoleCommand :: Constructors / Destructors
//-----------------------------------------------------------------------------------------------------------------------
template<class M>
ConsoleCommand<M>::ConsoleCommand()
    : m_model{nullptr}
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
    m_model = modelHead;
}

//-----------------------------------------------------------------------------------------------------------------------
// ConsoleCommand :: Methods
//-----------------------------------------------------------------------------------------------------------------------

#endif // CONSOLECOMMAND_H
