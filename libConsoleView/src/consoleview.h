/*----------------------------------------------------------------*/
/*  PROJECT:    Console View                                      */
/*----------------------------------------------------------------*/
/**
 * CLASS: ConsoleView
 * ConsoleView is the central class of the library ConsoleView.
 * ConsoleView manage everything about text print and user entry.
 * The class contain a collection of commands. Each command provide an executable action and corresponding argument/command (for user entry).
 * When ConsoleView is running, it catch user's entries and call the ConsoleView::execute() method of the corresponding command object.
 *
 * Command menu
 * ------------
 * Thanks to the command collection, ConsoleView construct and display a command menu.
 * The command menu is a list of all the commands, with a associated description.
 *
 * Default commands
 * ----------------
 * ConsoleView has 2 defaults commands: Quit and DisplayMenu.
 * They are customizable and replaceable.
 *
 * DisplayModelView Command
 * -------------------------
 * This command is a very particular command.
 * If needed, The command class has to be written by inheriting the class ConsoleCommand<Model>,
 * then link it to ConsoleView using the method ConsoleView::setDisplayModelViewCommand().
 * Once that done, the command can be executed via the signal .modelModified() of each command.
 *
 * Run
 * ====
 * Once set up, just run the user interface with ConsoleView::run().
 * The menu is shown, and the user can enter commands.
 * The run method will end when the user enter the quit command.
 *
 * Note: To create a new instance use the static method .create(), and not the constructor. Otherwise it will crash.
 * (I didn't manage to make private the constructor...)
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
    std::shared_ptr<ConsoleCommandBase> quitCommand();
    std::shared_ptr<ConsoleCommandBase> displayMenuCommand();

    // Setters:
    void setQuitCommand(const std::shared_ptr<ConsoleCommandBase> & quitCommand);
    void setDisplayMenuCommand(const std::shared_ptr<ConsoleCommandBase> & displayMenuCommand);
    void setDisplayModelViewCommand(const std::shared_ptr<ConsoleCommandBase> & displayModelViewCommand);
    void setMenuDescrition(const std::string & m_sMenuDescrition);


    // Methods:
    static void displayAppName(const std::string & sName);
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
