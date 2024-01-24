#pragma once

#include <TopoDS_Shape.hxx>

/// This file is from the OpenCASCADE examples
/// It shows how to use some operations on shapes and planes and stuff
TopoDS_Shape MakeBottle(const Standard_Real myWidth,
                        const Standard_Real myHeight,
                        const Standard_Real myThickness);
