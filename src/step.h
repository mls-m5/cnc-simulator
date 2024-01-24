#pragma once

#include <AIS_InteractiveContext.hxx>
#include <TopoDS_Shape.hxx>
#include <filesystem>

// TopoDS_Shape loadStepFile(std::filesystem::path path,
//                           Handle(AIS_InteractiveContext) theContext);
TopoDS_Shape loadStepFile(std::filesystem::path path);

class Assembly splitIntoAssembly(const TopoDS_Shape &compoundShape,
                                 AIS_InteractiveContext &context);
