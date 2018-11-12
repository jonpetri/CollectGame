# CollectGame
**Table of contents**
- [Folder structure](#p1)
- [Design](#p2)
- [Packages](#p3)
- [Tools](#p4)
- [Issues](#p5)

<br><a name="p1"></a> 
# Folder structure
### Root folders
There are 3 root folders:
- **design** 

Contains the class diagram of  the project and a readme file about some design details and main algorithms descriptions.
- **exe** (package folder)

Package of the executable. Contains the sources of  model and control classes and unit tests.
- **libConsoleView** (package folder)

Shared library package. Contains the sources of view classes, source files and unit tests.

### Package folders
Both packages are structured the same way.
- **src**  Sources: header and cpp files.

There is one header/cpp per class. The files are organised in sub folders, according to class families. All the classes and methods are commented, take a look at this comments to have details. 
- **test**  Boost tests.

The tests are organized exactly alike the sources. There is one test file per class, and if a test use mockup classes, they are in a "mockup" sub-folder.


<br><a name="p2"></a> 
# Design
The design is detailed in  [design/README.md](design/README.md). You can have a look to the project's class diagram as well: [design/class_diagram.pdf](design/class_diagram.pdf).


<br><a name="p3"></a> 
# Packages
The project is composed of 2 main packages, an executable "CollectGame" and a shared library (dll/so) "libConsoleView". LibConsoleView is separated since it can be reused in other projects.
### libConsoleView
libConsoleView could be reused in any program that wants this kind of interface: a console interface with a menu of commands. 
See details here: [libConsoleView/README.md](libConsoleView/README.md).

The package is in charge of the console interface. It's not linked to a third party library, but it includes Boost headers in order to use boost::signals2.

It is accompanied by 2 others cmake targets/packages: boost unit tests and an executable demo.

### CollectGame
The package contains model and control classes. It is not having any direct console in/out.
Again it's not linked to a third party library, but includes Boost headers in order to use boost::signals2 and boost::graph.

It is accompanied by an other cmake targets/package: boost unit tests.

<br><a name="p4"></a> 
# Tools
Useful information about used tools (version...)
- **Cmake**

version 3.12.0 for linux building, and version 3.5.2 for windows building (cross compilation with MXE). 
-> So I cant use the command: add_executable(TargetName) , and had to do it with add_executable(TargetName, sources), in the old way.
You can run cmake from a sub folder called "build*", as git ignore them.

- **Boost**

version 1.58 for linux building, and version 1.60 for windows building 

- **OS**

I built everything (including windows binaries) on Linux (Cross compilation with MXE). The project should be compilable natively on Windows, but I never tried. The unit tests pass on windows as well.

<br><a name="p5"></a> 
# Issues
### Problem with executable's unit tests
I don't know yet for which reason, but when I built the unit tests of the executable (CollectGame), the linker can't link the package CollectGame to libConsoleView any more. It sends me "Undefined reference to 'class::method()'" warning. That happens only with that unit test. After a day of fix trials, I chose to leave this unit tests aside.
Unit tests build of each package is optional thanks to cmake's cache options and I set this option off by default for the executable. The project builds well like that.

I didn't get the problem when I implemented the model, since I worked in a git-branch dedicated to the model. So I could write and run the unit tests of the model perfectly when I implemented the model. But now we can't run them any more, and command unit tests are missing.

### Random creation in windows
While writing that lines I figure out another problem: On windows the random function does not seem to work. Every run the map and items values are equal.  I didn't notice it before, since I launched it only a few time on windows, and (that's the mistake) the unit tests do not test the randomness. So here is a good lesson for me: randomness need to be tested.
