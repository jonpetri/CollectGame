# ConsoleView Library

libConsoleView can be used in programs needing a console interface with a menu of commands. 

To use the library, a specific command class has to be impemented. That class need to:
- inherit from library's `ConsoleCommand<M>` template class, with M the "model" class (model in sense of the MVC pattern's model)
- implement the virtual method execute() , which will be executed to do something with the model.
- define the arguments to be written by the user to call execute the comment, with associated descriptions.

Then the libray is able to build a menu, display it in the console, catch entries, run commands... Of course command classes can send message to the user, stop the run, etc...

Here is a simple use [exemple](test/boost/mockup/demo.cpp), also build with the library as demo.
