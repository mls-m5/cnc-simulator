#include "step.h"
#include "assembly.h"
#include <AIS_InteractiveContext.hxx>
#include <AIS_Shape.hxx>
#include <IFSelect_ReturnStatus.hxx>
#include <STEPControl_Reader.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Shape.hxx>

TopoDS_Shape loadStepFile(std::filesystem::path path) {
    STEPControl_Reader reader;
    IFSelect_ReturnStatus status = reader.ReadFile(path.c_str());

    if (status != IFSelect_ReturnStatus::IFSelect_RetDone) {
        throw std::runtime_error("Error: Cannot read STEP file.");
    }

    // Perform the transfer from STEP to OpenCASCADE
    reader.TransferRoots();
    TopoDS_Shape shape = reader.OneShape();

    return shape;
}

Assembly splitIntoAssembly(const TopoDS_Shape &compoundShape,
                           AIS_InteractiveContext &context) {
    auto assembly = Assembly{context};
    TopExp_Explorer explorer;
    for (explorer.Init(compoundShape, TopAbs_SOLID); explorer.More();
         explorer.Next()) {
        assembly.addPart(explorer.Current());
    }
    return assembly;
}

// /// This more complex version is to fix lighting issues, but I don't think it
// /// did anything
// TopoDS_Shape loadStepFile(std::filesystem::path path,
//                           Handle(AIS_InteractiveContext) theContext) {
//     STEPControl_Reader reader;
//     IFSelect_ReturnStatus status = reader.ReadFile(path.c_str());

//     if (status != IFSelect_ReturnStatus::IFSelect_RetDone) {
//         throw std::runtime_error("Error: Cannot read STEP file.");
//     }

//     // Perform the transfer from STEP to OpenCASCADE
//     reader.TransferRoots();
//     TopoDS_Shape shape = reader.OneShape();

//     // If you have an interactive context and want to set visual properties:
//     if (!theContext.IsNull()) {
//         Handle(AIS_Shape) aisShape = new AIS_Shape(shape);

//         // Set display properties
//         aisShape->SetMaterial(Graphic3d_NOM_STEEL);  // Set the material
//         aisShape->SetColor(Quantity_NOC_STEELBLUE3); // Set the color
//         theContext->Display(aisShape,
//                             AIS_Shaded); // Display the shape with shading

//         // Ensure proper lighting and shading
//         theContext->SetDisplayMode(aisShape, AIS_Shaded, Standard_True);
//     }

//     return shape;
// }
