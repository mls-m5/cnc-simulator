
#include "showwindow.h"

#include <BRepPrimAPI_MakeBox.hxx>
#include <STEPControl_Writer.hxx>
#include <Standard.hxx>
#include <Standard_CString.hxx>
#include <TopoDS_Shape.hxx>

void showWindow() {
    // Define the dimensions of the cube
    Standard_Real length = 100.0;
    Standard_Real width = 100.0;
    Standard_Real height = 100.0;

    // Create a box (cube) with the given dimensions
    TopoDS_Shape box = BRepPrimAPI_MakeBox(length, width, height).Shape();

    // Initialize a STEP writer
    STEPControl_Writer writer;
    writer.Transfer(box, STEPControl_AsIs);

    // Write the box shape to a STEP file
    Standard_CString filename = "cube.step";
    writer.Write(filename);

    // return 0;
}
