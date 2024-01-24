// #include "makebottle.h"
// #include "showwindow.h"

// int main() {
//     MakeBottle(10, 10, 10);
//     showWindow();
// }

#include "makebottle.h" // Include your makebottle header
#include "viewer.h"
#include <QApplication>
#include <QMainWindow>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QMainWindow mainWindow;

    // Create your OpenCASCADE viewer widget
    Viewer *viewerWidget = new Viewer(&mainWindow);

    mainWindow.setCentralWidget(viewerWidget);

    // Create the bottle shape using your function
    TopoDS_Shape bottleShape = MakeBottle(10, 10, 10);

    mainWindow.show();

    // Display the shape
    viewerWidget->displayShape(bottleShape);

    return a.exec();
}
