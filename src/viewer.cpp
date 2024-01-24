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

    _interactiveContext = new AIS_InteractiveContext(viewer);
    _view = viewer->CreateView();

    // Create a window and bind it to this widget
    Handle(Xw_Window) xwWindow =
        new Xw_Window(displayConnection, (Window)winId());
    _view->SetWindow(xwWindow);

    if (!xwWindow->IsMapped()) {
        xwWindow->Map();
    }

    _view->MustBeResized();
    _view->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, Quantity_NOC_GOLD, 0.08);
    _view->ZBufferTriedronSetup();

    // _view->SetDefaultLights();
    // _view->SetLightOn();

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

    _interactiveContext->Display(aisShape, Standard_True);
    _interactiveContext->SetDisplayMode(aisShape, AIS_Shaded, Standard_True);

    _view->FitAll();
    _view->ZFitAll();
    _view->MustBeResized();
}

void Viewer::paintEvent(QPaintEvent *event) {

    QWidget::paintEvent(event);
    if (_view.IsNull()) {
        return;
    }
    // myView->Redraw();
    _view->Update(); // Trigger redraw

    std::cout << "draw" << std::endl;
}

void Viewer::resizeEvent(QResizeEvent *event) {
    QWidget::resizeEvent(event);

    if (!_view.IsNull()) {
        _view->FitAll(); // Adjust the camera to fit the entire model
        _view->MustBeResized();
    }
}
