#include "viewer.h"

#include <Aspect_Handle.hxx>
#include <Graphic3d_GraphicDriver.hxx>
#include <OpenGl_GraphicDriver.hxx>
// #include <WNT_Window.hxx> // Only windows
#include <AIS_Shape.hxx>
#include <X11/Xlib.h> // Only linux
#include <Xw_Window.hxx>
#include <iostream>

Viewer::Viewer(QWidget *parent)
    : QWidget(parent) {
    // Initialize OpenCASCADE viewer
    Handle(Aspect_DisplayConnection) displayConnection =
        new Aspect_DisplayConnection();
    Handle(OpenGl_GraphicDriver) graphicDriver =
        new OpenGl_GraphicDriver(displayConnection, false);
    Handle(V3d_Viewer) viewer = new V3d_Viewer(graphicDriver);
    viewer->SetDefaultLights();
    viewer->SetLightOn();

    myInteractiveContext = new AIS_InteractiveContext(viewer);
    myView = viewer->CreateView();

    // Create a window and bind it to this widget
    Handle(Xw_Window) xwWindow =
        new Xw_Window(displayConnection, (Window)winId());
    myView->SetWindow(xwWindow);

    if (!xwWindow->IsMapped()) {
        xwWindow->Map();
    }

    myView->MustBeResized();
    myView->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, Quantity_NOC_GOLD, 0.08);
    myView->ZBufferTriedronSetup();

    setMinimumHeight(200);
    setMinimumWidth(400);

    setAutoFillBackground(
        false); // Prevent the widget from filling the background automatically
    setAttribute(Qt::WA_OpaquePaintEvent);   // Indicate that the paint event is
                                             // completely opaque
    setAttribute(Qt::WA_NoSystemBackground); // Indicate the system background
                                             // should not be drawn
}

Viewer::~Viewer() {}

void Viewer::displayShape(const TopoDS_Shape &shape) {
    // Display the shape in the interactive context
    Handle(AIS_Shape) aisShape = new AIS_Shape(shape);

    // Set the display mode to shaded (solid rendering)
    myInteractiveContext->SetDisplayMode(aisShape, AIS_Shaded, Standard_True);

    myInteractiveContext->Display(aisShape, Standard_True);

    myView->FitAll();
    myView->ZFitAll();
    myView->MustBeResized();
}

void Viewer::paintEvent(QPaintEvent *event) {

    QWidget::paintEvent(event);
    if (myView.IsNull()) {
        return;
    }
    // myView->Redraw();
    myView->Update(); // Trigger redraw

    std::cout << "draw" << std::endl;
}

void Viewer::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);

    if (!myView.IsNull()) {
        myView->FitAll(); // Adjust the camera to fit the entire model
        myView->MustBeResized();
    }
}
