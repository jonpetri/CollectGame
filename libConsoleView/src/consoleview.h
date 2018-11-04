/*----------------------------------------------------------------*/
/*  PROJECT:    Console View                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: ConsoleView
 * ConsoleView manage everything about text print and user entry.
 * The class contain commands. Each command provide an executable action and corresponding argument/command.
 * When ConsoleView is running, it catch user's entries and call the .execute() method of the corresponding command object.
 */
#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

// Includes:
#include <vector>
#include <memory>

#include "consolecommandbase.h"

class ConsoleView : public std::enable_shared_from_this<ConsoleView>
{


public:
    ConsoleView();
    ~ConsoleView();
    static std::shared_ptr<ConsoleView> create();

    // Getters:

    // Setters:
    void setQuitCommand(const std::shared_ptr<ConsoleCommandBase> & quitCommand);
    void setDisplayMenuCommand(const std::shared_ptr<ConsoleCommandBase> & displayMenuCommand);
    void setDisplayModelViewCommand(const std::shared_ptr<ConsoleCommandBase> & displayModelViewCommand);


    // Methods:
    void addCommand(const std::shared_ptr<ConsoleCommandBase> & newCommand);
    void removeCommand(const std::shared_ptr<ConsoleCommandBase> & cmd);
    void run();
    void executeCommand(std::string sUserEntry);
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
