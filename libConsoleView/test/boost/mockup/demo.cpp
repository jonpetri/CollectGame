
#include "consoleview.h"
#include "consolecommand.h"
#include "consolecommandbaseInheritance.h"
#include "commanddisplaymockupmodelview.h"
#include "commandsetvaluemockupmodel.h"
#include "modelMockup.h"

#include <memory>



/**
 * ConsoleView library demonstration
 * @param argc Not Used
 * @param argv Not Used
 * @return 0 if success
 */
int main(int argc, char *argv[])
{
    // Model
    std::shared_ptr<ModelMockup> m = std::make_shared<ModelMockup>();

    // View
    std::shared_ptr<ConsoleView> v = ConsoleView::create();

    // Control
    std::shared_ptr<CommandDisplayMockupModelView> cDisplayMockupModelView = std::make_shared<CommandDisplayMockupModelView>();
    cDisplayMockupModelView->setModel(m);
    v->setDisplayMenuCommand(cDisplayMockupModelView);
    std::shared_ptr<ConsoleCommand<ModelMockup>> cSetValueMockupModel = std::make_shared<CommandSetValueMockupModel>();
    cSetValueMockupModel->setModel(m);
    v->addCommand(cSetValueMockupModel);

    v->run();

    return 0;
}
