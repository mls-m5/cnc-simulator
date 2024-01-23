#include "viewer.h"

#include <Aspect_Handle.hxx>
#include <Graphic3d_GraphicDriver.hxx>
#include <OpenGl_GraphicDriver.hxx>
// #include <WNT_Window.hxx>
#include <AIS_Shape.hxx>
#include <X11/Xlib.h>
#include <Xw_Window.hxx>

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
    myView->Redraw();
}

Viewer::~Viewer() {}

void Viewer::displayShape(const TopoDS_Shape &shape) {
    // Display the shape in the interactive context
    Handle(AIS_Shape) aisShape = new AIS_Shape(shape);
    myInteractiveContext->Display(aisShape, Standard_True);

    myView->FitAll();
    myView->ZFitAll();
    myView->Redraw();
}

void Viewer::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    if (myView.IsNull()) {
        return;
    }
    myView->Redraw();
}
