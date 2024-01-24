#include "assembly.h"
#include "makebottle.h" // Include your makebottle header
#include "step.h"
#include "viewer.h"
#include <QApplication>
#include <QMainWindow>
#include <filesystem>
#include <iostream>
#include <stdexcept>

std::filesystem::path getStepFile() {
    for (auto it : std::filesystem::directory_iterator{"data"}) {
        if (it.path().extension() == ".step") {
            return it.path();
        }
    }

    auto e = "no step file was found in `data` directory\n";
    std::cerr << e;
    throw std::runtime_error{e};
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QMainWindow mainWindow;

    // Create your OpenCASCADE viewer widget
    Viewer *viewer = new Viewer(&mainWindow);

    mainWindow.setCentralWidget(viewer);

    // Create the bottle shape using your function
    TopoDS_Shape bottleShape = MakeBottle(10, 10, 10);

    auto machineShape = [] {
        try {
            return loadStepFile(getStepFile());
        }
        catch (const std::runtime_error &e) {
            std::cerr << e.what() << std::endl;
            std::terminate();
        }
    }();

    auto assembly =
        splitIntoAssembly(machineShape, viewer->interactiveContext());
    // viewer->displayShape(assembly.getCompoundShape());
    viewer->displayShape(bottleShape);

    double value = 0;
    viewer->paintCallback([&]() {
        value += .1;
        assembly.setAxis({{value, value, value, value, value}});
        assembly.updateAxis();
    });

    mainWindow.show();

    // Display the shape
    viewer->displayShape(bottleShape);

    return a.exec();
}
