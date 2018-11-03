/*----------------------------------------------------------------*/
/*  PROJECT:    Console View                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: ConsoleView
 *
 */
#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

// Includes:
#include <vector>
#include <memory>

#include "consolecommandbase.h"

class ConsoleView
{
public:
    ConsoleView();

    ~ConsoleView();

    // Getters:

    // Setters:
    void setDisplayModelViewCommand(const std::shared_ptr<ConsoleCommandBase> & displayModelViewCommand);


    // Methods:
    void addCommand(const std::shared_ptr<ConsoleCommandBase> & newCommand);
    void run();
    void executeCommand(const std::string & sUserEntry);
    void displayMenu();
    void printText(const std::string & sText);
    void displayModelView();
    void quit();

private:
    // Methods:

    // Members:
    std::vector< std::shared_ptr<ConsoleCommandBase> > m_commands;
    std::shared_ptr<ConsoleCommandBase> m_commandDisplayModelView;
    std::shared_ptr<ConsoleCommandBase> m_commandDisplayMenu;
    std::shared_ptr<ConsoleCommandBase> m_commandQuit;

    std::string m_sMenuDescrition;
    bool m_bQuit;
};

#endif // CONSOLEVIEW_H
