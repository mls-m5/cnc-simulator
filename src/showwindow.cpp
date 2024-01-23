
// #include "showwindow.h"

// #include <AIS_InteractiveContext.hxx>
// #include <AIS_Shape.hxx>
// #include <Aspect_Handle.hxx>
// #include <BRepPrimAPI_MakeBox.hxx>
// #include <OpenGl_GraphicDriver.hxx>
// #include <STEPControl_Writer.hxx>
// #include <Standard.hxx>
// #include <Standard_CString.hxx>
// #include <TopoDS_Shape.hxx>
// #include <V3d_View.hxx>
// #include <V3d_Viewer.hxx>
// #include <WNT_Window.hxx>

// void showWindow() {
//     // Define the dimensions of the cube
//     Standard_Real length = 100.0;
//     Standard_Real width = 100.0;
//     Standard_Real height = 100.0;

//     // Create a box (cube) with the given dimensions
//     TopoDS_Shape box = BRepPrimAPI_MakeBox(length, width, height).Shape();

//     // Visualization part
//     // Create a graphic driver
//     Handle(Aspect_DisplayConnection) displayConnection;
//     Handle(OpenGl_GraphicDriver) graphicDriver =
//         new OpenGl_GraphicDriver(displayConnection);

//     // Create a 3D viewer
//     Handle(V3d_Viewer) viewer = new V3d_Viewer(graphicDriver);
//     viewer->SetDefaultLights();
//     viewer->SetLightOn();

//     // Create an interactive context
//     Handle(AIS_InteractiveContext) context = new
//     AIS_InteractiveContext(viewer);

//     // Create a view
//     Handle(V3d_View) view = viewer->CreateView();

//     // Create a window
//     Handle(WNT_Window) window = new WNT_Window("Open CASCADE Viewer",
//                                                Handle(WNT_WClass)::DownCast(),
//                                                WS_OVERLAPPEDWINDOW,
//                                                100,
//                                                100,
//                                                800,
//                                                600);
//     view->SetWindow(window);

//     // Map the window
//     if (!window->IsMapped()) {
//         window->Map();
//     }
//     view->MustBeResized();

//     // Display the shape
//     Handle(AIS_Shape) aisShape = new AIS_Shape(box);
//     context->Display(aisShape, Standard_True);

//     // Fit the view
//     view->FitAll();
//     view->ZFitAll();
//     view->Redraw();

//     // Start the window's message loop
//     Standard_Integer aLowerLeftX = 100;
//     Standard_Integer aLowerLeftY = 100;
//     Standard_Integer aWidth = 800;
//     Standard_Integer aHeight = 600;

//     Handle(WNT_Window) aWNTWindow =
//         new WNT_Window("Open CASCADE 3D Viewer",
//                        Handle(WNT_WClass)::DownCast(),
//                        WS_OVERLAPPEDWINDOW | WS_SIZEBOX | WS_MAXIMIZEBOX |
//                            WS_MINIMIZEBOX | WS_CLIPCHILDREN,
//                        aLowerLeftX,
//                        aLowerLeftY,
//                        aWidth,
//                        aHeight);
//     aWNTWindow->SetVirtual(window->Virtual());
//     aWNTWindow->Map();

//     MSG aMessage;
//     while (GetMessage(&aMessage, NULL, 0, 0)) {
//         TranslateMessage(&aMessage);
//         DispatchMessage(&aMessage);
//     }

//     // return 0;
// }

// // void showWindow() {
// //     // Define the dimensions of the cube
// //     Standard_Real length = 100.0;
// //     Standard_Real width = 100.0;
// //     Standard_Real height = 100.0;

// //     // Create a box (cube) with the given dimensions
// //     TopoDS_Shape box = BRepPrimAPI_MakeBox(length, width, height).Shape();

// //     // Initialize a STEP writer
// //     STEPControl_Writer writer;
// //     writer.Transfer(box, STEPControl_AsIs);

// //     // Write the box shape to a STEP file
// //     Standard_CString filename = "cube.step";
// //     writer.Write(filename);

// //     // return 0;
// // }
